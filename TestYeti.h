#pragma once
#include "Observer.h"
#include "IGobject.h"
#include "Connectable.h"

class TestYeti :
	public IGobject ,  
	public IUpdateble
{
	public:
	unsigned int ConIDs[MAXIMUM_NUMBER_OF_CONNECTIONS]; 
	int* NumberOfConnectables;


	virtual void KeyPress(char key)
	{
			printf("%c-Pressed! - recieved by TestYeti",key);
	}


	virtual void DoUpdate(void)
	{
				
	}

	TestYeti(const char* objFile,const char* textureFile,bool addToSceneGraph)	
	{ 
		for(int i=0;i<MAXIMUM_NUMBER_OF_CONNECTIONS;i++)
			ConIDs[i]=0;
		init(objFile,textureFile,addToSceneGraph);
	}

	virtual ~TestYeti(void);
};

