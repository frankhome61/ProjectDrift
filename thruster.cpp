#include "thruster.h"
Servo THRUSTERS[8];
Servo&FORWARD_STARBOARD = THRUSTERS[0];//����ǰ
Servo& FORWARD_PORT = THRUSTERS[1];//����ǰ
Servo& BOW_STARBOARD = THRUSTERS[2];//��ǰ����
Servo& BOW_PORT = THRUSTERS[3];//��ǰ����
Servo& AFT_STARBOARD = THRUSTERS[4];//�Һ�����
Servo& AFT_PORT = THRUSTERS[5];//�������
Servo& TRANS_BOW = THRUSTERS[6];//��ͷת��
Servo& TRANS_AFT = THRUSTERS[7];//��βת��
extern int lights[];
void thrustersInit()
{
	for (int i = 0; i < 8; i++)
	{
		THRUSTERS[i].attach(i + 2);//Actual Arduino pin numbers are offset by 2
		THRUSTERS[i].writeMicroseconds(1500);//Write stop freq to initialize
	}
}
int getThrusterServoMs(unsigned char in_data)
{
	int speed1 = (unsigned char)(in_data << 1) >> 1;
	speed1 -= 64;
	speed1 *= 7;
	speed1 += 1500;
	return speed1;
}
void sendThrusterSpeed(unsigned char selector, short speed1)
{
	//TTTTTTTTTTTTTTTTOOOOOOOOOOOOOOOODDDDDDDDDDDDDDDDDDDOOOOOOOOOOOOO
	//4debug!!!!!!!!!!!
	analogWrite(lights[selector], (speed1-1500)/7+64);
	//THRUSTERS[selector].writeMicroseconds(speed1);
	return;
}
void thrusterTest()
{
	for (int i = 0; i < 8; i++)
	{
		THRUSTERS[i].writeMicroseconds(1700);
		delay(3000);
		THRUSTERS[i].writeMicroseconds(1500);
	}
	return;
}
