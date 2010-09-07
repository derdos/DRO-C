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
	String sReadBuffer;

public:
	Parent();
	void run();
	void pushPanel(Panel *panel);
	void popPanel();
	void clearBuffer();
};

#endif /* PARENT_H_ */
