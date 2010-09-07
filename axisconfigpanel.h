/*
 * The class that contains the axis config panel
 *
 *  Created on: Sep 7, 2010
 *      Author: David Erdos
 */

#ifndef AXISCONFIGPANEL_H_
#define AXISCONFIGPANEL_H_
#include "parent.h"

class AxisConfigPanel : public Panel{
private:
	char axisName;
	long startCount;
	double dist;
	Parent *parent;
public:
	AxisConfigPanel(const int axis, Parent *newParent);

	virtual void initialize();
	virtual void update(char *command);
};

#endif  /* AXISCONFIGPANEL_H_ */
