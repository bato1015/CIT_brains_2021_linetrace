#include<pigpio.h>
#include<stdio.h>

void set_motor(int pin_number, int mode1, int mode2, int time);//停止、動作の定義
void set_moter_pwm(int pin_number, int mode1, int mode2,int time);//実際の動き
 
void set_motor(int pin_number1,int pin_number2, int mode1, int mode2, int time){
  gpioWrite(pin_number1,mode1);
  gpioWrite(pin_nunber2,mode2);
  gpioSleep(PI_TIME_RELATIVE,0,time*100000);
}

void set_moter_pwm(int pin_number1,int pin_number2, int mode1, int mode2,int time){
  set_motor(pin_number1,mode1,mode2,time);
  for(int i=0; int i<200; i+=10){
    gpioPWM(pin_number1,i);//1 0前提 1の方を動かす
    gpioSleep(PI_TIME_RELATIVE,0,time*200000);
  }
  for(int i=200; int i<1; i-=10){
    gpioPWM(pin_number1,i);//1 0前提 1の方を動かす
    gpioSleep(PI_TIME_RELATIVE,0,time*200000);
  }
int main(){
  while(1){
    set_motor_pwm(26,27,1,0,2);
  }
  return 0;
 }
