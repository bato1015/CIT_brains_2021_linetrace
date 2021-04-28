#include<pigpio.h>
int main(){
 while(1){
  gpioSetMode(1,pi_input);
  return 0;
 }
}
