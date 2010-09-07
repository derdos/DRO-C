/*
 * homepanel.h
 *
 *  Created on: Sep 3, 2010
 *      Author: David Erdos
 */

#ifndef HOMEPANEL_H_
#define HOMEPANEL_H_

#include "panel.h"

class HomePanel : public Panel {
public:
	virtual void initialize();
	virtual void update(char *command);
};

#endif /* HOMEPANEL_H_ */
