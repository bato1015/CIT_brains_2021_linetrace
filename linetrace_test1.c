#include <stdio.h>
#include <pigpio.h>
#define MOTOR_R1 13 //GPIO13 PIN33
#define MOTOR_R2 19 //GPIO19 PIN35
#define MOTOR_L1 12 //GPIO12 PIN32
#define MOTOR_L2 18 //GPIO18 PIN12
#define SENSOR_R 9  //GPIO9 PIN21
#define SENSOR_L 11 //GPIO11 PIN23
#define SECOND_TO_MICRO 1000000
#define HIGH 0x1
#define LOW 0x0

void move_motorR(int pin_num1, int pin_num2, int speed)
{
    //speed : -255~255
    gpioSetMode(pin_num1, PI_INPUT);
    gpioSetMode(pin_num2, PI_INPUT);
    gpioWrite(pin_num1, LOW);//正転
    gpioWrite(pin_num2, HIGH);
    gpioPWM(pin_num1, speed);
    gpioPWM(pin_num2, speed);
}
void move_motorL(int pin_num3, int pin_num4, int speed)
{
    //speed : -255~255
    gpioSetMode(pin_num3, PI_INPUT);
    gpioSetMode(pin_num4, PI_INPUT);
    gpioWrite(pin_num3, HIGH);//正転
    gpioWrite(pin_num4, LOW);
    gpioPWM(pin_num3, speed);
    gpioPWM(pin_num4, speed);
}

int main()
{
    if (gpioInitialise() < 0)
    {
        printf("pigpio initialisation failed.\n");
        return 1;
    }
    else
        printf("pigpio initialised okay.\n");

    while (1)
    {
        if (gpioRead(SENSOR_R) == 1 && gpioRead(SENSOR_L) == 1)
        {
            printf("All OK!\n");
            Write:
            move_motorR(MOTOR_R1, MOTOR_R2, 200); // //speed (ここでいうi)は-255~255の範囲
            //gpioSleep(PI_TIME_RELATIVE, 0, SECOND_TO_MICRO * 1);
            move_motorL(MOTOR_L1, MOTOR_L2, 200); // //speed (ここでいうi)は-255~255の範囲
            //gpioSleep(PI_TIME_RELATIVE, 0, SECOND_TO_MICRO * 1);
            //sleep(2);
            gpioDelay(0.05 * SECOND_TO_MICRO);
        }
        if (gpioRead(SENSOR_R) == 0 && gpioRead(SENSOR_L) == 1)
        {
            printf("Sensor_R is Fall\n");
            move_motorR(MOTOR_R1, MOTOR_R2, 100); // //speed (ここでいうi)は-255~255の範囲
            //gpioSleep(PI_TIME_RELATIVE, 0, SECOND_TO_MICRO * 1);
            move_motorL(MOTOR_L1, MOTOR_L2, 200); // //speed (ここでいうi)は-255~255の範囲
            //gpioSleep(PI_TIME_RELATIVE, 0, SECOND_TO_MICRO * 1);
            //sleep(2);
            gpioDelay(0.05 * SECOND_TO_MICRO);
        }
        if (gpioRead(SENSOR_R) == 1 && gpioRead(SENSOR_L) == 0)
        {
            printf("Sensor_L is Fall\n");
            move_motorR(MOTOR_R1, MOTOR_R2, 200); // //speed (ここでいうi)は-255~255の範囲
            //gpioSleep(PI_TIME_RELATIVE, 0, SECOND_TO_MICRO * 1);
            move_motorL(MOTOR_L1, MOTOR_L2, 100); // //speed (ここでいうi)は-255~255の範囲
            //gpioSleep(PI_TIME_RELATIVE, 0, SECOND_TO_MICRO * 1);
            //sleep(2);
            gpioDelay(0.05 * SECOND_TO_MICRO);
        }
        if (gpioRead(SENSOR_R) && gpioRead(SENSOR_L) == 0)
        {
            printf("All Fall\n");
            move_motorR(MOTOR_R1, MOTOR_R2, 0); // //speed (ここでいうi)は-255~255の範囲
            //gpioSleep(PI_TIME_RELATIVE, 0, SECOND_TO_MICRO * 1);
            move_motorL(MOTOR_L1, MOTOR_L2, 0); // //speed (ここでいうi)は-255~255の範囲
            //gpioSleep(PI_TIME_RELATIVE, 0, SECOND_TO_MICRO * 1);
            //sleep(2);
            gpioDelay(0.05 * SECOND_TO_MICRO);
        }
    }
    gpioTerminate();
    return 0;
}