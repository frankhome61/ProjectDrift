#include "serial.h"
#include "thruster.h"
unsigned char switchCommandType(unsigned char package)

{

	if (package > 128)

	{

		return 'e';

	}

	else if (package < 8)

	{

		return 't';

	}

	else

	{

		if (package == 'u')

		{

			return 'u';

		}

		// todos

	}



}

unsigned char switchPackageType(unsigned char package)

{

	if ((unsigned char)(package >> 7))

	{

		return 'i';//i for instruction

	}

	else

	{

		return 's';//s for selector

	}



}



void processInPackage(unsigned char package)

{

	static unsigned char lastSelector;

	short speed;

	switch (switchPackageType(package))

	{

	case 's':// s 4 selector

			 //printf("it is a selector\n");

		lastSelector = package; break;

	case 'i':// i 4 instruction

			 //printf("it is a ins\n");

		switch (switchCommandType(lastSelector))

		{

		case 't': // t 4 thruster

				  //printf("it is for thurster");

			speed = getThrusterServoMs(package);

			//printf("---speed is %d \n", speed);

			sendThrusterSpeed(lastSelector, speed);

			break;

		case 'u':

			//printf("this is a extra instruction");

			break;

		}



		break;

	default:

		break;

	}

}

void serialInit()

{

	processInPackage('u');

}
