/*
 * Parent library for the LCD menu control aspect of the DRO
 *
 *  Created on: Sep 2, 2010
 *      Author: David Erdos
 */

#include "parent.h"
#include "panel.h"
#include "dro.h"
#include "slcd.h"

Parent::Parent(){
	iBufferSize = 7;
	iIndex = 0;
	memset(&sReadBuffer, 0, sizeof(sReadBuffer));
	cEOL = '\r';
	//Open the serial port
	Serial3.begin(115200);
}

void Parent::setHomePanel(Panel *panel){
	homePanel = panel;
	pushPanel(homePanel);
}

void Parent::run(){
	delay(100);
	//curPanel->initialize();

	//Set up the led for blinking
	pinMode(13, OUTPUT);
	boolean led = true;
	delay(100);

	while(1){
		delay(50);

		//Blink the led to show that we're updating
		digitalWrite(13, led);
		led = !led;

		//curPanel->update(sReadBuffer);
		DRO::ledBlink();

		while(Serial3.available()){
			char c = Serial3.read();
			Serial.println(c);
			if (c == 'x'){
				sReadBuffer[0] = 'x';
				sReadBuffer[1] = Serial3.read();
				sReadBuffer[2] = Serial3.read();
				sReadBuffer[3] = Serial3.read();
				Serial3.flush();
				Serial.println(sReadBuffer);
				delay(20);
			}
		}

		if (sReadBuffer[0] != 'x')
			strcpy(sReadBuffer, "updt");

		curPanel->update(sReadBuffer);
		memset(&sReadBuffer, 0, sizeof(sReadBuffer));
	}
}

void Parent::pushPanel(Panel *panel){
	lastPanel = curPanel;
	curPanel = panel;
	curPanel->initialize();
	Serial.println("Pushed Panel");
}

void Parent::popPanel(){
	curPanel = lastPanel;
	lastPanel = NULL;
	delay(20);
	curPanel->initialize();
	Serial.println("Popped Panel");
}
