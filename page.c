
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
unsigned long long int rdtsc(void)
{
   unsigned long long int x;
   unsigned a, d;

   __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

   return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}


int main()
{
	unsigned long long int i,a,b,size,rm,a1,b1;
	char *p1,*p2;
	int t;
	int page_min=100000;
	int mul = 1024*4;
	size = 1024*1024;
	unsigned long long int page_max=0; 
	while(mul>0)
	{
		
		p1= (char *)malloc(size*sizeof(char));
		memset(p1,'C',size*sizeof(char));
		mul--;
	}
	mul = 1024*4;
	while(mul>0)
	{
		
		p2 = (char *)malloc(size*sizeof(char));
		memset(p2,'D',size*sizeof(char));
		mul--;
	}
	a = rdtsc();
	char c = p2[1234];
	b=rdtsc();
for (i = 0; i < size; ++i)
{
	a1 = rdtsc();
	c = p1[i];
	b1=rdtsc();
	if (page_max  < (b1-a1))
	{
		page_max = (b1-a1);
	}
	
}
	

	printf("%llu     , %llu\n",(b-a),page_max);
	return 0;
	
}	