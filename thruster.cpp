#include "thruster.h"
Servo THRUSTERS[8];
Servo&FORWARD_STARBOARD = THRUSTERS[0];//右舷前
Servo& FORWARD_PORT = THRUSTERS[1];//左舷前
Servo& BOW_STARBOARD = THRUSTERS[2];//右前上下
Servo& BOW_PORT = THRUSTERS[3];//左前上下
Servo& AFT_STARBOARD = THRUSTERS[4];//右后上下
Servo& AFT_PORT = THRUSTERS[5];//左后上下
Servo& TRANS_BOW = THRUSTERS[6];//船头转弯
Servo& TRANS_AFT = THRUSTERS[7];//船尾转弯
//extern int lights[];
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
	//speed1 -= 1500;
	//speed1 /= 7;
	//speed1 += 64;
	//analogWrite(lights[selector], speed1);
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