/*
 * The class that contains the axis config panel
 *
 *  Created on: Sep 7, 2010
 *      Author: David Erdos
 */

#include "axisconfigpanel.h"
#include "dro.h"
#include "slcd.h"

const char * n0  = "x140";
const char * n1  = "x141";
const char * n2  = "x142";
const char * n3  = "x143";
const char * n4  = "x144";
const char * n5  = "x145";
const char * n6  = "x146";
const char * n7  = "x147";
const char * n8  = "x148";
const char * n9  = "x149";
const char * dec = "x150";

const char * Clear    = "x160";
const char * Return   = "x161";
const char * StartCal = "x162";
const char * StopCal  = "x163";
const char * CalDist  = "x164";

AxisConfigPanel::AxisConfigPanel(const int axis, Parent *newParent){
	if (axis == 1)
		axisName = 'x';
	else if (axis == 2)
		axisName = 'y';
	else if (axis == 3)
		axisName = 'z';
	else if (axis == 4)
		axisName = 'r';

	startCount = 0;
	dist = 0;
	parent = newParent;
}

void AxisConfigPanel::initialize(){
	if (axisName == 'x'){
		SLCD::initializeConfig(1);
		SLCD::updateConfigValues(dist);
	}
	else if (axisName == 'y'){
		SLCD::initializeConfig(2);
		SLCD::updateConfigValues(dist);
	}
	else if (axisName == 'z'){
		SLCD::initializeConfig(3);
		SLCD::updateConfigValues(dist);
	}
	else if (axisName == 'r'){
		SLCD::initializeConfig(4);
		SLCD::updateConfigValues(dist);
	}
}

void AxisConfigPanel::update(char *command){
	if (!strcmp(command,"updt")){
		SLCD::updateConfigValues(dist);
	}
	else if (!strcmp(command,Return)) {
		parent->popPanel();
		delay(100);
		SLCD::initializeHome();
	}
	else if (!strcmp(command,Clear)) {
		dist = 0;
		SLCD::updateConfigValues(dist);
	}
	else if (!strcmp(command,StartCal)) {
		if (axisName == 'x'){
			startCount = DRO::getXCnt();
		}
		else if (axisName == 'y'){
			startCount = DRO::getYCnt();
		}
		else if (axisName == 'z'){
			startCount = DRO::getZCnt();
		}
		else if (axisName == 'r'){
			startCount = DRO::getRCnt();
		}
	}
	else if (!strcmp(command,StopCal)) {
		if (axisName == 'x'){
			DRO::setXCal(startCount, DRO::getXCnt(), dist);
		}
		else if (axisName == 'y'){
			DRO::setYCal(startCount, DRO::getYCnt(), dist);
		}
		else if (axisName == 'z'){
			DRO::setZCal(startCount, DRO::getZCnt(), dist);
		}
		else if (axisName == 'r'){
			DRO::setRCal(startCount, DRO::getRCnt(), dist);
		}
	}
	else if (!strcmp(command,n0)) {

	}
	else if (!strcmp(command,n1)) {

	}
	else if (!strcmp(command,n2)) {

	}
	else if (!strcmp(command,n3)) {

	}
	else if (!strcmp(command,n4)) {

	}
	else if (!strcmp(command,n5)) {

	}
	else if (!strcmp(command,n6)) {

	}
	else if (!strcmp(command,n7)) {

	}
	else if (!strcmp(command,n8)) {

	}
	else if (!strcmp(command,n9)) {

	}
	else if (!strcmp(command,dec)) {

	}

}
