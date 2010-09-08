/*
 * LCD Driver for the Reach SLCD34 touch screen module
 *
 *  Created on: Sep 2, 2010
 *      Author: David Erdos
 */

#ifndef SLCD_H_
#define SLCD_H_

#include <WProgram.h>
#include "dro.h"

#define HOME_SCREEN		1
#define SETUP_SCREEN	2
#define XAXIS_CONFIG	3
#define YAXIS_CONFIG	4
#define ZAXIS_CONFIG	5
#define RAXIS_CONFIG	6

class SLCD{
public:
	SLCD();
	static void initializeHome();
	static void initializeConfig(const int axis);
	static void updateHomeValues();
	static void forceUpdateHomeValues();
	static void updateConfigValues(const double dist);
	static void displayAxisConfig(int axis);
	static void displaySetup();
	static void clearScreen();
	static int sendLCD(char *command, int final = 1);

private:
	static double dXVal;
	static double dYVal;
	static double dZVal;
	static double dRVal;
	static char cValue[7];
	static char cBuffer[7];

	static void fmtDouble(double val, byte precision, char *buf, unsigned frontPad, unsigned bufLen = 0xffff);
	static unsigned fmtUnsigned(unsigned long val, char *buf, unsigned bufLen = 0xffff, unsigned width = 0);

	static void dispXNeg(bool sign);
	static void dispYNeg(bool sign);
	static void dispZNeg(bool sign);
	static void dispRNeg(bool sign);
};

#endif /* SLCD_H_ */
