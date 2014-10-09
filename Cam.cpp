#include "Cam.h"
#include "projectMacros.h"

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
	_FollowFirstPerson=false;
	delete camTarget;
}

void
Cam::SetTarget(IGobject *targetObject)
{
	_distanceToTarget = 0.1;
	this->camTarget = &targetObject->getTransform()->position;
	if (this->camTarget)
		_isFollowingTarget = true;
	_target = targetObject;
	_target->IsVisible=true;
	_FollowFirstPerson=false;
}

IGobject* 
Cam::GetTarget(void)
{
	if(_isFollowingTarget||_FollowFirstPerson)
	return _target;
	else
	return NULL;
}

void
Cam::followTarget()
{
	if (this->camTarget)
	{
		_isFollowingTarget = true;
		_FollowFirstPerson = false;
		_target->IsVisible=true;
	}
}

void
Cam::StopFollowing()
{
	_FollowFirstPerson = _isFollowingTarget = false;
	this->GetTarget()->IsVisible=true;
	_target->IsVisible=true;
}

void
Cam::SetFirstPerson(IGobject* personObj)
{
	_target->IsVisible=true;
	_target = personObj;
	_target->IsVisible=false;
	this->camTarget = &personObj->transform.position;
	_isFollowingTarget=false;
	_FollowFirstPerson=true;
}

ConID*
Cam::SetFirstPerson(IConnectable* onPerson)
{
	this->targetConID = this->ConnectConnectableInstance(onPerson);
	this->camTarget = &GetConnected<IConnectable>(*targetConID)->Connection()->transform.position;
	_target->IsVisible=true;
	_target = GetConnected<IConnectable>(*targetConID)->Connection();
	_isFollowingTarget=false;
	_FollowFirstPerson=true;
	return targetConID;
	_target->IsVisible=false;
}

void
Cam::SetTargetasFirstPerson(void)
{
	_target->IsVisible=false;
	_FollowFirstPerson=true;
	_isFollowingTarget=false;
}

const
glm::vec3
Cam::GetTargetPosition()
{
	return *this->camTarget;
}

//void 
//Cam::keyPress(char key)
//{
//
//}
//
//void
//Cam::mouseMotion(int x,int y)
//{
//
//}
//
//void
//Cam::specialKeyPressed(int spezial)
//{
//
//}
void 
Cam::WheelVRoll(WHEEL state)
{
	transform.position.y+=(float)state/10;
}

void
Cam::Update()
{
	if(_isFollowingTarget)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(transform.position.x, transform.position.y, transform.position.z, camTarget->x,camTarget->y,camTarget->z, 0, 1, 0);
	}
	if(_FollowFirstPerson)
	{
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		this->transform = _target->transform;

		gluLookAt(transform.position.x, transform.position.y+1, transform.position.z, transform.rotation.x,transform.rotation.y,transform.rotation.z, 0, 1, 0);
	}
}

