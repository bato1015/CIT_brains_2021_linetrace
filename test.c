#include<stdio.h>
#include<pigpio.h>
int main(){
  if (gpioInitialise() < 0){
  printf("1");
  }else{
  printf("2");
  }
  gpioSetMode(26,PI_INPUT);
  while(1){
    gpioWrite(26,1);
  }
  return 0;
}

