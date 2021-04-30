#include<stdio.h>
#include<pigpio.h>
int main(){
  if (gpioInitialise() < 0){
  printf("1");
  }else{
  printf("2");
  }
  gpioSetMode(26,PI_INPUT);
  int i=10;
  int d=0;
  
  while(1){
    gpioPWM(26,i);
    gpioSleep(PI_TIME_RELATIVE,0,500000);
    d+=r;
    if(d>=255||d<=0){
      r*=-1;
    }
  }
  /*while(1){
    //gpioWrite(26,0);
    gpioPWM(26,i);
    if(i=250){
    i=i-250;
    }
    gpioSleep(PI_TIME_RELATIVE,0,500000);
    i=i+10;
  }
  /*for(int i=0;i<255;i+=10){
  gpioPWM(26,i);
  wait(1);
  }*/
  return 0;
}

