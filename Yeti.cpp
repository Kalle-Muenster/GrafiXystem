#include "projectMacros.h"
#include "Yeti.h"


Yeti::Yeti(void)
{
}

Yeti::Yeti(const char* objFile,const char* textureFile,bool addToSceneGraph)
{
	init(objFile,textureFile,addToSceneGraph);
	INPUT->attachKey(this);
}

Yeti::~Yeti(void)
{
}

void
Yeti::keyPress(char key)
{
	float X,Y;
	X=this->getTransform()->position.x;
	Y=this->getTransform()->position.z;
	switch (key)
	{
	case 'w':
		X+=0.01;
		break;
	case 's':
		X-=0.01;
		break;
	case 'a':
		Y+=0.01;
		break;
	case 'd':
		Y-=0.01;
		break;
	}
	this->move(glm::vec3(X,this->getTransform()->position.y,Y));
	std::cout<<"Key Pressed ! : ";
	printf("%c\n",key);
}



