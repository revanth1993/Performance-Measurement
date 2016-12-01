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

void procedurecall()
{
	
}
void procedurecall1(int a[])
{

	
}

void procedurecall2(int a[],int b[])
{
	
}

void procedurecall3(int a[],int b[], int c[])
{
	
}

void procedurecall4(int a[],int b[], int c[], int d[])
{
	
}

void procedurecall5(int a[],int b[], int c[], int d[], int e[])
{
	
}

void procedurecall6(int a[],int b[], int c[], int d[], int e[], int f[])
{
	

	
}

void procedurecall7(int a[],int b[], int c[], int d[], int e[], int f[],int g[])
{
	
}

int main(void)
{

	unsigned long long int a,b;
    int i,average=0;

    int arg1[1024*100],arg2[1024*100],arg3[1024*100],arg4[1024*100],arg5[1024*100],arg6[1024*100],arg7[1024*100];
	int avg_delay[8]={0,0,0,0,0,0,0,0};
	int sd[8][100000];
	procedurecall();
	procedurecall1(arg1);
	procedurecall2(arg1,arg2);
	procedurecall3(arg1,arg2,arg3);
	procedurecall4(arg1,arg2,arg3,arg4);
	procedurecall5(arg1,arg2,arg3,arg4,arg5);
	procedurecall6(arg1,arg2,arg3,arg4,arg5,arg6);
	procedurecall7(arg1,arg2,arg3,arg4,arg5,arg6,arg7);
	
	
for(i=0;i<=100000;i++)
{
		a = rdtsc();
		procedurecall();
		b = rdtsc();
		avg_delay[0] = avg_delay[0]+(b-a);
		sd[0][i] = (b-a);

		a = rdtsc();
		procedurecall1(arg1);
		b = rdtsc();
		avg_delay[1] = avg_delay[1]+(b-a);
		sd[1][i] = (b-a);		
    	
    	a = rdtsc();
		procedurecall2(arg1,arg2);
		b = rdtsc();
		avg_delay[2] = avg_delay[2]+(b-a);
		sd[2][i] = (b-a);
    	
    	a = rdtsc();
		procedurecall3(arg1,arg2,arg3);
		b = rdtsc();
		avg_delay[3] = avg_delay[3]+(b-a);
		sd[3][i] = (b-a);
    	
    	a = rdtsc();
		procedurecall4(arg1,arg2,arg3,arg4);
		b = rdtsc();
		avg_delay[4] = avg_delay[4]+(b-a);
		sd[4][i] = (b-a);
    	
    	a = rdtsc();
		procedurecall5(arg1,arg2,arg3,arg4,arg5);
		b = rdtsc();
		avg_delay[5] = avg_delay[5]+(b-a);
		sd[5][i] = (b-a);
    	
    	a = rdtsc();
		procedurecall6(arg1,arg2,arg3,arg4,arg5,arg6);
		b = rdtsc();
		avg_delay[6] = avg_delay[6]+(b-a);
		sd[6][i] = (b-a);
		
		a=rdtsc();
    	procedurecall7(arg1,arg2,arg3,arg4,arg5,arg6,arg7);
    	b=rdtsc();
		avg_delay[7] = avg_delay[7]+(b-a); 
		sd[7][i] = (b-a);
}
for(i=0;i<8;i++)
{
	printf("average time for %d argument procedure call %d \n" ,i,avg_delay[i]/100000);
	int avg;
	avg = avg_delay[i]/100000;
	int sdev = 0;
	int j;
	for (j = 0; j < 100000; ++j)
  	{
    	sdev = sdev + (sd[i][j]-avg)*(sd[i][j]-avg);
  	}	

  	printf("standard deviation for %d argument %lf\n",i,sqrt(sdev)/100000);


}
    return 0;
}
