#include <iostream>
#include <wiringPi.h>
#include <unistd.h>

int main()
{

	wiringPiSetup ();

	int MODE2 = 7;
	int MODE1 = 0;
	int MODE0 = 2;
	int STEP = 3;
	int nENBL = 12;
	int DIR = 13;
	int DECAY = 14;
	int nSLEEP = 30;
	int nHOME = 21;
	int nFAULT = 22;


        pinMode (MODE2, OUTPUT);
        pinMode (MODE1, OUTPUT);
        pinMode (MODE0, OUTPUT);
        pinMode (STEP, OUTPUT);
        pinMode (nENBL, OUTPUT);
        pinMode (DIR, OUTPUT);
        pinMode (DECAY, OUTPUT);
        pinMode (nSLEEP, OUTPUT);
        pinMode (nHOME, INPUT);
        pinMode (nFAULT, INPUT);

	//set microstepping to 1/32
	digitalWrite (MODE2, LOW);
	digitalWrite (MODE1, LOW);
	digitalWrite (MODE0, LOW);

	//set decay mode to fast
	//digitalWrite (DECAY, LOW);

	//set enable and sleep
	digitalWrite (nENBL, LOW);
	digitalWrite (nSLEEP, HIGH);

	//set direction
	digitalWrite (DIR, HIGH);

	//20 steps
	int x=0;
	while(x<32000)
	{
	digitalWrite (STEP, HIGH);
	usleep(3000);
	digitalWrite (STEP, LOW);
	usleep(3000);
	x++;
	}

	digitalWrite (DIR, LOW);
	x=0;
	delay (1000);

        while(x<32000)
        {
        digitalWrite (STEP, HIGH);
	usleep(3000);
        digitalWrite (STEP, LOW);
	usleep(3000);
        x++;
        }


	return 0;
}
