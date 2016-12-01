#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
unsigned long long int rdtsc(void)
{
   unsigned long long int x;
   unsigned a, d;

   __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

   return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

struct node{
	struct node *next;
	struct node *step;
};

struct node* construct_list(int size,int stride)
{
	struct node *p,*head,*temp;
	int i=0;
	head = (struct node*) malloc(sizeof(struct node));
	head->next = NULL;
	p = head;
	temp = head;
	while(i<size/sizeof(struct node))
	{
		p->next = (struct node*) malloc(sizeof(struct node));
		p->next->next = NULL; 
		i = i + 1;
		p = p->next;
	}

	while(temp->next!=NULL)
	{
		i=0;
		struct node *assign = temp;
		while(i<stride&&assign->next!=NULL)
		{
			assign = assign->next;
			i++;
		}
		temp->step = assign;
		temp = temp->next;
	}

	temp->step = head;

	return head;
}
void access_list(struct node *head)
{
	unsigned long long int i;
	for(i=0;i<1000000;i++)
	{
		head = head->step;
	}
}
int main()
{
	struct node *head,*p;
	unsigned long long int a,b;
	int stride,size;
	for(stride = 1 ; stride <= 16 ; stride*=2)
	{
		for(size=512;size<=1024*1024*64;size*=2)
		{
			head = construct_list(size,stride);
			a = rdtsc();
			access_list(head);
			b = rdtsc();
			free(head);
		
		printf("%llu\n",(b-a));
		}
	printf("\n");
		
	}
}	
