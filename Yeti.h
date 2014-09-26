#ifndef __YETI_INCLUDET__
#define __YETI_INCLUDET__

#include "InputManager.h"
#include "IGobject.h"

class Yeti : public IGobject ,public IInteractive
{
public:
	Yeti(void);
	Yeti(const char* objFile,const char* textureFile,bool addToSceneGraph);
	~Yeti(void);


	void keyPress(char);
	void mouseMotion(int,int);
};

#endif