/*
 * Author: Mardan
 * Date: 2019.6.10
 * Project: GuzalAida
 */


#include <time.h>
#include <stdio.h>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>

#define uchar unsigned char

//Global variable
FILE *fp;
char nowtime[16];
char cpu_load[16];
int lcdprint_page=1;

void gpio_init(void);
void lcd1602_control(uchar cmd);
void lcd1602_command(uchar dat);
void lcd1602_setmode(void);
void lcdprint(uchar *p,int row_number);

void page1();


int main(int argc, char const *argv[]){
  wiringPiSetup();
  gpio_init();
  lcd1602_setmode();
  lcdprint("   Welcome to",1);
  lcdprint(" GuzalAida CVN",2);
  sleep(3);
  openlog("displayinfo4lcd",LOG_CONS | LOG_PID,LOG_LOCAL0);
  syslog(LOG_INFO,"LCD1606 display info starting...");
  while(1){
    lcd1602_control(0x01);//清屏
    page1();
    /*
    switch(1){
      case 1:page1(lcdprint_page);break;
      //case 2:page2();break;
      //case 3:page3();break;
      default:lcdprint_page=1;break;
    }*/
    lcdprint_page++;
    sleep(1);
  }
  return 0;
}

void page1(){
  struct tm *ptr;
  time_t lt;
  lt=time(NULL);
  ptr=localtime(&lt);
  strftime(nowtime,16,"%I:%M:%S - %b",ptr);
  lcdprint(nowtime,1);
  fp=popen("uptime | awk '{print $9,$10,$11,$12}'","r");
  fgets(cpu_load,16,fp);
  lcdprint(cpu_load,2);
  printf("Time: %s --- Load: %s\n",nowtime,cpu_load);
  if(lcdprint_page>100){syslog(LOG_INFO,"Time: %s --- Load: %s\n",nowtime,cpu_load);lcdprint_page=0;}
  pclose(fp);

}

void gpio_init(){
    //data pin(0 to 7) Setpin
    pinMode(10,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    pinMode(14,OUTPUT);
    pinMode(21,OUTPUT);
    pinMode(22,OUTPUT);
    pinMode(23,OUTPUT);

    pinMode(26,OUTPUT); //RS Setpin
    pinMode(27,OUTPUT); //EN Setpin
}

void lcd1602_control(uchar cmd){
  digitalWrite(26,LOW); //RS = 0
  digitalWriteByte(cmd);//GPIO0=cmd
  digitalWrite(27,HIGH);
  delay(5);
  digitalWrite(27,LOW);
}

void lcd1602_command(uchar dat){
  digitalWrite(26,HIGH); //RS=1
  digitalWriteByte(dat);//GPIO0=dat
  digitalWrite(27,HIGH);// EN=1;
  delay(5);     
  digitalWrite(27,LOW);// EN=0;       
}

void lcd1602_setmode(void){
  lcd1602_control(0x38);//八线模式下两行显示 
  lcd1602_control(0x0c);//开启显示
  lcd1602_control(0x06);//地址+1
  lcd1602_control(0x01);//清屏
}

void lcdprint(uchar *p,int row_number){
  int i=0;
  row_number==1?lcd1602_control(0x80):lcd1602_control(0xc0);
  while(p[i]!='\0'){
    lcd1602_command(p[i]);
    i++;
  }
}
