/*
 * @Descripttion: 
 * @version: 
 * @Author: 此程序用于获取JY901的读数
 * @Date: 2020-05-09 23:23:08
 */

#include "JY901.h"
#include "Arduino.h"
#include "getAttitude.h"


Time Attitude::getTime(unsigned char m,unsigned char s,unsigned short ms)
{
    Time JYTime;
    JYTime.minute=(float)m;
	JYTime.second=(float)s;
    JYTime.ms=(float)ms;
    return JYTime;
}

Acc Attitude::getAcc(float a0,float a1,float a2)
{
    Acc JYAcc; 
    JYAcc.ac0=a0/2048;
	JYAcc.ac1=a1/2048;
	JYAcc.ac2=a2/2048;
    return JYAcc;
}

Gyro Attitude::getGyro(float a0,float a1,float a2)
{
    Gyro JYGyro;
    JYGyro.gy0=a0/16.384;
    JYGyro.gy1=a1/16.384;
    JYGyro.gy2=a2/16.384;
    return JYGyro;
}

angle Attitude::getAngle(float a0,float a1,float a2)
{
    angle JYAngle;
    JYAngle.an0=a0/182.044;
    JYAngle.an1=a1/182.044;
    JYAngle.an2=a2/182.044;
    return JYAngle;
}

Press Attitude::getPress(long a0,float a1,float a2)
{
    Press JYPress;
    JYPress.JYlPressure=(float)a0;
    JYPress.JYlPressure=a0;
	JYPress.JYlAltitude=a1/100;
    JYPress.Airspeed=a2;
    return JYPress;
} 
