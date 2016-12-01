
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
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
	unsigned long long int i,a,b,a1,b1;
	char *p,*q;
	unsigned long long int size;
	
	
	
	size = 1024*1024*1024;
	p = (char *) malloc(1024*1024*1024);
	q = (char *) malloc(1024*1024*1024);
	a1 = rdtsc();
	memset(p,'C',size);
	b1 = rdtsc();
	
	
	a  = rdtsc();
	memcpy(q,p,size);
	b = rdtsc();
	
	printf("write time for 1GB %f \n ",(float) (b1-a1)/2530000000);
	printf("memcpy time for 1GB %f \n" ,(float) (b-a)/2530000000);
	free(p);
	return 0;
}	
