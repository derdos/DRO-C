/*
 * homepanel.cpp
 *
 *  Created on: Sep 3, 2010
 *      Author: David Erdos
 */

#include "homepanel.h"
#include "panel.h"
#include "slcd.h"

void HomePanel::initialize(){
	SLCD::initializeLCD();
}

void HomePanel::update(char *command){
	SLCD::updateHomeValues();
}
