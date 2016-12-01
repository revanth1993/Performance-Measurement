
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
unsigned long long int rdtsc(void)
{
   unsigned long long int x;
   unsigned a, d;

   __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

   return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

void procedure(void)
{
        int x=0;
}

int main(int argc, char const *argv[])
{

        unsigned long long int a,b;
        int sys_time=0,i,pid,proc_time=0;
        int avg_proc,avg_sys;
        int sd_proc[100000],sd_sys[100000];

        for (i = 0; i < 100000; ++i)
        {

                a=rdtsc();
                int fd = open("t.txt",O_WRONLY|O_CREAT);
                b=rdtsc();
                close(fd);
                remove("t.txt");
         		sys_time = sys_time + (b-a);
                sd_sys[i] = (b-a);

         		a=rdtsc();
                procedure;
                b=rdtsc();
         		proc_time = proc_time + (b-a);
                sd_proc[i] = (b-a);

        }
        int sdev_proc=0,sdev_sys=0;
avg_sys = sys_time/100000;
avg_proc = proc_time/100000;
for (i = 0; i < 100000; ++i)
  {

    sdev_proc = sdev_proc + (sd_proc[i]-avg_proc)*(sd_proc[i]-avg_proc);
    sdev_sys = sdev_sys + (sd_sys[i]-avg_sys)*(sd_sys[i]-avg_sys);
  } 

        printf("average time for system call %d standard deviation %lf \n", sys_time/100000,sqrt(sdev_sys)/100000);
		printf("average time for procedure call %d standard deviation %lf \n",proc_time/100000,sqrt(sdev_proc)/100000);
        return 0;
}