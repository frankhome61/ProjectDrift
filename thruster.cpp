#include "thruster.h"
int getThrusterServoMs(unsigned char in_data)
{
	int speed = (unsigned char)(in_data << 1) >> 1;
	speed -= 64;
	speed *= 7;
	speed += 1500;
	return speed;
}
void sendThrusterSpeed(unsigned char selector, short speed)
{
	//
	return;
}