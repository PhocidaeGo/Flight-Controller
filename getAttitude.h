/*
 * @Descripttion: 
 * @version: 
 * @Author: 此程序用于获取JY901的读数
 * @Date: 2020-05-09 23:23:08
 */

#ifndef ATTITUDE_h
#define ATTITUDE_h

#include "Arduino.h"
#include "JY901.h"
#include <Wire.h>

//电路板上JY901接TX0和RX0

struct Time
{
	float minute;
	float second;
    float ms;
};

struct Acc
{
	float ac0;
	float ac1;
	float ac2;
};

struct Gyro//陀螺仪
{
    float gy0;
    float gy1;
    float gy2;
};

struct angle
{
    float an0;
    float an1;
    float an2;
};

struct Press
{
	float JYlPressure;
	float JYlAltitude;
    float Airspeed;//NOTICE:为发送数据方便，Airspeed并入该结构体
};

class Attitude 
{
    public:
      struct Time  JYTime;
      struct Acc   JYAcc;
      struct Gyro  JYGyro;
      struct angle JYAngle;
      struct Press JYPress; 

      Time  getTime(unsigned char, unsigned char, short unsigned int);
      Acc   getAcc(float,float,float);
      Gyro  getGyro(float,float,float);
      angle getAngle(float,float,float);
      Press getPress(long,float,float);//Airspeed作为第三个参数
};

#endif
