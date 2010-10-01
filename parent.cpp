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
	
	long XTemp = 0;
	long YTemp = 0;
	long ZTemp = 0;
	long RTemp = 0;

	while(1){
		XTemp = DRO::getXCnt();
		YTemp = DRO::getYCnt();
		ZTemp = DRO::getZCnt();
		RTemp = DRO::getRCnt();

		//Blink the led to show that we're updating
		//digitalWrite(13, led);
		//led = !led;
		//DRO::ledBlink();

		while(Serial3.available()){
			char c = Serial3.read();
			//Serial.println(c);
			if (c == 'x'){
				sReadBuffer[0] = 'x';
				sReadBuffer[1] = Serial3.read();
				sReadBuffer[2] = Serial3.read();
				sReadBuffer[3] = Serial3.read();
				Serial3.flush();
				//Serial.println(sReadBuffer);
				delay(20);
			}
		}

		if ((sReadBuffer[0] != 'x'))/*
				&& (XTemp != DRO::getXCnt())
				&& (YTemp != DRO::getYCnt())
				&& (ZTemp != DRO::getZCnt())
				&& (RTemp != DRO::getRCnt()))*/
			strcpy(sReadBuffer, "updt");

		curPanel->update(sReadBuffer);
		memset(&sReadBuffer, 0, sizeof(sReadBuffer));

		delay(50);
	}
}

void Parent::pushPanel(Panel *panel){
	lastPanel = curPanel;
	curPanel = panel;
	curPanel->initialize();
	//Serial.println("Pushed Panel");
}

void Parent::popPanel(){
	curPanel = lastPanel;
	lastPanel = NULL;
	delay(10);
	curPanel->initialize();
	//Serial.println("Popped Panel");
}

void Parent::jogUpdate(){
	upPrev = upVal;
	dnPrev = dnVal;
	rtPrev = rtVal;
	ltPrev = ltVal;

	xSgn = DRO::getXSign();
	ySgn = DRO::getYSign();
	zSgn = DRO::getZSign();
	rSgn = DRO::getRSign();

	upVal = digitalRead(A10);
	dnVal = digitalRead(A8);
	rtVal = digitalRead(A11);
	ltVal = digitalRead(A9);

	axis1 = DRO::getJogAxis1();
	axis2 = DRO::getJogAxis2();

	if(((upVal != upPrev) && (upVal == HIGH)) ||
	   ((dnVal != dnPrev) && (dnVal == HIGH))){
		if (axis2 == 0)
			Serial.println("X20");
		else if (axis2 == 1)
			Serial.println("Y20");
		else if (axis2 == 2)
			Serial.println("Z20");
		else if (axis2 == 3)
			Serial.println("A20");
	}
	else if ((upVal != upPrev) && (upVal == LOW) && (dnVal == HIGH)){
		if (axis2 == 0)
			if (xSgn)
				Serial.println("X2+");
			else
				Serial.println("X2-");
		else if (axis2 == 1)
			if (ySgn)
				Serial.println("Y2+");
			else
				Serial.println("Y2-");
		else if (axis2 == 2)
			if (zSgn)
				Serial.println("Z2+");
			else
				Serial.println("Z2-");
		else if (axis2 == 3)
			if (rSgn)
				Serial.println("A2+");
			else
				Serial.println("A2-");
	}
	else if ((dnVal != dnPrev) && (dnVal == LOW) && (upVal == HIGH)){
		if (axis2 == 0)
			if (!xSgn)
				Serial.println("X2+");
			else
				Serial.println("X2-");
		else if (axis2 == 1)
			if (!ySgn)
				Serial.println("Y2+");
			else
				Serial.println("Y2-");
		else if (axis2 == 2)
			if (!zSgn)
				Serial.println("Z2+");
			else
				Serial.println("Z2-");
		else if (axis2 == 3)
			if (!rSgn)
				Serial.println("A2+");
			else
				Serial.println("A2-");
	}

	if(((upVal != upPrev) && (upVal == HIGH)) ||
	   ((dnVal != dnPrev) && (dnVal == HIGH))){
		if (axis1 == 0)
			Serial.println("X10");
		else if (axis2 == 1)
			Serial.println("Y10");
		else if (axis2 == 2)
			Serial.println("Z10");
		else if (axis2 == 3)
			Serial.println("A10");
	}
	else if ((upVal != upPrev) && (upVal == LOW) && (dnVal == HIGH)){
		if (axis1 == 0)
			if (xSgn)
				Serial.println("X1+");
			else
				Serial.println("X1-");
		else if (axis1 == 1)
			if (ySgn)
				Serial.println("Y1+");
			else
				Serial.println("Y1-");
		else if (axis1 == 2)
			if (zSgn)
				Serial.println("Z1+");
			else
				Serial.println("Z1-");
		else if (axis1 == 3)
			if (rSgn)
				Serial.println("A1+");
			else
				Serial.println("A1-");
	}
	else if ((dnVal != dnPrev) && (dnVal == LOW) && (upVal == HIGH)){
		if (axis1 == 0)
			if (!xSgn)
				Serial.println("X1+");
			else
				Serial.println("X1-");
		else if (axis1 == 1)
			if (!ySgn)
				Serial.println("Y1+");
			else
				Serial.println("Y1-");
		else if (axis1 == 2)
			if (!zSgn)
				Serial.println("Z1+");
			else
				Serial.println("Z1-");
		else if (axis1 == 3)
			if (!rSgn)
				Serial.println("A1+");
			else
				Serial.println("A1-");
	}
}
