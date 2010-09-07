/*
 * The class that contains the axis config panel
 *
 *  Created on: Sep 7, 2010
 *      Author: David Erdos
 */

#ifndef AXISCONFIGPANEL_H_
#define AXISCONFIGPANEL_H_

class AxisConfigPanel{
private:
	char axisName;
	long startCount;
	double dist;
public:
	AxisConfigPanel(const int axis);

	virtual void initialize();
	virtual void update(char *command);
};

#endif  /* AXISCONFIGPANEL_H_ */
