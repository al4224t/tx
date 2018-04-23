#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include <curses.h>

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
	char mode2;
	char mode1;
	char mode;
	int steps=0;
	float rpm=0;

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
		//pinMode (tnHOME, INPUT);
		//pinMode (tnFAULT, INPUT);

		pinMode (bMODE2, OUTPUT);
		pinMode (bMODE1, OUTPUT);
		pinMode (bMODE0, OUTPUT);
		pinMode (bSTEP, OUTPUT);
		pinMode (bnENBL, OUTPUT);
		pinMode (bDIR, OUTPUT);
		pinMode (bDECAY, OUTPUT);
		pinMode (bnSLEEP, OUTPUT);
		//pinMode (bnHOME, INPUT);
		//pinMode (bnFAULT, INPUT);

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
		digitalWrite (tnENBL, LOW);
		digitalWrite (tnSLEEP, HIGH);
		digitalWrite (bnENBL, LOW);
		digitalWrite (bnSLEEP, HIGH);
	}

	void tstepping (int direction){
		digitalWrite(tDIR, direction);
		halfperiod = ((60*1000000)/(ustepdiv*1000*rpm*2));
		for (i=0; i<steps; i++){
			digitalWrite(tSTEP,HIGH);
			usleep(halfperiod);
			digitalWrite(tSTEP,LOW);
			usleep(halfperiod);
		}
	}

    void bstepping (int direction){
		digitalWrite(bDIR, direction);
		halfperiod = ((60*1000000)/(ustepdiv*1000*rpm*2));
		for (i=0; i<steps; i++){
			digitalWrite(bSTEP,HIGH);
			usleep(halfperiod);
			digitalWrite(bSTEP,LOW);
			usleep(halfperiod);
		}
	}

	void somestepping (){
		std::cout<<"Direction: ";
		std::cin>>mode;
		std::cout<<std::endl;
		std::cout<<"Steps: ";
		std::cin>>steps;
		std::cout<<std::endl;
		std::cout<<"rpm: ";
		std::cin>>rpm;
		std::cout<<std::endl;

		halfperiod = ((60*1000000)/(ustepdiv*1000*rpm*2));

		switch(mode){
			case 'w':
				digitalWrite(tDIR,0);
				for (i=0; i<steps; i++){
					digitalWrite(tSTEP,HIGH);
					usleep(halfperiod);
					digitalWrite(tSTEP,LOW);
					usleep(halfperiod);
				}
				break;
			case 's':
				digitalWrite(tDIR,1);
				for (i=0; i<steps; i++){
					digitalWrite(tSTEP,HIGH);
					usleep(halfperiod);
					digitalWrite(tSTEP,LOW);
					usleep(halfperiod);
				}
				break;
			case 'a':
				digitalWrite(bDIR,1);
				for (i=0; i<steps; i++){
					digitalWrite(bSTEP,HIGH);
					usleep(halfperiod);
					digitalWrite(bSTEP,LOW);
					usleep(halfperiod);
				}
				break;
			case 'd':
				digitalWrite(bDIR,0);
				for (i=0; i<steps; i++){
					digitalWrite(bSTEP,HIGH);
					usleep(halfperiod);
					digitalWrite(bSTEP,LOW);
					usleep(halfperiod);
				}
				break;
		}
	}

	void driving (){
		halfperiod = 200;
		while(1){
		mode1 = getch();

		if (mode1=='w'||mode1=='s'||mode1=='a'||mode1=='d'||mode1==' '){
			mode2=mode1;
		}
		if (mode2!=mode){
			usleep(50000);
		}
		mode=mode2;

		switch(mode){
			case 'w':
				//for (i=0;i<50;i++){
				digitalWrite(tDIR,0);
					digitalWrite(tSTEP,HIGH);
					usleep(halfperiod);
					digitalWrite(tSTEP,LOW);
					usleep(halfperiod);
//				}
				break;
			case 's':
				//for (i=0;i<50;i++){
				digitalWrite(tDIR,1);
					digitalWrite(tSTEP,HIGH);
					usleep(halfperiod);
					digitalWrite(tSTEP,LOW);
					usleep(halfperiod);
//				}
				break;
			case 'a':
				//or (i=0;i<50;i++){
				digitalWrite(bDIR,1);
					digitalWrite(bSTEP,HIGH);
					usleep(halfperiod);
					digitalWrite(bSTEP,LOW);
					usleep(halfperiod);
//				}
				break;
			case 'd':
				//for (i=0;i<50;i++){
				digitalWrite(bDIR,0);
					digitalWrite(bSTEP,HIGH);
					usleep(halfperiod);
					digitalWrite(bSTEP,LOW);
					usleep(halfperiod);
//				}
				break;
			default:
				usleep(1);
		}
		}
	}
};

int main()
{

	wiringPiSetup ();

	drv8824 tx;
	tx.setup();

	initscr();
	cbreak();
	noecho();
	nodelay(stdscr,TRUE);
	//while (1){
	//	tx.somestepping();
	//}

	tx.driving();
	//drv8824lower.tstepping(0,8000,10);
	//drv8824lower.tstepping(1,8000,10);
	//drv8824lower.bstepping(0,12000,10);
	//drv8824lower.bstepping(1,24000,10);
	//drv8824lower.bstepping(0,12000,10);

	return 0;
}
