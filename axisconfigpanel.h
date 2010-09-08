/*
 * The class that contains the axis config panel
 *
 *  Created on: Sep 7, 2010
 *      Author: David Erdos
 */

#ifndef AXISCONFIGPANEL_H_
#define AXISCONFIGPANEL_H_
#include "parent.h"
#include "WString.h"

class AxisConfigPanel : public Panel{
private:
	char axisName;
	int axisNum;
	long startCount;
	double dist;
	Parent *parent;
	String input;
public:
	AxisConfigPanel(const int axis, Parent *newParent);

	virtual void initialize();
	virtual void update(char *command);

	bool isValid(String value);
	bool containsDecimal(String value);
};

#endif  /* AXISCONFIGPANEL_H_ */
