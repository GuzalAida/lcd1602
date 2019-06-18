/*
 * Author: Mardan
 * Date: 2019.6.10
 * Project: GuzalAida
 */


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>

#define uchar unsigned char

//Global variable
FILE *fp;
char nowtime[16];
char cpu_load[16];

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
  int lcdprint_page=1;
  while(1){
    if(lcdprint_page>3){lcdprint_page=1;}
    lcd1602_control(0x01);//清屏
    switch(lcdprint_page){
      case 1:page1(argv[1]);break;
      //case 2:page2();break;
      //case 3:page3();break;
      default:lcdprint_page=1;break;
    }
    lcdprint_page++;
    sleep(3);
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
  fscanf(fp,"%s",&cpu_load);
  lcdprint(cpu_load,2);
  pclose(fp);

}

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
