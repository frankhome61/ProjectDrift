#include "thruster.h"
#include "serial.h"
int lights[] = { 6,9,10,11 };
void setup()
{
	serialInit();
	thrustersInit();
	thrusterTest();
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
