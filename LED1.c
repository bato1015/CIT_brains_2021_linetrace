#include<pigpio.h>
#include<stdio.h>
int outputpin=17;
int PI_OITPUT=1;
int main(){
  if (gpioInitialise() < 0){
  }else{
  }
  int gpioSetMode(outputpin,PI_OUTPUT);
  gpioTerminate();
  return 0;
}
