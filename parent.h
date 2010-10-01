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

	int upVal;
	int dnVal;
	int rtVal;
	int ltVal;

	int upPrev;
	int dnPrev;
	int rtPrev;
	int ltPrev;

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
