
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

int pipefdth1[2],pipefdth2[2],pipefdth3[2];
int MAX = 1000;

void *sendmessage(void *p)
{
    char e[1] = "C";
    char b[1];
    int i = 0;
for(i=0;i<MAX;++i)
{
    write(pipefdth1[1],e,1);
    read(pipefdth2[0],b,1);
}
}
void *sendmessage2(void *p)
{
    char e[1] = "D";
    char b[1];
    int i = 0,t=0;
    int *time;
    time = malloc(sizeof(int));
    unsigned long long int t1,t2;
for(i=0;i<MAX;++i)
{   
    t1 = rdtsc();
    write(pipefdth2[1],e,1);
    read(pipefdth1[0],b,1);
    t2 = rdtsc();
    t = t + (t2-t1);
}

*time = t/2000;
pthread_exit(time);
}
void *sendmessagelocal(void *p)
{
    char e[1] = "D";
    char b[1];
    int i = 0,t=0;
    unsigned long long int t1,t2;
    int *time;
    time = malloc(sizeof(int));
for(i=0;i<MAX;++i)
{   
    t1 = rdtsc();
    write(pipefdth3[1],e,1);
    read(pipefdth3[0],b,1);
    t2 = rdtsc();
    t = t + (t2-t1);
}

*time = t/1000;
pthread_exit(time);
}


int main(int argc, char const *argv[])
{

        unsigned long long int a,b,t1=0,t2=0;
        int pid,n;
        int pipefd1[2],pipefd2[2],i;
        char child[1] = "C";
        char parent[1] = "P";
        pipe(pipefd1);
        pipe(pipefd2);
        
        int localcom[10000],interproc[10000];

        for (i = 0; i < 10000; ++i)
        {
            a = rdtsc();
            n = write(pipefd1[1],parent,1);
            n = read(pipefd1[0],parent,1);
            b = rdtsc();

            localcom[i] = b-a;

            t1 = t1 + localcom[i];

        }        

        t1 = t1/10000;

        pid = fork();

    for (i = 0; i < 10000; ++i)
    {
        if (pid == 0)
        {
            n = read(pipefd1[0],child,1);
            n = write(pipefd2[1],child,1);
			if (i==9999)
			{
				exit(0);
			}
        }


        else
        {
            
            a = rdtsc();
            n = write(pipefd1[1],parent,1);
            n = read(pipefd2[0],parent,1);
            b = rdtsc();
            
            interproc[i] = b-a;   
            t2 = t2 + interproc[i]; 
        }

        
    }
    t2 = t2/20000;
    if (pid!=0)
    {
        printf("Context switch time between processes %llu \n",t2-t1);
    }
    
 pthread_t th1,th2,th3;
 pipe(pipefdth1);
 pipe(pipefdth2);
 pipe(pipefdth3);
 int *local,*interthread;
 pthread_create(&th3,NULL,sendmessagelocal,NULL);
 pthread_join(th3,(void *) &local);
 pthread_create(&th1,NULL,sendmessage,NULL);
 pthread_create(&th2,NULL,sendmessage2,NULL);
 pthread_join(th1,NULL);
 pthread_join(th2,(void *) &interthread);

 
 printf("Average time context switch between threads %d \n", (*interthread - *local));
   
	return 0;

}