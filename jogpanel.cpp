/*
 * The class that contains the setup panel
 *
 *  Created on: Sep 7, 2010
 *      Author: David Erdos
 */

#include "JogPanel.h"
#include "dro.h"
#include "slcd.h"

const char * x1    	 = "x191";
const char * y1    	 = "x192";
const char * z1   	 = "x193";
const char * r1 	 = "x194";
const char * x2		 = "x195";
const char * y2		 = "x196";
const char * z2		 = "x197";
const char * r2		 = "x198";

#define Xn	0
#define Yn	1
#define Zn	2
#define Rn 	3

JogPanel::JogPanel(Parent *newParent){
	parent = newParent;
}

void JogPanel::initialize(){
	SLCD::displayJog();
	SLCD::updateJog();
}

void JogPanel::update(char *command){
	const char * Return   = "x161";
	
	if (!strcmp(command,"updt")){
		//Nothing to do here...
	}else if (!strcmp(command,Return)) {
		//Serial.println("Popping Setup Panel");
		parent->popPanel();
	}else if (!strcmp(command,x1) && (DRO::getJogAxis2() != Xn)) {
		DRO::setJogAxis1(Xn);
		SLCD::updateJog();
		stopAxis1Jog();
	}else if (!strcmp(command,y1) && (DRO::getJogAxis2() != Yn)) {
		DRO::setJogAxis1(Yn);
		SLCD::updateJog();
		stopAxis1Jog();
	}else if (!strcmp(command,z1) && (DRO::getJogAxis2() != Zn)) {
		DRO::setJogAxis1(Zn);
		SLCD::updateJog();
		stopAxis1Jog();
	}else if (!strcmp(command,r1) && (DRO::getJogAxis2() != Rn)) {
		DRO::setJogAxis1(Rn);
		SLCD::updateJog();
		stopAxis1Jog();
	}else if (!strcmp(command,x2) && (DRO::getJogAxis1() != Xn)) {
		DRO::setJogAxis2(Xn);
		SLCD::updateJog();
		stopAxis2Jog();
	}else if (!strcmp(command,y2) && (DRO::getJogAxis1() != Yn)) {
		DRO::setJogAxis2(Yn);
		SLCD::updateJog();
		stopAxis2Jog();
	}else if (!strcmp(command,z2) && (DRO::getJogAxis1() != Zn)) {
		DRO::setJogAxis2(Zn);
		SLCD::updateJog();
		stopAxis2Jog();
	}else if (!strcmp(command,r2) && (DRO::getJogAxis1() != Rn)) {
		DRO::setJogAxis2(Rn);
		SLCD::updateJog();
		stopAxis2Jog();
	}
}

void JogPanel::stopAxis1Jog(){
	Serial.println("X10");
	Serial.println("Y10");
	Serial.println("Z10");
	Serial.println("A10");
}

void JogPanel::stopAxis2Jog(){
	Serial.println("X20");
	Serial.println("Y20");
	Serial.println("Z20");
	Serial.println("A20");
}
