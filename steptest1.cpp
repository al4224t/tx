#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include <ncurses.h>

using namespace std;

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
	int modenew;
	int mode;
	char cdir;
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
//	        digitalWrite (tDECAY, HIGH);
//		digitalWrite (bDECAY, HIGH);

		//set enable and sleep
		digitalWrite (tnENBL, LOW);
		digitalWrite (tnSLEEP, HIGH);
		digitalWrite (bnENBL, LOW);
		digitalWrite (bnSLEEP, HIGH);
	}

/*	void tstepping (int direction){
		digitalWrite(tDIR, direction);
		halfperiod = ((60*1000000)/(ustepdiv*1000*rpm*2));
		for (i=0; i<steps; i++){
			digitalWrite(tSTEP,HIGH);
			usleep(halfperiod);
			digitalWrite(tSTEP,LOW);
			usleep(halfperiod);
		}
	}
*/

/*    void bstepping (int direction){
		digitalWrite(bDIR, direction);
		halfperiod = ((60*1000000)/(ustepdiv*1000*rpm*2));
		for (i=0; i<steps; i++){
			digitalWrite(bSTEP,HIGH);
			usleep(halfperiod);
			digitalWrite(bSTEP,LOW);
			usleep(halfperiod);
		}
	}
*/

	void command(){
		//echo();
		//nocbreak();
		//std::cout<<"COMMAND MODE"<<std::endl;
		//mode='q';
		//mode1='q';
		//mode2='q';
		//while (mode!='m'){
		//std::cout<<"\nDirection: ";
		//std::cin>>mode;
		//mode=getch();
		//std::cout<<std::endl;
		//if (mode=='m'){
		//	break;
		//}
		//std::cout<<"\nSteps: ";
		//std::cin>>steps;
		//std::cout<<std::endl;
		//std::cout<<"\nrpm: ";
		//std::cin>>rpm;
		//std::cout<<std::endl;
		//clear();
		//echo();
		//nocbreak();
		//nodelay(stdscr,FALSE);
		std::cout<<"COMMAND MODE\n"<<std::endl;
		cdir='w';

		while(cdir!='m'){

			std::cout<<"-Enter direction using 'w' 'a' 's' 'd'"<<std::endl;
			std::cout<<"-Press 'm' to switch to driving mode\n";
			std::cin>>cdir;
			std::cout<<std::endl;
			if (cdir=='m'){
				break;
			}

			std::cout<<"-Enter number of steps\n";
                	std::cin>>steps;
                	std::cout<<std::endl;

                	std::cout<<"-Enter speed in rpm\n";
                	std::cin>>rpm;
                	std::cout<<std::endl;

			halfperiod = ((60*1000000)/(ustepdiv*1000*rpm*2));

			switch(cdir){
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
				default:
					usleep(1);
			}
		}
	}

	void driving (){
		//noecho();
		//cbreak();
		//std::cout<<"\n\rDRIVING MODE"<<std::endl;

		clear();
		printw("DRIVING MODE");
		printw("\n\n\r-Use 'w' 'a' 's' 'd' keys to drive");
		printw("\n\r-Press 'm' to switch to command mode");
		refresh();
		mode=' ';

		halfperiod = 200;

		while(mode!='m'){

			modenew=getch();

			if (modenew!=-1){
				if (modenew!=mode){
					usleep(100000);
				}
				mode=modenew;
			}

			switch(mode){
				case 'w':
					digitalWrite(tDIR,0);
					digitalWrite(tSTEP,HIGH);
					usleep(halfperiod);
					digitalWrite(tSTEP,LOW);
					usleep(halfperiod);
					break;
				case 's':
					digitalWrite(tDIR,1);
					digitalWrite(tSTEP,HIGH);
					usleep(halfperiod);
					digitalWrite(tSTEP,LOW);
					usleep(halfperiod);
					break;
				case 'a':
					digitalWrite(bDIR,1);
					digitalWrite(bSTEP,HIGH);
					usleep(halfperiod);
					digitalWrite(bSTEP,LOW);
					usleep(halfperiod);
					break;
				case 'd':
					digitalWrite(bDIR,0);
					digitalWrite(bSTEP,HIGH);
					usleep(halfperiod);
					digitalWrite(bSTEP,LOW);
					usleep(halfperiod);
					break;
				case ' ':
					usleep(1);
					break;
				default:
					usleep(50000);
			}
		}
	}
};

int main(){

	wiringPiSetup ();
	drv8824 tx;
	tx.setup();

	while(1){
		initscr();
		keypad(stdscr,TRUE);
		nodelay(stdscr,TRUE);
		cbreak();
		noecho();
		tx.driving();
		clear();
		endwin();

		tx.command();
	}

	return 0;
}
