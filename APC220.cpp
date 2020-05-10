/*
 * @Descripttion: 此程序用于使用APC220回传数据
 * @version: 
 * @Author: Phocidae
 * @Date: 2020-05-09 23:23:08
 */

#include "Arduino.h"
#include "APC220.h"

void APC220::setAPC220()
{
    Serial3.begin(9600);
    Serial3.println("APC220 initiated");
    Serial3.println("please wait 3s");
}

/*至少需要传输6组共15个数据,默认回传保留3位小数*/
void APC220::comTime(struct Time planTime)
{
    Serial3.println(planTime.minute);
    Serial3.println(planTime.second);
    Serial3.println(planTime.ms);
}

void APC220::comAcc(struct Acc planAcc)
{
    Serial3.println(planAcc.ac0);
    Serial3.println(planAcc.ac1);
    Serial3.println(planAcc.ac2);
}

void APC220::comGyro(struct Gyro planGyro)
{
    Serial3.println(planGyro.gy0);
    Serial3.println(planGyro.gy1);
    Serial3.println(planGyro.gy2);
}

void APC220::comAngle(struct angle planAngle)
{
    Serial3.println(planAngle.an0);
    Serial3.println(planAngle.an1);
    Serial3.println(planAngle.an2);
}

void APC220::comPress(struct Press planPress)
{
    Serial3.println(planPress.JYlPressure);
    Serial3.println(planPress.JYlAltitude);
    Serial3.println(planPress.Airspeed);
}
