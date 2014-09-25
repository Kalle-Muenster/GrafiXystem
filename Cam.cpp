#include "Cam.h"


Cam::Cam(void)
{
	_isFollowingTarget=false;
	this->transform.position.x=0;
	this->transform.position.y=0;
	this->transform.position.z=0;
	this->transform.rotation.x=0;
	this->transform.rotation.y=0;
	this->transform.rotation.z=0;
	this->transform.scale.x=1;
	this->transform.scale.y=1;
	this->transform.scale.z=1;
}


Cam::~Cam(void)
{
	
	delete camTarget;
}

void
Cam::SetTarget(Transform &targetObjectsTransform)
{
	this->camTarget = &targetObjectsTransform.position;
	if (this->camTarget)
		_isFollowingTarget = true;
}

void
Cam::followTarget()
{
	if (this->camTarget)
		_isFollowingTarget = true;
}

void
Cam::StopFollowing()
{
	_isFollowingTarget = false;
}

const
glm::vec3
Cam::GetTargetPosition()
{
	return *this->camTarget;
}

void 
Cam::keyPress(char key)
{

}

void
Cam::mouseMotion(int x,int y)
{

}

void
Cam::specialKeyPressed(int spezial)
{

}

void
Cam::Update()
{
	if(_isFollowingTarget)
	{
		//todo  cam-positioning
	}
}