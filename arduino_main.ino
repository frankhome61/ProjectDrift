#include "thruster.h"
#include "serial.h"
#include <Servo.h>
int lights[] = { 6,3,5,11 };
void setup()
{
	serialInit();
	//thrustersInit();
	//thrusterTest();
}
void loop()
{
	if (Serial.available() > 0)
	{
		byte buffer;
		while (Serial.available())
		{
			buffer = Serial.read();
		}
		processInPackage(buffer);
	}
}
