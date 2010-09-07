/*
 * Panel library for the LCD menu control aspect of the DRO
 *
 *  Created on: Sep 2, 2010
 *      Author: David Erdos
 */

#ifndef PANEL_H_
#define PANEL_H_

#include <WProgram.h>

class Panel {
public:
	virtual void initialize();
	virtual void update(char *command);
};

#endif /* PANEL_H_ */
