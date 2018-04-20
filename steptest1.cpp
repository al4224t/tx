#include <iostream>
#include <wiringPi.h>
#include <unistd.h>

int main()
{

	wiringPiSetup ();

	int MODE2 = 0;
	int MODE1 = 2;
	int MODE0 = 3;
	int STEP = 23;
	int nENBL = 12;
	int DIR = 13;
	int DECAY = 14;
	int nSLEEP = 22;
	//int nHOME = 21;
	//int nFAULT = 22;

	int tMODE2 = 6;
	int tMODE1 = 10;
	int tMODE0 = 11;
	int tSTEP = 26;
	int tnENBL = 31;
	int tDIR = 27;
	int tDECAY = 28;
	int tnSLEEP = 29;
	//int tnHOME = 21;
	//int tnFAULT = 22;

        pinMode (MODE2, OUTPUT);
        pinMode (MODE1, OUTPUT);
        pinMode (MODE0, OUTPUT);
        pinMode (STEP, OUTPUT);
        pinMode (nENBL, OUTPUT);
        pinMode (DIR, OUTPUT);
        pinMode (DECAY, OUTPUT);
        pinMode (nSLEEP, OUTPUT);
        //pinMode (nHOME, INPUT);
        //pinMode (nFAULT, INPUT);

	pinMode (tMODE2, OUTPUT);
        pinMode (tMODE1, OUTPUT);
        pinMode (tMODE0, OUTPUT);
        pinMode (tSTEP, OUTPUT);
        pinMode (tnENBL, OUTPUT);
        pinMode (tDIR, OUTPUT);
        pinMode (tDECAY, OUTPUT);
        pinMode (tnSLEEP, OUTPUT);
        //pinMode (nHOME, INPUT);
        //pinMode (nFAULT, INPUT);

	//set microstepping to 1/32
	digitalWrite (MODE2, HIGH);
	digitalWrite (MODE1, HIGH);
	digitalWrite (MODE0, HIGH);

	digitalWrite (tMODE2, HIGH);
	digitalWrite (tMODE1, HIGH);
	digitalWrite (tMODE0, HIGH);
	//set decay mode to fast
	//digitalWrite (DECAY, LOW);

	//set enable and sleep
	digitalWrite (nENBL, LOW);
	digitalWrite (nSLEEP, HIGH);

	digitalWrite (tnENBL, LOW);
	digitalWrite (tnSLEEP, HIGH);
	//set direction
	digitalWrite (DIR, LOW);
	digitalWrite (tDIR, LOW);

	//20 steps
	int x=0;
	while(x<8000)
	{
	digitalWrite (STEP, HIGH);
	usleep(200);
	digitalWrite (STEP, LOW);
	usleep(200);
	x++;
	}

	digitalWrite (DIR, HIGH);
	x=0;
	delay (100);

        while(x<8000)
        {
        digitalWrite (STEP, HIGH);
	usleep(300);
        digitalWrite (STEP, LOW);
	usleep(300);
        x++;
        }

	delay (100);

	x=0;
	while(x<16000)
	{
	digitalWrite (tSTEP, HIGH);
	usleep(200);
	digitalWrite (tSTEP, LOW);
	usleep(200);
	x++;
	}

	digitalWrite (tDIR, HIGH);
	x=0;
	delay (100);

        while(x<32000)
        {
        digitalWrite (tSTEP, HIGH);
	usleep(200);
        digitalWrite (tSTEP, LOW);
	usleep(200);
        x++;
        }

	delay (100);
	x=0;
	digitalWrite (tDIR, LOW);

        while(x<16000)
        {
        digitalWrite (tSTEP, HIGH);
	usleep(200);
        digitalWrite (tSTEP, LOW);
	usleep(200);
        x++;
        }

	return 0;
}
