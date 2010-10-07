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

	upVal = 0;
	dnVal = 0;
	rtVal = 0;
	ltVal = 0;

	upPrev = 0;
	dnPrev = 0;
	rtPrev = 0;
	ltPrev = 0;
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

		jogUpdate();

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
	char lastCommand[4];
	upPrev = upVal;
	dnPrev = dnVal;
	rtPrev = rtVal;
	ltPrev = ltVal;

	int xSgn = DRO::getXSign();
	int ySgn = DRO::getYSign();
	int zSgn = DRO::getZSign();
	int rSgn = DRO::getRSign();

	upVal = digitalRead(A10);
	dnVal = digitalRead(A8);
	rtVal = digitalRead(A11);
	ltVal = digitalRead(A9);

	int axis1 = DRO::getJogAxis1();
	int axis2 = DRO::getJogAxis2();

	if(((upVal != upPrev) && (upVal == HIGH)) ||
	   ((dnVal != dnPrev) && (dnVal == HIGH))){
		if (axis2 == 0){
			Serial.println("X20");
			strcpy(lastCommand, "X20");
		}else if (axis2 == 1){
			Serial.println("Y20");
			strcpy(lastCommand, "Y20");
		}else if (axis2 == 2){
			Serial.println("Z20");
			strcpy(lastCommand, "Z20");
		}else if (axis2 == 3){
			Serial.println("A20");
			strcpy(lastCommand, "A20");
		}
	}
	else if ((upVal != upPrev) && (upVal == LOW) && (dnVal == HIGH)){
		if (axis2 == 0){
			if (xSgn > 0){
				Serial.println("X2+");
				strcpy(lastCommand, "X2+");
			}else{
				Serial.println("X2-");
				strcpy(lastCommand, "X2-");
			}
		}else if (axis2 == 1){
			if (ySgn > 0){
				Serial.println("Y2+");
				strcpy(lastCommand, "Y2+");
			}else{
				Serial.println("Y2-");
				strcpy(lastCommand, "Y2-");
			}
		}else if (axis2 == 2){
			if (zSgn > 0){
				Serial.println("Z2+");
				strcpy(lastCommand, "Z2+");
			}else{
				Serial.println("Z2-");
				strcpy(lastCommand, "Z2-");
			}
		}else if (axis2 == 3){
			if (rSgn > 0){
				Serial.println("A2+");
				strcpy(lastCommand, "A2+");
			}else{
				Serial.println("A2-");
				strcpy(lastCommand, "A2-");
			}
		}
	}
	else if ((dnVal != dnPrev) && (dnVal == LOW) && (upVal == HIGH)){
		if (axis2 == 0){
			if (xSgn < 0){
				Serial.println("X2+");
				strcpy(lastCommand, "X2+");
			}else{
				Serial.println("X2-");
				strcpy(lastCommand, "X2-");
			}
		}else if (axis2 == 1){
			if (ySgn < 0){
				Serial.println("Y2+");
				strcpy(lastCommand, "Y2+");
			}else{
				Serial.println("Y2-");
				strcpy(lastCommand, "Y2-");
			}
		}else if (axis2 == 2){
			if (zSgn < 0){
				Serial.println("Z2+");
				strcpy(lastCommand, "Z2+");
			}else{
				Serial.println("Z2-");
				strcpy(lastCommand, "Z2-");
			}
		}else if (axis2 == 3){
			if (rSgn < 0){
				Serial.println("A2+");
				strcpy(lastCommand, "A2+");
			}else{
				Serial.println("A2-");
				strcpy(lastCommand, "A2-");
			}
		}
	}


	if(((ltVal != ltPrev) && (ltVal == HIGH)) ||
	   ((rtVal != rtPrev) && (rtVal == HIGH))){
		if (axis1 == 0){
			Serial.println("X10");
			strcpy(lastCommand, "X10");
		}else if (axis1 == 1){
			Serial.println("Y10");
			strcpy(lastCommand, "Y10");
		}else if (axis1 == 2){
			Serial.println("Z10");
			strcpy(lastCommand, "Z10");
		}else if (axis1 == 3){
			Serial.println("A10");
			strcpy(lastCommand, "A10");
		}
	}
	else if ((ltVal != ltPrev) && (ltVal == LOW) && (rtVal == HIGH)){
		if (axis1 == 0){
			if (xSgn > 0){
				Serial.println("X1+");
				strcpy(lastCommand, "X1+");
			}else{
				Serial.println("X1-");
				strcpy(lastCommand, "X1-");
			}
		}else if (axis1 == 1){
			if (ySgn > 0){
				Serial.println("Y1+");
				strcpy(lastCommand, "Y1+");
			}else{
				Serial.println("Y1-");
				strcpy(lastCommand, "Y1-");
			}
		}else if (axis1 == 2){
			if (zSgn > 0){
				Serial.println("Z1+");
				strcpy(lastCommand, "Z1+");
			}else{
				Serial.println("Z1-");
				strcpy(lastCommand, "Z1-");
			}
		}else if (axis1 == 3){
			if (rSgn > 0){
				Serial.println("A1+");
				strcpy(lastCommand, "A1+");
			}else{
				Serial.println("A1-");
				strcpy(lastCommand, "A1-");
			}
		}
	}
	else if ((rtVal != rtPrev) && (rtVal == LOW) && (ltVal == HIGH)){
		if (axis1 == 0){
			if (xSgn < 0){
				Serial.println("X1+");
				strcpy(lastCommand, "X1+");
			}else{
				Serial.println("X1-");
				strcpy(lastCommand, "X1-");
			}
		}else if (axis1 == 1){
			if (ySgn < 0){
				Serial.println("Y1+");
				strcpy(lastCommand, "Y1+");
			}else{
				Serial.println("Y1-");
				strcpy(lastCommand, "Y1-");
			}
		}else if (axis1 == 2){
			if (zSgn < 0){
				Serial.println("Z1+");
				strcpy(lastCommand, "Z1+");
			}else{
				Serial.println("Z1-");
				strcpy(lastCommand, "Z1-");
			}
		}else if (axis1 == 3){
			if (rSgn < 0){
				Serial.println("A1+");
				strcpy(lastCommand, "A1+");
			}else{
				Serial.println("A1-");
				strcpy(lastCommand, "A1-");
			}
		}
	}

	if ((upVal == LOW) || (dnVal == LOW) || (ltVal == LOW) || (rtVal == LOW)){
		digitalWrite(13,1);
	} else {
		digitalWrite(13,0);
	}

	if((lastCommand[2] == '+') || (lastCommand[2] == '-')){
		if((lastCommand[1] == '1') &&
				((ltVal == LOW) && (rtVal == LOW))){
			if(lastCommand[0] == 'X'){
				Serial.println("X10");
			}else if(lastCommand[0] == 'Y'){
				Serial.println("Y10");
			}else if(lastCommand[0] == 'Z'){
				Serial.println("Z10");
			}else if(lastCommand[0] == 'A'){
				Serial.println("A10");
			}
		}else if((lastCommand[1] == '2') &&
				((upVal == LOW) && (dnVal == LOW))){
			if(lastCommand[0] == 'X'){
				Serial.println("X20");
			}else if(lastCommand[0] == 'Y'){
				Serial.println("Y20");
			}else if(lastCommand[0] == 'Z'){
				Serial.println("Z20");
			}else if(lastCommand[0] == 'A'){
				Serial.println("A20");
			}
		}
	}
}
