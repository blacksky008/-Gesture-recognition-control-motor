#include <Wire.h>//使用wire.h的库
#include "paj7620.h"//使用额外拓展的Paj7620手势识别的库

#define GES_REACTION_TIME		800//设置反应延时800ms
#define GES_QUIT_TIME			1000//设置退出延时1000ms
volatile char item;//定义item存储读取信息

//初始化
void setup()
{
	Serial.begin(9600);//定义串口波特率为9600
	pinMode(11, INPUT);//定义一个限位开关为输入设备
	pinMode(12, INPUT);//定义另一个限位开关为输入设备
	pinMode(9, OUTPUT);//定义电机一引脚为输出端
	pinMode(10, OUTPUT);//定义另一电机引脚为输出端

	item = Serial.read();//读取串口信息
}
//循环体
void loop()
{
	uint8_t data = 0, data1 = 0, error; //定义数据data，data1，和error

	error = paj7620ReadReg(0x43, 1, &data);//读取0x43位置的手势结果
	if (!error) //如果没有错误，执行
	{
		if(data == GES_UP_FLAG)//信号为上挥动
		{
			delay(GES_REACTION_TIME);//延时800ms反应时间
			paj7620ReadReg(0x43, 1, &data);//赋值
			//执行上升操作
			Serial.println("Up");//打印up
			digitalWrite(9,HIGH);//电机正转
			digitalWrite(10,LOW);//电机正转
		}

		else if(data == GES_DOWN_FLAG)//信号为下挥动
		{
			delay(GES_REACTION_TIME);//延时800ms反应时间
			paj7620ReadReg(0x43, 1, &data);//赋值
			//执行下降操作
			Serial.println("Down");//打印down
			digitalWrite(9,LOW);//电机反转
			digitalWrite(10,HIGH);//电机反转
		}

		else 
		{
			Serial.println("else sign");//打印down
			digitalWrite(9,HIGH);//电机反转
			digitalWrite(10,HIGH);//电机反转
		}

		delay(GES_QUIT_TIME);//延时1000ms
	}


	if (digitalRead(11) == 0)//如果限位开关被触发
	{
		digitalWrite(9,HIGH);//电机停止
		digitalWrite(10,HIGH);//电机停止
	}
	if (digitalRead(12) == 0)//如果限位开关被触发
	{
		digitalWrite(9,HIGH);//电机停止
		digitalWrite(10,HIGH);//电机停止
	}

	while (Serial.available() > 0) {//判断串口是否有信号输入，有则执行switch选择
		switch (item) {//使用switch来判断收到什么信号执行怎样的操作
		case '0'://信号0
			//停止
			digitalWrite(9,HIGH);//电机停止
			digitalWrite(10,HIGH);//电机停止
			break;
			//电机左转
		case '1':
			digitalWrite(9,HIGH);//电机左转
			digitalWrite(10,LOW);//电机左转
			break;
			//电机右转
		case '2':
			digitalWrite(9,LOW);//电机右转
			digitalWrite(10,HIGH);//电机右转
			break;
			//收到干扰信号时，保证电机停止状态
		default:
			digitalWrite(9,HIGH);//电机停止
			digitalWrite(10,HIGH);//电机停止
			break;
		}
	}

}
