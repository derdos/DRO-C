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
	if (axis == 1){
		axisName = 'x';
		axisNum = 1;
	} else if (axis == 2) {
		axisName = 'y';
		axisNum = 2;
	} else if (axis == 3) {
		axisName = 'z';
		axisNum = 3;
	} else if (axis == 4) {
		axisName = 'r';
		axisNum = 4;
	}

	startCount = 0;
	dist = 0;
	parent = newParent;
}

void AxisConfigPanel::initialize(){
	if (axisName == 'x'){
		SLCD::initializeConfig(1);
		SLCD::updateConfigValues(dist,axisNum);
	}
	else if (axisName == 'y'){
		SLCD::initializeConfig(2);
		SLCD::updateConfigValues(dist,axisNum);
	}
	else if (axisName == 'z'){
		SLCD::initializeConfig(3);
		SLCD::updateConfigValues(dist,axisNum);
	}
	else if (axisName == 'r'){
		SLCD::initializeConfig(4);
		SLCD::updateConfigValues(dist,axisNum);
	}
}

void AxisConfigPanel::update(char *command){
	if (!strcmp(command,"updt")){
		//delay(50);
		//SLCD::updateConfigValues(dist, axisNum);
	}
	else if (!strcmp(command,Return)) {
		parent->popPanel();
		delay(20);
	}
	else if (!strcmp(command,Clear)) {
		dist = 0;
		input = "";
		SLCD::updateConfigValues(dist, axisNum);
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
		input += "0";
		if (isValid(input)){
			input.toCharArray(inputCharArr,7);
			dist = atof(inputCharArr);
			SLCD::updateConfigValues(dist,axisNum);
		}
		else {
			input = input.substring(0,input.length()-1);
		}
	}
	else if (!strcmp(command,n1)) {
		input += "1";
		if (isValid(input)){
			input.toCharArray(inputCharArr,8);
			dist = atof(inputCharArr);
			SLCD::updateConfigValues(dist,axisNum);
		}
		else {
			input = input.substring(0,input.length()-1);
		}
	}
	else if (!strcmp(command,n2)) {
		input += "2";
		if (isValid(input)){
			input.toCharArray(inputCharArr,8);
			dist = atof(inputCharArr);
			SLCD::updateConfigValues(dist,axisNum);
		}
		else {
			input = input.substring(0,input.length()-1);
		}
	}
	else if (!strcmp(command,n3)) {
		input += "3";
		if (isValid(input)){
			input.toCharArray(inputCharArr,8);
			dist = atof(inputCharArr);
			SLCD::updateConfigValues(dist,axisNum);
		}
		else {
			input = input.substring(0,input.length()-1);
		}
	}
	else if (!strcmp(command,n4)) {
		input += "4";
		if (isValid(input)){
			input.toCharArray(inputCharArr,8);
			dist = atof(inputCharArr);
			SLCD::updateConfigValues(dist,axisNum);
		}
		else {
			input = input.substring(0,input.length()-1);
		}
	}
	else if (!strcmp(command,n5)) {
		input += "5";
		if (isValid(input)){
			input.toCharArray(inputCharArr,8);
			dist = atof(inputCharArr);
			SLCD::updateConfigValues(dist,axisNum);
		}
		else {
			input = input.substring(0,input.length()-1);
		}
	}
	else if (!strcmp(command,n6)) {
		input += "6";
		if (isValid(input)){
			input.toCharArray(inputCharArr,8);
			dist = atof(inputCharArr);
			SLCD::updateConfigValues(dist,axisNum);
		}
		else {
			input = input.substring(0,input.length()-1);
		}
	}
	else if (!strcmp(command,n7)) {
		input += "7";
		if (isValid(input)){
			input.toCharArray(inputCharArr,8);
			dist = atof(inputCharArr);
			SLCD::updateConfigValues(dist,axisNum);
		}
		else {
			input = input.substring(0,input.length()-1);
		}
	}
	else if (!strcmp(command,n8)) {
		input += "8";
		if (isValid(input)){
			input.toCharArray(inputCharArr,8);
			dist = atof(inputCharArr);
			SLCD::updateConfigValues(dist,axisNum);
		}
		else {
			input = input.substring(0,input.length()-1);
		}
	}
	else if (!strcmp(command,n9)) {
		input += "9";
		if (isValid(input)){
			input.toCharArray(inputCharArr,8);
			dist = atof(inputCharArr);
			SLCD::updateConfigValues(dist,axisNum);
		}
		else {
			input = input.substring(0,input.length()-1);
		}
		Serial.print(input);
	}
	else if (!strcmp(command,dec)) {
		if (input.length() == 0)
			input += "0.";
		else
			input += ".";
		
		if (!isValid(input)){
			input = input.substring(0,input.length()-1);
		}
		Serial.print(input);
	}
}

bool AxisConfigPanel::isValid(String value){
	if ((value.indexOf('.') > 0) && 
		(value.indexOf('.') != value.lastIndexOf('.')))
		return false;
	
	if (axisNum != 4) {
		if (value.length() < 8){
			if (value.indexOf('.') < 0){
				if (value.length() > 2)
					return false;
				else
					return true;
			}
			else if ((value.substring(0,1).equals('.')) && (value.length() < 5)){
				return true;
			}
			else if ((value.substring(1,2).equals('.')) && (value.length() > 1)){
				return true;
			}
			else if ((value.substring(2,3).equals('.')) && (value.length() > 2)){
				return true;
			}
			else if ((value.substring(0,2).equals("0.")) && (value.length() < 7)){
				return true;
			}
			else
				return false;
		} else
			return false;
	} else {
		if (value.length() < 8){
			if (value.indexOf('.') < 0){
				if (value.length() > 3)
					return false;
				else
					return true;
			}
			else if ((value.substring(0,1).equals('.')) && (value.length() < 4)){
				return true;
			}
			else if ((value.substring(1,2).equals('.')) && (value.length() > 1)){
				return true;
			}
			else if ((value.substring(2,3).equals('.')) && (value.length() > 2)){
				return true;
			}
			else if ((value.substring(3,4).equals('.')) && (value.length() > 3)){
				return true;
			}
			else if ((value.substring(0,2).equals("0.")) && (value.length() < 7)){
				return true;
			}
			else
				return false;
		} else
			return false;
	}
}
