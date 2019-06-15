/*
 * Author: Mardan
 * Date: 2019.6.13
 * Project: GuzalAida
 */


#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


FILE *fp;


char time[16];
char temp[16];
char cpu_load[16];
char io_used[16];
char RAM_used[16];

float cpu_temp=0;


void get_now_time(){
  struct tm *ptr;
  time_t lt;
  lt=time(NULL);
  ptr=localtime(&lt);
  strftime(time,16,"%I:%M:%S - %b",ptr);
}

char *get_cpu_temp(){
  fp=popen("cat /sys/class/thermal/thermal_zone0/temp","r");
  fscanf(fp,"%d",&cpu_temp);
  cpu_temp=cpu_temp/1000;
  sprintf(temp,"%1f",cpu_temp);
  pclose(fp);
}

char *get_cpu_load(){
  fp=popen("uptime | awk '{print $9,$10,$11,$12}'","r");
  fscanf(fp,"%s",&load);
  pclose(fp);
}

char *get_io_used(){
	sprintf(io_used,"%4.2f",get_io_occupy());
}

char *get_RAM_used(){
	get_mem_occupy(&mem);
	double using = ((double)(mem.total - mem.free)/mem.total)*100;
	sprintf(RAM_used,"%4.2f",using);
}