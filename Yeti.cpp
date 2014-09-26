#include "projectMacros.h"
#include "Yeti.h"


Yeti::Yeti(void)
{
}

Yeti::Yeti(const char* objFile,const char* textureFile,bool addToSceneGraph)
{
	init(objFile,textureFile,addToSceneGraph);
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


void
Yeti::mouseMotion(int x,int y)
{
	
	
	if(INPUT->Mouse.LEFT.HOLD)
		this->rotate(glm::vec3(this->getTransform()->rotation.x+INPUT->Mouse.Movement.x,this->getTransform()->rotation.y,this->getTransform()->rotation.z));
	else if(INPUT->Mouse.MIDDLE.HOLD)
		this->rotate(glm::vec3(this->getTransform()->rotation.x,this->getTransform()->rotation.y,this->getTransform()->rotation.z+INPUT->Mouse.Movement.x));
	else if(INPUT->Mouse.RIGHT.HOLD)
		{
			this->rotate(glm::vec3(this->getTransform()->rotation.x,this->getTransform()->rotation.y+INPUT->Mouse.Movement.x,this->getTransform()->rotation.z));
			this->rotate(glm::vec3(this->getTransform()->rotation.x,this->getTransform()->rotation.y,this->getTransform()->rotation.z+INPUT->Mouse.Movement.y));
		}
}


