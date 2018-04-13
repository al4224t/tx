#include <iostream>
#include <wiringPi.h>
#include <unistd.h>

class drv8824
{

	int halfperiod = 1000;
	int ustepdiv = 1;

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

        int tMODE2 = 29;
        int tMODE1 = 28;
        int tMODE0 = 27;
        int tSTEP = 26;
        int tnENBL = 31;
        int tDIR = 11;
        int tDECAY = 10;
        int tnSLEEP = 6;
        int tnHOME = 5;
        int tnFAULT = 4;

	int i=0;
	int j=0;

	public:

	void setup (){
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

                pinMode (tMODE2, OUTPUT);
                pinMode (tMODE1, OUTPUT);
                pinMode (tMODE0, OUTPUT);
                pinMode (tSTEP, OUTPUT);
                pinMode (tnENBL, OUTPUT);
                pinMode (tDIR, OUTPUT);
                pinMode (tDECAY, OUTPUT);
                pinMode (tnSLEEP, OUTPUT);
                pinMode (tnHOME, INPUT);
                pinMode (tnFAULT, INPUT);

		//set microstepping
		digitalWrite (MODE2, HIGH);
        	digitalWrite (MODE1, HIGH);
        	digitalWrite (MODE0, HIGH);
        	ustepdiv = 32;

                digitalWrite (tMODE2, HIGH);
                digitalWrite (tMODE1, HIGH);
                digitalWrite (tMODE0, HIGH);

        	//set decay mode to fast
        	digitalWrite (DECAY, HIGH);
		digitalWrite (tDECAY, HIGH);
        	//set enable and sleep
        	digitalWrite (nENBL, LOW);
        	digitalWrite (nSLEEP, HIGH);
		digitalWrite (tnENBL, LOW);
		digitalWrite (tnSLEEP, HIGH);

	}

	void stepping (int direction, int steps, float rpm){
		digitalWrite(DIR, direction);
		halfperiod = ((60*1000000)/(ustepdiv*1000*rpm*2));
		for (i=0; i<steps; i++){
			digitalWrite(STEP,HIGH);
			usleep(halfperiod);
			digitalWrite(STEP,LOW);
			usleep(halfperiod);
		}
	}

        void tstepping (int tdirection, int tsteps, float trpm){
                digitalWrite(tDIR, tdirection);
                halfperiod = ((60*1000000)/(ustepdiv*1000*trpm*2));
                for (i=0; i<tsteps; i++){
                        digitalWrite(tSTEP,HIGH);
                        usleep(halfperiod);
                        digitalWrite(tSTEP,LOW);
                        usleep(halfperiod);
                }
        }

};


int main()
{

	wiringPiSetup ();

	drv8824 drv8824lower;
	drv8824lower.setup();
	/*20 steps
	int x=0;
	while(x<8000)
	{
	digitalWrite (STEP, HIGH);
	usleep(50000);
	digitalWrite (STEP, LOW);
	usleep(50000);
	x++;
	}

	digitalWrite (DIR, LOW);
	x=0;
	delay (1000);

        while(x<8000)
        {
        digitalWrite (STEP, HIGH);
	usleep(50000);
        digitalWrite (STEP, LOW);
	usleep(50000);
        x++;
        }
	*/
	drv8824lower.stepping(0,8000,5);
	drv8824lower.stepping(1,8000,5);
	drv8824lower.tstepping(0,32000,5);
	drv8824lower.tstepping(1,32000,5);

	return 0;
}
