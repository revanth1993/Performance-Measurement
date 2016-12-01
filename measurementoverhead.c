#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
unsigned long long int rdtsc(void)
{
   unsigned long long int x;
   unsigned a, d;
 
   __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));
 
   return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

int main(void)
{

unsigned long long int a,b,avg=0;
int i;
int sd[100000],sdev=0;
for(i = 0;  i<100000 ; i++)
{
    a=rdtsc();
    b=rdtsc(); 
    avg = avg + b-a;
    sd[i] = b-a;
}

printf("Average no of clock cycles spent for measuring time %llu \n" ,avg/100000);
avg = avg/100000;
for (i = 0; i < 100000; ++i)
  {
    sdev = sdev + (sd[i]-avg)*(sd[i]-avg);
  }	

printf("standard deviation %lf \n" ,sqrt(sdev)/100000);

  return 0;
}
