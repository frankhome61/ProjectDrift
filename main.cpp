#include "stdio.h"
#include "serial.h"
#include "thruster.h"
int main()
{


	serialInit();
	processInPackage((unsigned char)2);
	processInPackage((unsigned char)255);

	/*
	unsigned char input = 255;
	unsigned char input2 = 47;
	if (input < (unsigned char)128)
	{



		printf("id:--->%d\n", (unsigned char)input);

	}
	else
	{
		short speed = (unsigned char)(input << 1) >> 1;
		speed -= 64;
		speed *= 7;
		speed += 1500;

		printf("num:-------->%d\n", speed);
	}*/
	scanf_s("%d", 1);
}

