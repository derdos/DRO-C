/*
 * homepanel.h
 *
 *  Created on: Sep 3, 2010
 *      Author: David Erdos
 */
#ifndef HOMEPANEL_H_
#define HOMEPANEL_H_

#include <WProgram.h>
#include <WString.h>
#include "panel.h"
#include "axisconfigpanel.h"
#include "parent.h"

class HomePanel : public Panel {
private:
	Parent *parent;
	AxisConfigPanel XConfig;
	AxisConfigPanel YConfig;
	AxisConfigPanel ZConfig;
	AxisConfigPanel RConfig;

public:
	HomePanel(Parent *parent);
	virtual void initialize();
	virtual void update(char *command);
};


#endif /* HOMEPANEL_H_ */
