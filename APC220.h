/*
 * @Descripttion: 此程序用于使用APC220回传数据
 * @version: 
 * @Author: Phocidae
 * @Date: 2020-05-09 23:23:08
 */


#ifndef APC220_h
#define APC220_h

#include "Arduino.h"
#include "getAttitude.h"

//APC220使用Serial3

class APC220
{
    public:
      void setAPC220();//初始化APC220
      void comTime(struct Time);
      void comAcc(struct Acc);
      void comGyro(struct Gyro);
      void comAngle(struct angle);
      void comPress(struct Press);
};

#endif 
