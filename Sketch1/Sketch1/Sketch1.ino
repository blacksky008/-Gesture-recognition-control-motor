#include <Wire.h>//ʹ��wire.h�Ŀ�
#include "paj7620.h"//ʹ�ö�����չ��Paj7620����ʶ��Ŀ�

#define GES_REACTION_TIME		800//���÷�Ӧ��ʱ800ms
#define GES_QUIT_TIME			1000//�����˳���ʱ1000ms
volatile char item;//����item�洢��ȡ��Ϣ

//��ʼ��
void setup()
{
	Serial.begin(9600);//���崮�ڲ�����Ϊ9600
	pinMode(11, INPUT);//����һ����λ����Ϊ�����豸
	pinMode(12, INPUT);//������һ����λ����Ϊ�����豸
	pinMode(9, OUTPUT);//������һ����Ϊ�����
	pinMode(10, OUTPUT);//������һ�������Ϊ�����

	item = Serial.read();//��ȡ������Ϣ
}
//ѭ����
void loop()
{
	uint8_t data = 0, data1 = 0, error; //��������data��data1����error

	error = paj7620ReadReg(0x43, 1, &data);//��ȡ0x43λ�õ����ƽ��
	if (!error) //���û�д���ִ��
	{
		if(data == GES_UP_FLAG)//�ź�Ϊ�ϻӶ�
		{
			delay(GES_REACTION_TIME);//��ʱ800ms��Ӧʱ��
			paj7620ReadReg(0x43, 1, &data);//��ֵ
			//ִ����������
			Serial.println("Up");//��ӡup
			digitalWrite(9,HIGH);//�����ת
			digitalWrite(10,LOW);//�����ת
		}

		else if(data == GES_DOWN_FLAG)//�ź�Ϊ�»Ӷ�
		{
			delay(GES_REACTION_TIME);//��ʱ800ms��Ӧʱ��
			paj7620ReadReg(0x43, 1, &data);//��ֵ
			//ִ���½�����
			Serial.println("Down");//��ӡdown
			digitalWrite(9,LOW);//�����ת
			digitalWrite(10,HIGH);//�����ת
		}

		else 
		{
			Serial.println("else sign");//��ӡdown
			digitalWrite(9,HIGH);//�����ת
			digitalWrite(10,HIGH);//�����ת
		}

		delay(GES_QUIT_TIME);//��ʱ1000ms
	}


	if (digitalRead(11) == 0)//�����λ���ر�����
	{
		digitalWrite(9,HIGH);//���ֹͣ
		digitalWrite(10,HIGH);//���ֹͣ
	}
	if (digitalRead(12) == 0)//�����λ���ر�����
	{
		digitalWrite(9,HIGH);//���ֹͣ
		digitalWrite(10,HIGH);//���ֹͣ
	}

	while (Serial.available() > 0) {//�жϴ����Ƿ����ź����룬����ִ��switchѡ��
		switch (item) {//ʹ��switch���ж��յ�ʲô�ź�ִ�������Ĳ���
		case '0'://�ź�0
			//ֹͣ
			digitalWrite(9,HIGH);//���ֹͣ
			digitalWrite(10,HIGH);//���ֹͣ
			break;
			//�����ת
		case '1':
			digitalWrite(9,HIGH);//�����ת
			digitalWrite(10,LOW);//�����ת
			break;
			//�����ת
		case '2':
			digitalWrite(9,LOW);//�����ת
			digitalWrite(10,HIGH);//�����ת
			break;
			//�յ������ź�ʱ����֤���ֹͣ״̬
		default:
			digitalWrite(9,HIGH);//���ֹͣ
			digitalWrite(10,HIGH);//���ֹͣ
			break;
		}
	}

}
