/*
 * @Descripttion: 此程序设定Timer4控制的PIN6,7,8输出f=500Hz的PWM & Timer2控制的PIN9,10;
 * @version: 
 * @Author: Phocidae
 * @Date: 2020-05-09 23:23:08
 */

#include "motors.h"
#include "Arduino.h"

void motors::setTimer4()
{
    pinMode(m1OP,OUTPUT); 
    pinMode(m2OP,OUTPUT);
    pinMode(m3OP,OUTPUT);

    TCCR4A=_BV(COM4A1)|_BV(COM4B1)| _BV(COM4C1)|_BV(WGM42)| _BV(WGM40);//Fast PWM with 9bit
    TCCR4B=_BV(CS41)|_BV(CS40);//500Hz，周期为4098us，占空比区间为[0.244,0.366,0.488]
    OCR4A=124;//brushless
    OCR4B=187;//brush(无需行程设定） (187~249)
    OCR4C=187;//brush
}

void motors::setTimer2()
{
    pinMode(s1OP,OUTPUT);
    pinMode(s2OP,OUTPUT);

    TCCR2A = _BV(COM2A0) | _BV(COM2B1) |  _BV(WGM20); 
    TCCR2B = _BV(WGM22) | _BV(CS22) |_BV(CS21)| _BV(CS20);
    OCR2A = 156;//50Hz
    OCR2B =156;
}    

Signal motors::readSignal()
{
    Signal planSignal;
    planSignal.m1Re=pulseIn(m1RP,HIGH,20);//读取，pulseIn()的完整形式应为pulseIn(Pin,HIGH/LOW,timeout),timeout (optional): the number of microseconds to wait for the pulse to be completed: the function returns 0 if no complete pulse was received within the timeout. Default is one second (unsigned long).timeout需用示波器测得
    planSignal.m23Re=pulseIn(m23RP,HIGH,20);
    planSignal.s1Re=pulseIn(s1RP,HIGH,20);
    planSignal.s2Re=pulseIn(s2RP,HIGH,20);
    planSignal.d23Re=pulseIn(d23P,HIGH,20);
    return planSignal;
}

void motors::Output(struct Signal mysignal)
{
    struct Signal planSignal=mysignal;
    m1O=map(planSignal.m1Re,986,1964,135,233);//电机输出,此处的135和233为校正值
    if (planSignal.d23Re>1475)//假设微调旋钮中值为1480，>1480：右边转速较快，<1480：左边转速较快
    {
        m3O=map(planSignal.m23Re,986,1964,195,233);//此处的195为修正值
        m2O=m3O-0.9*fabs((map(planSignal.d23Re,986,1964,195,233)-214));
    }
    else
    {
        m2O=map(planSignal.m23Re,986,1964,195,233);//此处的195为修正值
        m3O=m2O-0.9*fabs((map(planSignal.d23Re,986,1964,195,233)-214));
    }
    
    s1O=map(planSignal.s1Re,986,1964,1,20);//舵机输出
    s2O=map(planSignal.s2Re,986,1964,1,20);

    //该函数必须以以下部分结尾
    OCR4A=m1O;
    OCR4B=m2O;
    OCR4C=m3O;
    OCR2A=s1O;
    OCR2B=s2O;
}
