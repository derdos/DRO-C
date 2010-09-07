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
	memset(&sReadBuffer, 0, sizeof(sReadBuffer));
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

	//Set up the led for blinking
	pinMode(13, OUTPUT);
	boolean led = true;
	delay(100);

	while(1){
		delay(100);

		//Blink the led to show that we're updating
		digitalWrite(13, led);
		led = !led;

		curPanel->update(sReadBuffer);

		DRO::ledBlink();
		//Check how many bytes are in the buffer
		if(Serial3.available() > 0){
			int c = -1;
			int i = 0;
			while(c != '\r' && i < 5){
				while(c == -1){
					c = Serial3.read();
				}
				sReadBuffer[i++] = c;
			}

			//Serial.println("foo");
			Serial.println(sReadBuffer);
			memset(&sReadBuffer, 0, sizeof(sReadBuffer));
		}
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
