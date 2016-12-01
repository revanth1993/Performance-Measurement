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

	unsigned long long int a,b,clockcyle=0;
	int i;
    for (i = 0; i < 10; ++i)
    {
  
     a=rdtsc();
     sleep(1);
     b=rdtsc();
     
     printf("%llu\n",b-a);
	   clockcyle = clockcyle + (b-a);
    }

printf("The average time stamp counter for a sleep of 1 second in between %llu\n", clockcyle/10);
	return 0;
}