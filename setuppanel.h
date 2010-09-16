/*
 * The class that contains the setup panel
 *
 *  Created on: Sep 15, 2010
 *      Author: David Erdos
 */

#ifndef SETUPPANEL_H_
#define SETUPPANEL_H_
#include "parent.h"

class SetupPanel : public Panel{
private:
	Parent *parent;
public:
	SetupPanel(Parent *newParent);
	
	virtual void initialize();
	virtual void update(char *command);
};

#endif  /* SETUPPANEL_H_ */
