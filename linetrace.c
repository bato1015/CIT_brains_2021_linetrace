//--------------------
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <time.h>
//--------------------
//ピン番号定義
#define MOTOR_R1 19
#define MOTOR_R2 13
#define MOTOR_L1 18
#define MOTOR_L2 12
#define LINE_1 27
#define LINE_2 17
//--------------------
#define HIGH 0x1
#define LOW 0x0
#define SECOND_TO_MICRO 1000000
#define PERCENT_TO_PWM 2.55
//--------------------
//プロトタイプ宣言
void gpio_setup();                   //GPIO設定
void motor_stop(int, int, int, int); //停止
void motor_brake(int, int);          //ブレーキ
void motor_move(int, int, int);      //回転
void motor_move2(int, int, int);     //回転
//--------------------
int main()
{
    if (gpioInitialise() < 0)
    {
        printf("pigpio initialisation failed.");
        return 1;
    }
    else
    {
        printf("pigpio initialised okay.");
    }

    gpio_setup();

    //入力テスト---------------------------------------------------------------------
    /*
  while(1)
  {
    printf("LINE INPUT %d %d \n", gpioRead(LINE_1), gpioRead(LINE_2));
       gpioDelay(0.05 * SECOND_TO_MICRO);
  }
*/
  //PWM出力テスト-----------------------------------------------
  /*
  int i = 0;

  for (; i < 100; i++)
  {
    motor_move(MOTOR_R1, MOTOR_R2, i);
    motor_move2(MOTOR_L1, MOTOR_L2, i);
    gpioDelay(0.05 * SECOND_TO_MICRO);
  }

  for (; i > -100; i--)
  {
    motor_move(MOTOR_R1, MOTOR_R2, i);
    motor_move2(MOTOR_L1, MOTOR_L2, i);
    gpioDelay(0.05 * SECOND_TO_MICRO);
  }

  motor_stop(MOTOR_R1, MOTOR_R2, MOTOR_L1, MOTOR_L2);
  gpioDelay(SECOND_TO_MICRO);
<<<<<<< HEAD
  
  */
//-----------------------------

//ライントレース---------------------------------------------------
    while (1)
    {
	gpioSleep(PI_TIME_RELATIVE, 0, 050000);
        printf("LINE INPUT %d %d \n", gpioRead(LINE_1), gpioRead(LINE_2));
        if (gpioRead(LINE_1) == 0 && gpioRead(LINE_2) == 1)
        {
            motor_move(MOTOR_R1, MOTOR_R2, 0);
            motor_move2(MOTOR_L1, MOTOR_L2, 60);
        }
        if (gpioRead(LINE_1) == 1 && gpioRead(LINE_2) == 0)
        {
            motor_move(MOTOR_R1, MOTOR_R2, 70);
            motor_move2(MOTOR_L1, MOTOR_L2, 0);
        }
        if (gpioRead(LINE_1) == 1 && gpioRead(LINE_2) == 1)
        {
            motor_move(MOTOR_R1, MOTOR_R2, 50);
            motor_move2(MOTOR_L1, MOTOR_L2, 50);
        }
        if (gpioRead(LINE_1) == 0 && gpioRead(LINE_2) == 0)
        {
            motor_move(MOTOR_R1, MOTOR_R2, 50);
            motor_move2(MOTOR_L1, MOTOR_L2, 50);
        }
    }
    //PWMテスト時はここから上までコメントアウト------------------
    gpioTerminate();
    return 0;
}

//GPIO設定
void gpio_setup()
{
    gpioSetMode(MOTOR_R1, PI_OUTPUT);
    gpioSetMode(MOTOR_R2, PI_OUTPUT);
    gpioSetMode(MOTOR_L1, PI_OUTPUT);
    gpioSetMode(MOTOR_L2, PI_OUTPUT);

    gpioSetMode(LINE_1, PI_INPUT);
    gpioSetMode(LINE_2, PI_INPUT);
}
//--------------------
//停止
void motor_stop(int pin_num1, int pin_num2, int pin_num3, int pin_num4)
{
    gpioWrite(pin_num1, LOW);
    gpioWrite(pin_num2, LOW);
    gpioWrite(pin_num3, LOW);
    gpioWrite(pin_num4, LOW);
}
//--------------------
//ブレーキ
void motor_brake(int pin_num1, int pin_num2)
{
    gpioWrite(pin_num1, HIGH);
    gpioWrite(pin_num2, HIGH);
}
//--------------------
//回転
void motor_move(int pin_num1, int pin_num2, int speed)
{
    if (speed < 0)
    {
        gpioPWM(pin_num1, abs(speed) * PERCENT_TO_PWM);
        gpioWrite(pin_num2, LOW);
    }
    else if (speed > 0)
    {
        gpioWrite(pin_num1, LOW);
        gpioPWM(pin_num2, speed * PERCENT_TO_PWM);
    }
    else
    {
        gpioWrite(pin_num1, LOW);
        gpioWrite(pin_num2, LOW);
    }
}
void motor_move2(int pin_num3, int pin_num4, int speed)
{
    if (speed > 0)
    {
        gpioPWM(pin_num3, speed * PERCENT_TO_PWM);
        gpioWrite(pin_num4, LOW);
    }
    else if (speed < 0)
    {
        gpioWrite(pin_num3, LOW);
        gpioPWM(pin_num4, abs(speed) * PERCENT_TO_PWM);
    }
    else
    {
        gpioWrite(pin_num3, LOW);
        gpioWrite(pin_num4, LOW);
    }
}
