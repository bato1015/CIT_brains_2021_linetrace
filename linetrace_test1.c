#include <stdio.h>
#include <pigpio.h>
#define MOTOR_R1 13 //GPIO13 PIN33
#define MOTOR_R2 19 //GPIO19 PIN35
#define MOTOR_L1 12 //GPIO12 PIN32
#define MOTOR_L2 18 //GPIO18 PIN12
#define SENSOR_R 9  //GPIO9 PIN21
#define SENSOR_L 11 //GPIO11 PIN23

void move_motor(int pin_num1, int pin_num2, int speed)
{
    //speed : -255~255
    gpioSetMode(pin_num1, PI_OUTPUT);
    gpioSetMode(pin_num2, PI_OUTPUT);
    gpioPWM(pin_num1, speed);
    gpioPWM(pin_num2, speed);
}

int main()
{
    if (gpioInitialise() < 0)
        printf("pigpio initialisation failed.");
    else
        printf("pigpio initialised okay.");
    sleep(10);
    while (1)
    {
        if (gpioRead(SENSOR_R) && gpioRead(SENSOR_L) == 1)
        {
            move_motor(MOTOR_R1, MOTOR_R2, 200); // //speed (ここでいうi)は-255~255の範囲
            gpioSleep(PI_TIME_RELATIVE, 0, 1000000 * 1);
            move_motor(MOTOR_L1, MOTOR_L2, -200); // //speed (ここでいうi)は-255~255の範囲
            gpioSleep(PI_TIME_RELATIVE, 0, 1000000 * 1);
            sleep(2);
        }
        if (gpioRead(SENSOR_R) == 0 && gpioRead(SENSOR_L) == 1)
        {
            move_motor(MOTOR_R1, MOTOR_R2, 100); // //speed (ここでいうi)は-255~255の範囲
            gpioSleep(PI_TIME_RELATIVE, 0, 1000000 * 1);
            move_motor(MOTOR_L1, MOTOR_L2, -200); // //speed (ここでいうi)は-255~255の範囲
            gpioSleep(PI_TIME_RELATIVE, 0, 1000000 * 1);
            sleep(2);
        }
        if (gpioRead(SENSOR_R) == 1 && gpioRead(SENSOR_L) == 0)
        {
            move_motor(MOTOR_R1, MOTOR_R2, 200); // //speed (ここでいうi)は-255~255の範囲
            gpioSleep(PI_TIME_RELATIVE, 0, 1000000 * 1);
            move_motor(MOTOR_L1, MOTOR_L2, -100); // //speed (ここでいうi)は-255~255の範囲
            gpioSleep(PI_TIME_RELATIVE, 0, 1000000 * 1);
            sleep(2);
        }
        if (gpioRead(SENSOR_R) && gpioRead(SENSOR_L) == 0)
        {
            move_motor(MOTOR_R1, MOTOR_R2, 0); // //speed (ここでいうi)は-255~255の範囲
            gpioSleep(PI_TIME_RELATIVE, 0, 1000000 * 1);
            move_motor(MOTOR_L1, MOTOR_L2, 0); // //speed (ここでいうi)は-255~255の範囲
            gpioSleep(PI_TIME_RELATIVE, 0, 1000000 * 1);
            sleep(2);
        }
    }
    return 0;
}