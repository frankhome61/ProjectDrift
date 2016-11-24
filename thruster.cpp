#include "thruster.h"
#include "Arduino.h"
extern int lights[];
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
	//
        speed1-=1500;
        speed1/=7;
        speed1+=64;
        analogWrite(lights[selector],speed1);
	return;
}
