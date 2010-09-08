/*
 * The class that contains most of the DRO functionality
 *
 *  Created on: Sep 2, 2010
 *      Author: David Erdos
 */

#ifndef DRO_H_
#define DRO_H_

#include <WProgram.h>
#include <EEPROM.h>

#define INCH	0
#define CM		1
#define SILENT	0
#define QUIET 	1
#define LOUD	2

#define XSCL_ADDR	0
#define YSCL_ADDR	5
#define ZSCL_ADDR	9
#define RSCL_ADDR	13
#define UNIT_ADDR	17
#define VOL_ADDR	19

class DRO {
public:
	DRO();

	//Accessor functions for setup
	static int getUnits();
	static int getVolume();
	static void setUnits(int newUnit);
	static void setVolume(int newVolume);

	//Accessor functions for the axes
	static double getXPos();
	static double getYPos();
	static double getZPos();
	static double getRAng();
	static double updateXPos(long curCount);
	static double updateYPos(long curCount);
	static double updateZPos(long curCount);
	static double updateRAng(long curCount);

	//Accessor functions for axis scaling
	static double getXScl();
	static double getYScl();
	static double getZScl();
	static double getRScl();
	static void setXScl(double newScale);
	static void setYScl(double newScale);
	static void setZScl(double newScale);
	static void setRScl(double newScale);
	static void setXCal(long startCount, long stopCount, double distMoved);
	static void setYCal(long startCount, long stopCount, double distMoved);
	static void setZCal(long startCount, long stopCount, double distMoved);
	static void setRCal(long startCount, long stopCount, double distMoved);

	//Accessor functions for the quadrature counts
	static long getXCnt();
	static long getYCnt();
	static long getZCnt();
	static long getRCnt();
	static void setXCnt(long newCount);
	static void setYCnt(long newCount);
	static void setZCnt(long newCount);
	static void setRCnt(long newCount);
	static void zeroX();
	static void zeroY();
	static void zeroZ();
	static void zeroR();

	static void incXCnt();
	static void incYCnt();
	static void incZCnt();
	static void incRCnt();
	static void decXCnt();
	static void decYCnt();
	static void decZCnt();
	static void decRCnt();

	static void changeXSign();
	static void changeYSign();
	static void changeZSign();
	static void changeRSign();

	static int getXFlag();
	static int getYFlag();
	static int getZFlag();
	static int getRFlag();

	static void clearXFlag();
	static void clearYFlag();
	static void clearZFlag();
	static void clearRFlag();

	static void ledBlink();
	static EEPROMClass eSettings; //Class for writing and reading from EEPROM

private:
	static int ledPin;
	static int ledState;
	static int iUnits;
	static int iVolume;

	static double dXPos; //Current position of the X axis
	static double dXScl; //Scaling factor to convert quadrature counts to position
	static long lXCnt;   //X axis quadrature count

	static double dYPos;
	static double dYScl;
	static long lYCnt;

	static double dZPos;
	static double dZScl;
	static long lZCnt;

	static double dRAng;
	static double dRScl;
	static long lRCnt;

	static int XFlag;
	static int YFlag;
	static int ZFlag;
	static int RFlag;

	static int XSChange;
	static int YSChange;
	static int ZSChange;
	static int RSChange;
};

#endif /* DRO_H_ */
