/*
 * Author: Mardan
 * Date: 2019.6.10
 * Project: GuzalAida
 */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>
#define uchar unsigned char

FILE *fp;
char str1[15],str2[10];

void gpio_init(){
    int i;
    for(i=0;i<8;i++){
         pinMode(i,OUTPUT);
    } //data pin(0 to 7) Setpin
    pinMode(27,OUTPUT); //RS Setpin
    pinMode(28,OUTPUT); //EN Setpin
}

void lcd1602_control(uchar cmd){
  digitalWrite(27,LOW); //RS = 0
  digitalWriteByte(cmd);//GPIO0=cmd
  digitalWrite(28,HIGH);
  delay(5);
  digitalWrite(28,LOW);
}

void lcd1602_command(uchar dat){
  digitalWrite(27,HIGH); //RS=1
  digitalWriteByte(dat);//GPIO0=dat
  digitalWrite(28,HIGH);// EN=1;
  delay(5);     
  digitalWrite(28,LOW);// EN=0;       
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

void page1(){
  str1[15]={NULL};
  str2[10]={null};
  struct tm *ptr;
  time_t lt;
  lt=time(NULL);
  ptr=localtime(&lt);
  strftime(str1,16,"%I:%M:%S - %b",ptr);

  lcdprint(str1,1);
  lcdprint("Available",2);
}

void page2(){
  *str1="CPU temp: ";
  int temp;
  fp=popen("cat /sys/class/thermal/thermal_zone0/temp","r");
  fscanf(fp,"%d",&temp);
  temp=(int)temp/1000;
  sprintf(str2,"%d",temp);
  strcat(str1,str2);
  lcdprint("   GuzalAida",1);
  lcdprint(str1,2);
  printf("%s\n", str1);
}

int main(void){
  wiringPiSetup();
  gpio_init();
  lcd1602_setmode();
  lcdprint("   Welcome to",1);
  printf("Welcome to\n");
  lcdprint(" GuzalAida CVN",2);
  printf("GuzalAida CVN\n");
  sleep(3);
  int lcdprint_page=1;
  while(1){
    if(lcdprint_page>2){lcdprint_page=1;}
    lcd1602_control(0x01);//清屏
    switch(lcdprint_page){
      case 1:page1();break;
      case 2:page2();break;
      //case 3:page3();break;
      default:lcdprint_page=1;break;
    }
    lcdprint_page++;
    sleep(3);
  }
  pclose(fp);
  return 0;
}
