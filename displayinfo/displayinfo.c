/*
 * Author: Mardan
 * Date: 2019.6.10
 * Project: GuzalAida
 */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "getinfo.h"
#include "lcd1602.h"
#define uchar unsigned char


FILE *fp;

void page1();
void page2();
void page3();

int main(void){
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
      case 1:page1();break;
      case 2:page2();break;
      case 3:page3();break;
      default:lcdprint_page=1;break;
    }
    lcdprint_page++;
    sleep(3);
  }
  return 0;
}

void page1(){

}
void page2(){

}
void page3(){
  
}