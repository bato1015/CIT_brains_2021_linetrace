#include<stdio.h>
#include<pigpio.h>
int main(){
  if (gpioInitialise() < 0){
  printf("1");
  }else{
  printf("2");
  }
  gpioSetMode(int outpin=17,PI_INPUT);
  return 0;
}

