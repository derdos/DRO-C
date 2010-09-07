/*
 * homepanel.cpp
 *
 *  Created on: Sep 3, 2010
 *      Author: David Erdos
 */
//====================================================
//						HomePanel
//====================================================
#include "homepanel.h"
#include "slcd.h"
#include "parent.h"

const char * zeroX = "x130";
const char * zeroY = "x131";
const char * zeroZ = "x132";
const char * zeroR = "x133";

const char * XConf = "x170";
const char * YConf = "x171";
const char * ZConf = "x172";
const char * RConf = "x173";

const int AxisX = 1;
const int AxisY = 2;
const int AxisZ = 3;
const int AxisR = 4;

HomePanel::HomePanel(Parent *parent) :
		parent(parent),
		XConfig(1,parent),
		YConfig(2,parent),
		ZConfig(3,parent),
		RConfig(4,parent){
}

void HomePanel::initialize(){
	SLCD::initializeHome();
}

void HomePanel::update(char *command){
	if (!strcmp(command,"updt")){
		SLCD::updateHomeValues();
	} else if (!strcmp(command,zeroX)) {
		DRO::zeroX();
		SLCD::updateHomeValues();
	} else if (!strcmp(command,zeroY)) {
		DRO::zeroY();
		SLCD::updateHomeValues();
	} else if (!strcmp(command,zeroZ)) {
		DRO::zeroZ();
		SLCD::updateHomeValues();
	} else if (!strcmp(command,zeroR)) {
		DRO::zeroR();
		SLCD::updateHomeValues();
	} else if (!strcmp(command,XConf)) {
		parent->pushPanel(&XConfig);
	} else if (!strcmp(command,YConf)) {
		parent->pushPanel(&YConfig);
	} else if (!strcmp(command,ZConf)) {
		parent->pushPanel(&ZConfig);
	} else if (!strcmp(command,RConf)) {
		parent->pushPanel(&RConfig);
	}
}
