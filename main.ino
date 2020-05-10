/*
 * @Author: Phocidae
 * @Date: 2020-05-09 23:23:08
 * @Description: 适用于第一版PCB板
 * @FilePath: \main\main.ino
 */

#include <Wire.h>

#include "motors.h"
#include "JY901.h"
#include "getAttitude.h"
#include "airspeed.h"
#include "APC220.h"


/*class*/
motors   planMotors;
Attitude planAttitude;
airspeed planAirspeed;
APC220   planData;

float OFFSET;

void setup()
{
    planData.setAPC220();    

    planMotors.setTimer4();
    planMotors.setTimer2();
    
    Serial.begin(9600);//for JY901
    Serial3.begin(9600);//for APC220

    OFFSET=planAirspeed.getOffset();

    planMotors.planSignal={986,986,1475,1475,1475};//接收机信号初值    
}



void loop()
{   
    //控制电机部分
    planMotors.planSignal=planMotors.readSignal();
    planMotors.Output(planMotors.planSignal);


    //for JY901
    while (Serial.available()) 
{
    JY901.CopeSerialData(Serial.read()); //Call JY901 data cope function
}   

    //读取JY901数据部分
    planAttitude.JYTime=planAttitude.getTime(JY901.stcTime.ucMinute,(float)JY901.stcTime.ucSecond,(float)JY901.stcTime.usMiliSecond);
    planAttitude.JYAcc=planAttitude.getAcc((float)JY901.stcAcc.a[0],(float)JY901.stcAcc.a[1],(float)JY901.stcAcc.a[2]);
    planAttitude.JYGyro=planAttitude.getGyro((float)JY901.stcGyro.w[0],(float)JY901.stcGyro.w[1],(float)JY901.stcGyro.w[2]);
    planAttitude.JYAngle=planAttitude.getAngle((float)JY901.stcAngle.Angle[0],(float)JY901.stcAngle.Angle[1],(float)JY901.stcAngle.Angle[2]);

    //demo for Airspeed
    float airSpeed=planAirspeed.getAirspeed(OFFSET);

    planAttitude.JYPress=planAttitude.getPress(JY901.stcPress.lPressure,(float)JY901.stcPress.lAltitude,airSpeed);


    //发送数据
    planData.comTime(planAttitude.JYTime);
    planData.comAcc(planAttitude.JYAcc);
    planData.comGyro(planAttitude.JYGyro);
    planData.comAngle(planAttitude.JYAngle); 
    planData.comPress(planAttitude.JYPress);

/*  
    //frequncy test
    unsigned long starttime;
    unsigned long stoptime;
    unsigned long looptime;
    starttime = 1000*millis();
    stoptime = 1000*millis();
    looptime = stoptime - starttime;
    Serial.print("Time(us)="); Serial.println(looptime);

    //demo for JY901
    Serial.print("Acc0=");Serial.println((float)planAttitude.JYAcc.ac0);
    Serial.print("Acc1=");Serial.println((float)planAttitude.JYAcc.ac1);
    Serial.print("Acc2=");Serial.println((float)planAttitude.JYAcc.ac2);

    //demo for Airspeed
    Serial.print("Airspeed="); Serial.println(airSpeed);  //若显示Airspeed为"nan",表示传感器安装错误
*/
}
