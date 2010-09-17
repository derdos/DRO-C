/*
 * The class that contains the setup panel
 *
 *  Created on: Sep 7, 2010
 *      Author: David Erdos
 */

#include "setuppanel.h"
#include "dro.h"
#include "slcd.h"

const char * Loud     	 = "x181";
const char * Quiet    	 = "x182";
const char * Silent   	 = "x183";
const char * Centimeter  = "x185";
const char * Inch		 = "x186";
const char * RevX		 = "x187";
const char * RevY		 = "x188";
const char * RevZ		 = "x189";
const char * RevR		 = "x190";

#define INCH	0
#define CM		1
#define SILENT	0
#define QUIET 	1
#define LOUD	2

SetupPanel::SetupPanel(Parent *newParent){
	parent = newParent;
}

void SetupPanel::initialize(){
	SLCD::displaySetup();
	SLCD::updateSetup();
	SLCD::setVolume(DRO::getVolume());
	SLCD::setUnits(DRO::getUnits());
}

void SetupPanel::update(char *command){
	const char * Return   = "x161";
	const char * Calibrate   = "x166";
	
	if (!strcmp(command,"updt")){
		//Nothing to do here...
	}
	else if (!strcmp(command,Return)) {
		Serial.println("Popping Setup Panel");
		parent->popPanel();
	}
	else if (!strcmp(command,Centimeter)) {
		DRO::setUnits(CM);
		SLCD::setUnits(CM);
		SLCD::updateSetup();
	}
	else if (!strcmp(command,Inch)) {
		DRO::setUnits(INCH);
		SLCD::setUnits(INCH);
		SLCD::updateSetup();
	}
	else if (!strcmp(command,Loud)) {
		DRO::setVolume(LOUD);
		SLCD::setVolume(LOUD);
		SLCD::updateSetup();
	}
	else if (!strcmp(command,Quiet)) {
		DRO::setVolume(QUIET);
		SLCD::setVolume(QUIET);
		SLCD::updateSetup();
	}
	else if (!strcmp(command,Silent)) {
		DRO::setVolume(SILENT);
		SLCD::setVolume(SILENT);
		SLCD::updateSetup();
	}
	else if (!strcmp(command,Calibrate)) {
		Serial3.flush();
		SLCD::sendLCD("tc");
		Serial.println("Calibration Started");
		while(!Serial3.available()){
			//Do nothing until the calibration completes
		}
		Serial.println("Calibration Complete");
		SLCD::displaySetup();
		SLCD::updateSetup();
	}
	else if (!strcmp(command,RevX)) {
		DRO::changeXSign();
	}
	else if (!strcmp(command,RevY)) {
		DRO::changeYSign();
	}
	else if (!strcmp(command,RevZ)) {
		DRO::changeZSign();
	}
	else if (!strcmp(command,RevR)) {
		DRO::changeRSign();
	}
}