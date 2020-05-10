/*
 * @Descripttion: 此程序用于从MVPX700读取空速
 * @version: 
 * @Author: Phocidae
 * @Date: 2020-05-09 23:23:08
 */


#ifndef AIRSPEED_h
#define AIRSPEED_h

#include "Arduino.h"

#define airPin A0

class airspeed
{    
public:
    float getOffset();//校准：得到前2秒读数，作为基准点(OFFSET)
    float getAirspeed(float);//输出结果
};

#endif