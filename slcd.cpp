/*
 * LCD Driver for the Reach SLCD34 touch screen module
 *
 *  Created on: Sep 2, 2010
 *      Author: David Erdos
 */

#include "slcd.h"
#include "dro.h"
#include <Stdio.h>

#define TRUE 1
#define FALSE 0

double SLCD::dXVal;
double SLCD::dYVal;
double SLCD::dZVal;
double SLCD::dRVal;
char SLCD::cValue[7];

SLCD::SLCD(){
	dXVal = 0;
	dYVal = 0;
	dZVal = 0;
	dRVal = 0;
	memset(&cValue, 0, sizeof(cValue));
	memset(&cBuffer, 0, sizeof(cBuffer));
}

void SLCD::initializeHome(){
	//Clear the screen twice just to be sure
	sendLCD("z");

	//Display the home screen
	if (DRO::getUnits()) { //0 means centimeters
		sendLCD("m 1:cm");
		updateHomeValues();
	}
	else {
		sendLCD("m 1:in");
		updateHomeValues();
	}

	DRO::getXScl();
	DRO::getYScl();
	DRO::getZScl();
	DRO::getRScl();

	forceUpdateHomeValues();
}

void SLCD::initializeConfig(const int axis){
	clearScreen();
	if (axis == 1){
		sendLCD("m 3:x");
		sendLCD("m 4 00.0000");
	} else if (axis == 2){
		sendLCD("m 3:y");
		sendLCD("m 4 00.0000");
	} else if (axis == 3){
		sendLCD("m 3:z");
		sendLCD("m 4 00.0000");
	} else if (axis == 4){
		sendLCD("m 3:r");
		sendLCD("m 4 000.000");
	}
}

int SLCD::sendLCD(char *command, int final){
	if (!final){
		Serial3.print(command);
	} else{
		Serial3.print(command);
		Serial3.print('\r');
	}
}

void SLCD::updateHomeValues(int axis){
	int XFlag = DRO::getXFlag();
	int YFlag = DRO::getYFlag();
	int ZFlag = DRO::getZFlag();
	int RFlag = DRO::getRFlag();

	if ((XFlag) || (axis == 1)) {
		DRO::getXScl();
		dXVal = DRO::getXPos();
		if ((XFlag == 1) || (axis == 1)){
			sendLCD("m 6 ",0);
			fmtDouble(abs(dXVal),4,cValue,2,9);
			sendLCD(cValue);
			if (dXVal > 0)
				dispXNeg(false);
			else
				dispXNeg(true);
		} else if (XFlag == 2) {
			sendLCD("m 6 ",0);
			fmtDouble(abs(dXVal),4,cValue,2,9);
			sendLCD(cValue);
			dispXNeg(false);
		} else if (XFlag == 3) {
			sendLCD("m 6 ",0);
			fmtDouble(abs(dXVal),4,cValue,2,9);
			sendLCD(cValue);
			dispXNeg(true);
		}
		DRO::clearXFlag();
	}

	if ((YFlag) || (axis == 2)) {
		DRO::getYScl();
		dYVal = DRO::getYPos();
		if ((YFlag == 1) || (axis == 2)){
			sendLCD("m 7 ",0);
			fmtDouble(abs(dYVal),4,cValue,2,9);
			sendLCD(cValue);
			if (dYVal > 0)
				dispYNeg(false);
			else
				dispYNeg(true);
		} else if (YFlag == 2) {
			sendLCD("m 7 ",0);
			fmtDouble(abs(dYVal),4,cValue,2,9);
			sendLCD(cValue);
			dispYNeg(false);
		} else if (YFlag == 3) {
			sendLCD("m 7 ",0);
			fmtDouble(abs(dYVal),4,cValue,2,9);
			sendLCD(cValue);
			dispYNeg(true);
		}
		DRO::clearYFlag();
	}

	if ((ZFlag) || (axis == 3)) {
		DRO::getZScl();
		dZVal = DRO::getZPos();
		if ((ZFlag == 1) || (axis == 3)){
			sendLCD("m 8 ",0);
			fmtDouble(abs(dZVal),4,cValue,2,9);
			sendLCD(cValue);
			if (dZVal > 0)
				dispZNeg(false);
			else
				dispZNeg(true);
		} else if (ZFlag == 2) {
			sendLCD("m 8 ",0);
			fmtDouble(abs(dZVal),4,cValue,2,9);
			sendLCD(cValue);
			dispZNeg(false);
		} else if (ZFlag == 3) {
			sendLCD("m 8 ",0);
			fmtDouble(abs(dZVal),4,cValue,2,9);
			sendLCD(cValue);
			dispZNeg(true);
		}
		DRO::clearZFlag();
	}

	if ((RFlag) || (axis == 4)) {
		DRO::getRScl();
		dRVal = DRO::getRAng();
		if ((RFlag == 1) || (axis == 4)){
			sendLCD("m 9 ",0);
			fmtDouble(abs(dRVal),3,cValue,3,9);
			sendLCD(cValue);
			if (dRVal > 0)
				dispRNeg(false);
			else
				dispRNeg(true);
		} else if (RFlag == 2) {
			sendLCD("m 9 ",0);
			fmtDouble(abs(dRVal),3,cValue,3,9);
			sendLCD(cValue);
			dispRNeg(false);
		} else if (RFlag == 3) {
			sendLCD("m 9 ",0);
			fmtDouble(abs(dRVal),3,cValue,3,9);
			sendLCD(cValue);
			dispRNeg(true);
		}
		DRO::clearRFlag();
	}
}

