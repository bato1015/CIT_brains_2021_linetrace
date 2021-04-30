#include<stdio.h>
#include<pigpio.h>
int main(){
  if (gpioInitialise() < 0){
  printf("1");
  }else{
  printf("2");
  }
  gpioSetMode(26,PI_INPUT);
  /*while(1){
    //gpioWrite(26,0);
    gpioPWM(26,100);
  }*/
  for(int i=0;i<255;i=i+i*10){
  gpioPWM(26,i);
  }
  return 0;
}

