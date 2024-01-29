#include <stdio.h>
#include <pigpio.h>
#include "main.h"
#include <fstream>
#include <iostream>
//#include <cstdlib>


int main(int argc, char* argv[]){
	//std::ofstream logfile("log.csv");
	gpioInitLibCheck();
	initSetup(23, 17);

	writeToSysLog("zprava", 1);
	writeToSysLog("zprava2", 1);
	writeToSysLog("zpravadfsdfsdadsaa", 1);
	writeToSysLog("zpravwqqwfqwa2", 1);
	while(true){
		ledOnButClick(17, 23);



	}

}
