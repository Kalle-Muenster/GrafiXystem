#ifndef _CONNECTABLE_OBSERVER_
#define _CONNECTABLE_OBSERVER_
#include "projectMacros.h"
#include "InputManager.h"
#include "Connectable.h"



class CInteractive : 
	public IInteractive, public IConnectable
{
public:
	CInteractive(void){}
	virtual ~CInteractive(void){};

	virtual void mouseQlicks(int button,bool IsPressed,glm::vec2 position)
	{
		if(IsPressed)
		printf("button \"%i\" pressed! ",button);
	}

};






#endif