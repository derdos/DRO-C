/*
 * The class that contains most of the DRO functionality
 *
 *  Created on: Sep 2, 2010
 *      Author: David Erdos
 */

#include "dro.h"

const double MIN_SCL = 0.00001;

EEPROMClassMod DRO::eSettings; //Class for writing and reading from EEPROM

int DRO::XFlag;
int DRO::YFlag;
int DRO::ZFlag;
int DRO::RFlag;

int DRO::ledPin;
int DRO::ledState;
int DRO::iUnits;
int DRO::iVolume;
double DRO::dXPos; //Current position of the X axis
double DRO::dXScl; //Scaling factor to convert quadrature counts to position
long DRO::lXCnt;   //X axis quadrature count

double DRO::dYPos;
double DRO::dYScl;
long DRO::lYCnt;

double DRO::dZPos;
double DRO::dZScl;
long DRO::lZCnt;

double DRO::dRAng;
double DRO::dRScl;
long DRO::lRCnt;

DRO::DRO(){
	ledPin = 13;
	ledState = 1;

	iUnits = 0;
	iVolume = 0;

	dXPos = 0;
	dXScl = eSettings.readDouble(XSCL_ADDR);
	lXCnt = 0;

	dYPos = 0;
	dYScl = eSettings.readDouble(YSCL_ADDR);
	lYCnt = 0;

	dZPos = 0;
	dZScl = eSettings.readDouble(ZSCL_ADDR);
	lZCnt = 0;

	dRAng = 0;
	dRScl = eSettings.readDouble(RSCL_ADDR);
	lRCnt = 0;

	XFlag = 0;
	YFlag = 0;
	ZFlag = 0;
	RFlag = 0;
	
	setVolume(getVolume());
}

int DRO::getUnits(){
	iUnits = eSettings.readInt(UNIT_ADDR);
	return iUnits;
}

int DRO::getVolume(){
	iVolume = eSettings.readInt(VOL_ADDR);
	return iVolume;
}

void DRO::setUnits(int newUnit){
	if ((newUnit <= 1) && (newUnit >= 0)){
		if ((iUnits == INCH) && (newUnit == CM)) {
			setXScl(getXScl()*2.54);
			setYScl(getYScl()*2.54);
			setZScl(getZScl()*2.54);
			setRScl(getRScl()*2.54);
		}
		else if ((iUnits == CM) && (newUnit == INCH)) {
			setXScl(getXScl()/2.54);
			setYScl(getYScl()/2.54);
			setZScl(getZScl()/2.54);
			setRScl(getRScl()/2.54);
		}
		iUnits = newUnit;
		eSettings.writeInt(UNIT_ADDR,iUnits);
	}
}

void DRO::setVolume(int newVolume){
	if ((newVolume <= 2)&(newVolume >= 0))
		iVolume = newVolume;
		eSettings.writeInt(VOL_ADDR,iVolume);
}

//Accessor functions for the axes
double DRO::getXPos(){
	dXPos = lXCnt * dXScl;
	if(dXPos > 99.9999)
		dXPos = 99.9999;
	else if (dXPos < -99.9999)
		dXPos = -99.9999;
	return dXPos;
}

double DRO::getYPos(){
	dYPos = lYCnt * dYScl;
	if(dYPos > 99.9999)
		dYPos = 99.9999;
	else if (dYPos < -99.9999)
		dYPos = -99.9999;
	return dYPos;
}

double DRO::getZPos(){
	dZPos = lZCnt * dZScl;
	if(dZPos > 99.9999)
		dZPos = 99.9999;
	else if (dZPos < -99.9999)
		dZPos = -99.9999;
	return dZPos;
}

double DRO::getRAng(){
	dRAng = lRCnt * dRScl;
	if(dRAng > 999.999)
		dRAng = 999.999;
	else if (dRAng < -999.999)
		dRAng = -999.999;
	return dRAng;
}

double DRO::updateXPos(long curCount){
	dXPos = curCount / dXScl;
	return dXPos;
}

double DRO::updateYPos(long curCount){
	dYPos = curCount / dYScl;
	return dYPos;
}
double DRO::updateZPos(long curCount){
	dZPos = curCount / dZScl;
	return dZPos;
}

double DRO::updateRAng(long curCount){
	dRAng = curCount / dRScl;
	return dRAng;
}

//Accessor functions for axis scaling
double DRO::getXScl(){
	dXScl = eSettings.readDouble(XSCL_ADDR);
	if (dXScl == 0)
		dXScl = MIN_SCL;
	return dXScl;
}

double DRO::getYScl(){
	dYScl = eSettings.readDouble(YSCL_ADDR);
	if (dYScl == 0)
		dYScl = MIN_SCL;
	return dYScl;
}

double DRO::getZScl(){
	dZScl = eSettings.readDouble(ZSCL_ADDR);
	if (dZScl == 0)
		dZScl = MIN_SCL;
	return dZScl;
}

double DRO::getRScl(){
	dRScl = eSettings.readDouble(RSCL_ADDR);
	if (dRScl == 0)
		dRScl = MIN_SCL;
	return dRScl;
}

