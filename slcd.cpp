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
}

char SLCD::readBlocking(){
	int c = -1;
	while((c = Serial3.read()) == -1){
		c = Serial3.read();
	}
	return c;
}

void SLCD::readAck(){
	char c = readBlocking();
	char r = readBlocking();
	Serial.print("r = ");
	Serial.println((double)r);
	Serial.print("c = ");
	Serial.println((double)c);
	Serial.flush();

	if(c == '^'){
		Serial.println("Buffer Overflow");
		readAck();
	} else if(c == '>') {
		Serial.println("Ack Received");
	} else {
		Serial.print("Invalid Ack:(");
		Serial.print((double) c);
		Serial.println(")");
	}
}

void SLCD::SendLCD(char *text){
	Serial3.println(text);
	readAck();
}

void SLCD::initializeLCD(){
	//Clear the screen twice just to be sure
	SendLCD("z");
	SendLCD("z");

	//Display the home screen
	if (DRO::getUnits()) { //0 means centimeters
		SendLCD("m 1:cm 00.0000 00.0000 00.0000 000.000");
	}
	else {
		SendLCD("m 1:in 00.0000 00.0000 00.0000 000.000");
	}
	DRO::getXScl();
	DRO::getYScl();
	DRO::getZScl();
	DRO::getRScl();
}

void SLCD::updateHomeValues(){
	dXVal = DRO::getXPos();
	dYVal = DRO::getYPos();
	dZVal = DRO::getZPos();
	dRVal = DRO::getRAng();

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

	Serial3.print("m 2 ");
	fmtDouble(abs(dXVal),4,cValue,2,9);
	Serial3.print(cValue);
	fmtDouble(abs(dYVal),4,cValue,2,9);
	Serial3.print(" ");
	Serial3.print(cValue);
	fmtDouble(abs(dZVal),4,cValue,2,9);
	Serial3.print(" ");
	Serial3.print(cValue);
	fmtDouble(abs(dRVal),3,cValue,3,9);
	Serial3.print(" ");
	SendLCD(cValue);
}

void SLCD::displayAxisConfig(int axis){
	if (axis == XAXIS_CONFIG) {
		SendLCD("m 3:x");
		SendLCD("m 4 00.0000");
	}
	else if (axis == YAXIS_CONFIG){
		SendLCD("m 3:y");
		SendLCD("m 4 00.0000");
	}
	else if (axis == ZAXIS_CONFIG){
		SendLCD("m 3:z");
		SendLCD("m 4 00.0000");
	}
	else {
		SendLCD("m 3:r");
		SendLCD("m 4 00.0000");
	}
}

void SLCD::clearScreen(){
	SendLCD("z");
	SendLCD("z");
}

//Displays negative signs
void SLCD::dispXNeg(bool sign){
	if (sign)
		SendLCD("r 3 80 13 85 1 000");
	else
		SendLCD("r 3 80 13 85 1 fff");
}

void SLCD::dispYNeg(bool sign){
	if (sign)
		SendLCD("r 3 195 13 200 1 000");
	else
		SendLCD("r 3 195 13 200 1 fff");
}

void SLCD::dispZNeg(bool sign){
	if (sign)
		SendLCD("r 245 80 255 85 1 000");
	else
		SendLCD("r 245 80 255 85 1 fff");
}

void SLCD::dispRNeg(bool sign){
	if (sign)
		SendLCD("r 245 195 255 200 1 000");
	else
		SendLCD("r 245 195 255 200 1 fff");
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
