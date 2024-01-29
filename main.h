#include <stdio.h>
#include <pigpio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <filesystem>

bool fileExistsCheck(const char *filename){
	std::ifstream file(filename);
	return file.good();
}

void fileBackup(std::string filename){
	std::string line;
	std::ifstream ini_file("log.csv");
	std::ofstream out_file("backup/_log.csv");
	if(ini_file && out_file){
		while(getline(ini_file, line)){
			out_file << line << "\n";
		}
	}
	
	ini_file.close();
	out_file.close();
}
void writeToSysLog(std::string message, int record){
	std::ofstream logfile;
	switch (record){
	case 0:
		if (fileExistsCheck("log.csv")){fileBackup("log.csv");}
		logfile.open("log.csv", std::ofstream::trunc); break;//init record, removing old stuff
	case 1:
		logfile.open("log.csv", std::ofstream::app); break;//normal record, buffering at end of file
	}
	
	logfile << message;
	auto now = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(now);

	int spaces = 30 - message.size();
	for (int i = 0; i < spaces; i++){
		logfile << " ";
	}
	logfile << std::ctime(&time);
	logfile.close();


}



int gpioInitLibCheck(){
	if (gpioInitialise() < 0){
		fprintf(stderr, "pigpio not available\n");
		return 1;
	}
	writeToSysLog("Init successfull", 0);
	return 0;
}

void setLed(int ledPin){
	gpioSetMode(ledPin, PI_OUTPUT);
	gpioWrite(ledPin, 0);
}
void setButton(int butPin){
	gpioSetMode(butPin, PI_INPUT);
}
void ledOnButClick(int butPin, int ledPin){
	if (gpioRead(butPin)){
		gpioWrite(ledPin, 1);

	} else {
		gpioWrite(ledPin, 0);

	}
}

void initSetup(int ledPin, int butPin){
	setLed(ledPin);
	setButton(butPin);
}	

