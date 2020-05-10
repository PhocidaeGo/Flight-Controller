/*
 * @Descripttion: 此程序设定Timer4控制的PIN6,7,8输出f=500Hz的PWM & Timer2控制的PIN9,10;
 * @version: 
 * @Author: Phocidae
 * @Date: 2020-05-09 23:23:08
 */

#ifndef MOTORS_h
#define MOTORS_h

#include "Arduino.h"

//PWM Out_PIN
#define m1OP 6//brushless
#define m2OP 7//brush
#define m3OP 8
#define s1OP 9//Servo
#define s2OP 10

//Read signal from remote
#define m1RP  36
#define m23RP 34
#define s1RP  32//垂直尾翼
#define s2RP  30//水平尾翼
#define d23P  28//2号、3号电机的速度差


struct Signal
{
    int m1Re;
    int m23Re;
    int s1Re;
    int s2Re;
    int d23Re;
};

class motors
{
    private:
      int m1O=195;
      int m2O=195;
      int m3O=195;
      int s1O=5;//舵机的零值为90度
      int s2O=5;     

    public:
      struct Signal planSignal;

      //设置寄存器
      void setTimer4();//控制PIN6、7、8
      void setTimer2();//控制PIN9、10

      Signal readSignal();//读取遥控器信号
      void Output(struct Signal);

};

#endif
