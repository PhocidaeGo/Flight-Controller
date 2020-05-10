/*
 * @Descripttion: 此程序用于从MVPX700读取空速
 * @version: 
 * @Author: Phocidae
 * @Date: 2020-05-09 23:23:08
 */

#include "Arduino.h"
#include "airspeed.h"

float airspeed::getOffset()
{
    int sum = 0;
    int sensorValue = 0;
    for (int i = 0; i < 20; i++)
    {
        sensorValue=analogRead(airPin)-512;
        sum=sum+sensorValue;
        delay(100);
    }
    float OFFSET=sum/20;
    return OFFSET;
}

float airspeed::getAirspeed(float OFFSET)
{
    float sensorValue=analogRead(airPin)-OFFSET;
    float airspeed=sqrt(7.55*sensorValue-3866.976);
    return airspeed;
}