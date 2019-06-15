/*
 * Author: Mardan
 * Date: 2019.6.13
 * Project: GuzalAida
 */


#include <wiringPi.h>


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
