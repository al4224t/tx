#include <iostream>
#include <wiringPi.h>
#include <unistd.h>

class drv8824
{

	int halfperiod = 1000;
	int ustepdiv = 1;

	int tMODE2 = 0;
	int tMODE1 = 2;
	int tMODE0 = 3;
	int tSTEP = 23;
	int tnENBL = 12;
	int tDIR = 13;
	int tDECAY = 14;
	int tnSLEEP = 22;
	//int tnHOME = 21;
	//int tnFAULT = 22;

	int bMODE2 = 6;
	int bMODE1 = 10;
	int bMODE0 = 11;
	int bSTEP = 26;
	int bnENBL = 31;
	int bDIR = 27;
	int bDECAY = 28;
	int bnSLEEP = 29;
	//int bnHOME = 21;
	//int bnFAULT = 22;

	int i=0;
	int j=0;

	public:

	void setup (){
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

		pinMode (bMODE2, OUTPUT);
		pinMode (bMODE1, OUTPUT);
		pinMode (bMODE0, OUTPUT);
		pinMode (bSTEP, OUTPUT);
		pinMode (bnENBL, OUTPUT);
		pinMode (bDIR, OUTPUT);
		pinMode (bDECAY, OUTPUT);
		pinMode (bnSLEEP, OUTPUT);
		pinMode (bnHOME, INPUT);
		pinMode (bnFAULT, INPUT);

		//set microstepping to 1/32
		digitalWrite (tMODE2, HIGH);
		digitalWrite (tMODE1, HIGH);
		digitalWrite (tMODE0, HIGH);

		digitalWrite (bMODE2, HIGH);
		digitalWrite (bMODE1, HIGH);
		digitalWrite (bMODE0, HIGH);
		
		ustepdiv = 32;

        //set decay mode to fast
        digitalWrite (tDECAY, HIGH);
		digitalWrite (bDECAY, HIGH);
        
		//set enable and sleep
		digitalWrite (tENBL, LOW);
		digitalWrite (tSLEEP, HIGH);
		digitalWrite (bnENBL, LOW);
		digitalWrite (bnSLEEP, HIGH);
	}

	void tstepping (int direction, int steps, float rpm){
		digitalWrite(tDIR, direction);
		halfperiod = ((60*1000000)/(ustepdiv*1000*rpm*2));
		for (i=0; i<steps; i++){
			digitalWrite(tSTEP,HIGH);
			usleep(halfperiod);
			digitalWrite(tSTEP,LOW);
			usleep(halfperiod);
		}
	}

    void bstepping (int direction, int steps, float rpm){
		digitalWrite(bDIR, direction);
		halfperiod = ((60*1000000)/(ustepdiv*1000*trpm*2));
		for (i=0; i<steps; i++){
			digitalWrite(bSTEP,HIGH);
			usleep(halfperiod);
			digitalWrite(bSTEP,LOW);
			usleep(halfperiod);
		}
	}

};


int main()
{

	wiringPiSetup ();

	drv8824 drv8824lower;
	drv8824lower.setup();

	drv8824lower.tstepping(0,8000,5);
	drv8824lower.tstepping(1,8000,5);
	drv8824lower.bstepping(0,8000,5);
	drv8824lower.bstepping(1,8000,5);

	return 0;
}
