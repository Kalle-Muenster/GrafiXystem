#ifndef __YETI_INCLUDET__
#define __YETI_INCLUDET__

#include "InputManager.h"
#include "IGobject.h"

class Yeti : IGobject , IObserver
{
public:
	Yeti(void);
	~Yeti(void);
	void IObserver::specialKeyPressed(int key);
	void IObserver::keyPress(char key);
	void IObserver::mouseMotion(int x, int y);

};

#endif