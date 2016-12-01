#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
unsigned long long int rdtsc(void)
{
   unsigned long long int x;
   unsigned a, d;

   __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

   return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

void *message1(void *p)
{
    unsigned long long int a;
    a = rdtsc();
    unsigned long long int *b;
    b = malloc(sizeof(a));
    *b = a;
    pthread_exit(b);

}
int main(int argc, char const *argv[])
{

        unsigned long long int a,b;
        int pid,n;
        int pipefd1[2],pipefd2[2],i,j,sdev;
        unsigned long long int  child,parent,*thread,avg=0;
        int sd_p[10000],sd_t[10000];
		pipe(pipefd1);
       for (i = 0; i < 10000; ++i)
      {
            a = rdtsc();
            n = fork();
            if (n==0)
            {
                child=rdtsc();
                write(pipefd1[1],&child,sizeof(child));
                exit(0);
            }

            else
            {
                pid = read(pipefd1[0],&parent,sizeof(parent));
            }
       avg = avg + (parent-a);
       sd_p[i] = parent-a;
        }
sdev=0;
for (j = 0; j < 10000; ++j)
    {
      sdev = sdev + (sd_p[j]-avg/10000)*(sd_p[j]-avg/10000);
    } 

    printf("Average time for child process creation %llu standard deviation %lf\n",avg/10000,sqrt(sdev)/10000);

	avg = 0;
	pthread_t t1;
    
       for (i = 0; i < 10000; ++i)
      {
            a = rdtsc();
            pthread_create(&t1,NULL,message1,NULL);
            pthread_join(t1,(void *) &thread);
            avg = avg + (*thread-a);
            sd_t[i] = (*thread-a);
	}
sdev=0;
for (j = 0; j < 10000; ++j)
    {
      sdev = sdev + (sd_t[j]-avg/10000)*(sd_t[j]-avg/10000);
    } 

    printf("Average time for  thread creation %llu standard deviation %lf\n",avg/10000,sqrt(sdev)/10000);
    return 0;

}