/*
 * Parent library for the LCD menu control aspect of the DRO
 *
 *  Created on: Sep 2, 2010
 *      Author: David Erdos
 */

#include "parent.h"
#include "panel.h"
#include "dro.h"
#include <homepanel.h>

static HomePanel homePanel;

Parent::Parent(){
	iBufferSize = 7;
	iIndex = 0;
	sReadBuffer = "";
	cEOL = '\r';
	//Open the serial port
	Serial3.begin(115200);
	Serial3.println("z");
	homePanel = HomePanel();
	pushPanel(&homePanel);
}

void Parent::run(){
	delay(100);
	//DRO::setXScl(0.0005);
	//DRO::setYScl(0.0005);
	curPanel->initialize();
	delay(100);
	while(1){
		delay(20);
		//double read = DRO::eSettings.readDouble(XSCL_ADDR);
		//Serial.println(read);
		/*
		Serial.print("X:  ");
		Serial.print(DRO::getXPos());
		Serial.print("   ");
		Serial.print(DRO::getXScl());
		Serial.print("   ");
		Serial.println(DRO::getXCnt());

		Serial.print("Y:  ");
		Serial.print(DRO::getYPos());
		Serial.print("   ");
		Serial.print(DRO::getYScl());
		Serial.print("   ");
		Serial.println(DRO::getYCnt());

		Serial.print("Z:  ");
		Serial.print(DRO::getZPos());
		Serial.print("   ");
		Serial.print(DRO::getZScl());
		Serial.print("   ");
		Serial.println(DRO::getZCnt());

		Serial.print("R:  ");
		Serial.print(DRO::getRAng());
		Serial.print("   ");
		Serial.print(DRO::getRScl());
		Serial.print("   ");
		Serial.println(DRO::getRCnt());
		*/
		curPanel->update(sReadBuffer.getChars());
		//Check how many bytes are in the buffer
		/*if(Serial3.available() > 0)
			sReadBuffer += Serial3.read();
		if(sReadBuffer.charAt(sReadBuffer.length()) == cEOL){
			//Update current panel
			curPanel->update(sReadBuffer.getChars());
			//Clear the read buffer
			sReadBuffer = "";
		}
		*/

	}
}

void Parent::pushPanel(Panel *panel){
	lastPanel = curPanel;
	curPanel = panel;
	panel->initialize();
}

void Parent::popPanel(){
	curPanel = lastPanel;
	lastPanel = NULL;
	curPanel->initialize();
}
