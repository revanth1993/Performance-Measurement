#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

unsigned long long int rdtsc(void)
{
   unsigned long long int x;
   unsigned a, d;
 
   __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));
 
   return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

int main(int argc, char const *argv[])
{

	unsigned long long int a,b;
	int time=0,i;
	for (i = 0; i < 10; ++i)
	{
     
     a=rdtsc();
     b=rdtsc();
     
     printf("%llu\n",b-a);
	time = time + (b-a);
	}

	printf("average delay in successive time stamp counters %d\n", time/10);
	return 0;
}