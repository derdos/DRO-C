/*
 * Parent library for the LCD menu control aspect of the DRO
 *
 *  Created on: Sep 2, 2010
 *      Author: David Erdos
 */

#ifndef PARENT_H_
#define PARENT_H_

#include <WProgram.h>
#include <WString.h>
#include "panel.h"

class Parent {
private:
	unsigned int iBufferSize;
	unsigned int iIndex;
	char cEOL;
	Panel *curPanel;
	Panel *lastPanel;
	Panel *homePanel;
	char sReadBuffer[5];

	int upVal = 0;
	int dnVal = 0;
	int rtVal = 0;
	int ltVal = 0;

	int upPrev = 0;
	int dnPrev = 0;
	int rtPrev = 0;
	int ltPrev = 0;

public:
	Parent();
	void run();
	void pushPanel(Panel *panel);
	void popPanel();
	void clearBuffer();
	void setHomePanel(Panel *panel);
	void jogUpdate();
};

#endif /* PARENT_H_ */
