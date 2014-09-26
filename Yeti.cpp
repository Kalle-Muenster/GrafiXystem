#include "projectMacros.h"
#include "Yeti.h"


Yeti::Yeti(void)
{
}

Yeti::Yeti(const char* objFile,const char* textureFile,bool addToSceneGraph)
{
	this->init(objFile,textureFile);
	if(addToSceneGraph)
		SCENE->Add(this);
}

Yeti::~Yeti(void)
{
}


void
Yeti::mouseMotion(int x,int y)
{
	this->move(glm::vec3((float)x/-1000,this->getTransform()->position.y,(float)y/-1000));

}


