/*
 * The class that contains the setup panel
 *
 *  Created on: Sep 15, 2010
 *      Author: David Erdos
 */

#ifndef JOGPANEL_H_
#define JOGPANEL_H_
#include "parent.h"

class JogPanel : public Panel{
private:
	Parent *parent;
public:
	JogPanel(Parent *newParent);
	
	virtual void initialize();
	virtual void update(char *command);
};

#endif  /* JOGPANEL_H_ */