void DRO::setXScl(double newScale){
	dXScl = newScale;
	eSettings.writeDouble(XSCL_ADDR,dXScl);
}

void DRO::setYScl(double newScale){
	dYScl = newScale;
	eSettings.writeDouble(YSCL_ADDR,dYScl);
}

void DRO::setZScl(double newScale){
	dZScl = newScale;
	eSettings.writeDouble(ZSCL_ADDR,dZScl);
}

void DRO::setRScl(double newScale){
	dRScl = newScale;
	eSettings.writeDouble(RSCL_ADDR,dRScl);
}

void DRO::setXCal(long startCount, long stopCount, double distMoved){
	dXScl = distMoved / (stopCount - startCount);
	if (dXScl == 0)
		dXScl = MIN_SCL;
	eSettings.writeDouble(XSCL_ADDR,dXScl);
}

void DRO::setYCal(long startCount, long stopCount, double distMoved){
	dYScl = distMoved / (stopCount - startCount);
	if (dYScl == 0)
			dYScl = MIN_SCL;
	eSettings.writeDouble(YSCL_ADDR,dYScl);
}

void DRO::setZCal(long startCount, long stopCount, double distMoved){
	dZScl = distMoved / (stopCount - startCount);
	if (dZScl == 0)
			dZScl = MIN_SCL;
	eSettings.writeDouble(ZSCL_ADDR,dZScl);
}

void DRO::setRCal(long startCount, long stopCount, double distMoved){
	dRScl = distMoved / (stopCount - startCount);
	if (dRScl == 0)
			dRScl = MIN_SCL;
	eSettings.writeDouble(RSCL_ADDR,dRScl);
}

//Accessor functions for the quadrature counts
long DRO::getXCnt(){
	return lXCnt;
}

long DRO::getYCnt(){
	return lYCnt;
}

long DRO::getZCnt(){
	return lZCnt;
}

long DRO::getRCnt(){
	return lRCnt;
}

void DRO::setXCnt(long newCount){
	lXCnt = newCount;
}

void DRO::setYCnt(long newCount){
	lYCnt = newCount;
}

void DRO::setZCnt(long newCount){
	lZCnt = newCount;
}

void DRO::setRCnt(long newCount){
	lRCnt = newCount;
}

void DRO::zeroX(){
	lXCnt = 0;
	dXPos = 0;
}

void DRO::zeroY(){
	lYCnt = 0;
	dYPos = 0;
}

void DRO::zeroZ(){
	lZCnt = 0;
	dZPos = 0;
}

void DRO::zeroR(){
	lRCnt = 0;
	dRAng = 0;
}

void DRO::changeXSign(){
	dXScl = -dXScl;
	eSettings.writeDouble(XSCL_ADDR,dXScl);
}

void DRO::changeYSign(){
	dYScl = -dYScl;
	eSettings.writeDouble(YSCL_ADDR,dYScl);
}

void DRO::changeZSign(){
	dZScl = -dZScl;
	eSettings.writeDouble(ZSCL_ADDR,dZScl);
}

void DRO::changeRSign(){
	dRScl = -dRScl;
	eSettings.writeDouble(RSCL_ADDR,dRScl);
}

void DRO::incXCnt(){
	if (lXCnt == -1)
		XFlag = 2;
	else
		XFlag = 1;
	lXCnt++;
}

void DRO::incYCnt(){
	if (lYCnt == -1)
		YFlag = 2;
	else
		YFlag = 1;
	lYCnt++;
}

void DRO::incZCnt(){
	if (lZCnt == -1)
		ZFlag = 2;
	else
		ZFlag = 1;
	lZCnt++;
}

void DRO::incRCnt(){
	if (lRCnt == -1)
		RFlag = 2;
	else
		RFlag = 1;
	lRCnt++;
}

void DRO::decXCnt(){
	if (lXCnt == 0)
		XFlag = 3;
	else
		XFlag = 1;
	lXCnt--;
}

void DRO::decYCnt(){
	if (lYCnt == 0)
		YFlag = 3;
	else
		YFlag = 1;
	lYCnt--;
}

void DRO::decZCnt(){
	if (lZCnt == 0)
		ZFlag = 3;
	else
		ZFlag = 1;
	lZCnt--;
}

void DRO::decRCnt(){
	if (lRCnt == 0)
		RFlag = 3;
	else
		RFlag = 1;
	lRCnt--;
}

void DRO::ledBlink(){
	if(ledState){
		ledState = 0;
		digitalWrite(ledPin, LOW);
	}
	else{
		ledState = 1;
		digitalWrite(ledPin, HIGH);
	}
}

int DRO::getXFlag(){
	return XFlag;
}

int DRO::getYFlag(){
	return YFlag;
}

int DRO::getZFlag(){
	return ZFlag;
}

int DRO::getRFlag(){
	return RFlag;
}

void DRO::clearXFlag(){
	XFlag = 0;
}

void DRO::clearYFlag(){
	YFlag = 0;
}

void DRO::clearZFlag(){
	ZFlag = 0;
}

void DRO::clearRFlag(){
	RFlag = 0;
}