void SLCD::forceUpdateHomeValues(){
	dXVal = DRO::getXPos();
	dYVal = DRO::getYPos();
	dZVal = DRO::getZPos();
	dRVal = DRO::getRAng();
	
	DRO::getXScl();
	DRO::getYScl();
	DRO::getZScl();
	DRO::getRScl();

	//Are the values negative?
	if(dXVal < 0){
		dispXNeg(TRUE);
	}
	else{
		dispXNeg(FALSE);
	}

	if(dYVal < 0){
		dispYNeg(TRUE);
	}
	else{
		dispYNeg(FALSE);
	}

	if(dZVal < 0){
		dispZNeg(TRUE);
	}
	else{
		dispZNeg(FALSE);
	}

	if(dRVal < 0){
		dispRNeg(TRUE);
	}
	else{
		dispRNeg(FALSE);
	}

	sendLCD("m 2 ",0);
	fmtDouble(abs(dXVal),4,cValue,2,9);
	sendLCD(cValue,0);
	fmtDouble(abs(dYVal),4,cValue,2,9);
	sendLCD(" ",0);
	sendLCD(cValue,0);
	fmtDouble(abs(dZVal),4,cValue,2,9);
	sendLCD(" ",0);
	sendLCD(cValue,0);
	fmtDouble(abs(dRVal),3,cValue,3,9);
	sendLCD(" ",0);
	sendLCD(cValue);
}

void SLCD::updateConfigValues(const double dist, int axis){
	sendLCD("m 4 ",0);
	Serial.println("Starting Config Values Update");
	if (axis == 4) {
		fmtDouble(dist,3,cValue,3,9);
	} else {
		fmtDouble(dist,4,cValue,2,9);
	}
	
	Serial.print("cValue: ");
	Serial.println(cValue);
	sendLCD(cValue);
	Serial.println("Config Values Updated");
}

void SLCD::clearScreen(){
	sendLCD("z");
	sendLCD("z");
}

//Displays negative signs
void SLCD::dispXNeg(bool sign){
	if (sign)
		sendLCD("r 3 80 13 85 1 000");
	else
		sendLCD("r 3 80 13 85 1 fff");
}

void SLCD::dispYNeg(bool sign){
	if (sign)
		sendLCD("r 3 195 13 200 1 000");
	else
		sendLCD("r 3 195 13 200 1 fff");
}

void SLCD::dispZNeg(bool sign){
	if (sign)
		sendLCD("r 245 80 255 85 1 000");
	else
		sendLCD("r 245 80 255 85 1 fff");
}

void SLCD::dispRNeg(bool sign){
	if (sign)
		sendLCD("r 245 195 255 200 1 000");
	else
		sendLCD("r 245 195 255 200 1 fff");
}

//
// Produce a formatted string in a buffer corresponding to the value provided.
// If the 'width' parameter is non-zero, the value will be padded with leading
// zeroes to achieve the specified width.  The number of characters added to
// the buffer (not including the null termination) is returned.
//
unsigned SLCD::fmtUnsigned(unsigned long val, char *buf, unsigned bufLen, unsigned width)
{
	if (!buf || !bufLen)
		return(0);

	// produce the digit string (backwards in the digit buffer)
	char dbuf[10];
	unsigned idx = 0;
	while (idx < sizeof(dbuf)){
		dbuf[idx++] = (val % 10) + '0';
		if ((val /= 10) == 0)
			break;
	}

	// copy the optional leading zeroes and digits to the target buffer
	unsigned len = 0;
	byte padding = (width > idx) ? width - idx : 0;
	char c = '0';
	while ((--bufLen > 0) && (idx || padding)){
		if (padding)
		  padding--;
		else
		  c = dbuf[--idx];
		*buf++ = c;
		len++;
	}

	// add the null termination
	*buf = '\0';
	return(len);
}


//
// Format a floating point value with number of decimal places.
// The 'precision' parameter is a number from 0 to 6 indicating the desired decimal places.
// The 'buf' parameter points to a buffer to receive the formatted string.  This must be
// sufficiently large to contain the resulting string.  The buffer's length may be
// optionally specified.  If it is given, the maximum length of the generated string
// will be one less than the specified value.
//
// example: fmtDouble(3.1415, 2, buf); // produces 3.14 (two decimal places)
//
void SLCD::fmtDouble(double val, byte precision, char *buf, unsigned frontPad, unsigned bufLen)
{
	byte width = 0;
	if (!buf || !bufLen)
		return;

	// limit the precision to the maximum allowed value
	const byte maxPrecision = 6;
	if (precision > maxPrecision)
		precision = maxPrecision;

	if (--bufLen > 0){
    // check for a negative value
	if (val < 0.0){
		val = -val;
		*buf = '-';
		bufLen--;
	}

    // compute the rounding factor and fractional multiplier
    double roundingFactor = 0.5;
    unsigned long mult = 1;
    for (byte i = 0; i < precision; i++){
    	roundingFactor /= 10.0;
    	mult *= 10;
	}

	if (bufLen > 0)
	{
		// apply the rounding factor
		val += roundingFactor;

		// add the integer portion to the buffer
		unsigned len = fmtUnsigned((unsigned long)val, buf, bufLen, frontPad);
		buf += len;
		bufLen -= len;
    }

	// handle the fractional portion
	if ((precision > 0) && (bufLen > 0))
	{
    	*buf++ = '.';
		if (--bufLen > 0)
    	  buf += fmtUnsigned((unsigned long)((val - (unsigned long)val) * mult), buf, bufLen, precision);
		}
	}

	// null-terminate the string
	*buf = '\0';
}
