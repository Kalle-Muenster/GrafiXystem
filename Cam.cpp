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
	this->transform.movement.x=0;
	this->transform.movement.y=0;
	this->transform.movement.z=0;


	InitiateListener(&this->transform);
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

BASS_3DVECTOR
Cam::move(glm::vec3  newPosition)
{
		this->transform.movement.x = newPosition.x - this->transform.position.x;
		this->transform.movement.y = newPosition.y - this->transform.position.y;
		this->transform.movement.z = newPosition.z - this->transform.position.z;

		this->transform.position.x = newPosition.x;
		this->transform.position.y = newPosition.y;
		this->transform.position.z = newPosition.z;



		SetMyPosition(&this->transform);
		DebugOutPosition();

		return transform.position;
}

BASS_3DVECTOR
Cam::rotate(glm::vec3 newRotation)
{
		this->transform.rotation.x = newRotation.x;
		this->transform.rotation.y = newRotation.y;
		this->transform.rotation.z = newRotation.z;

		this->transform.forward = glm::normalize((glm::vec3)this->transform.rotation);

		return this->transform.rotation;
}

void
Cam::Update()
{
	if(_isFollowingTarget)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		this->rotate(*camTarget);

		gluLookAt(transform.position.x, transform.position.y, transform.position.z, camTarget->x,camTarget->y,camTarget->z, 0, 1, 0);
	}
	if(_FollowFirstPerson)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		this->move(*camTarget);

		gluLookAt(camTarget->x, camTarget->y, camTarget->z, _target->transform.rotation.x+=INPUT->Mouse.Movement.x,(_target->transform.rotation.y+=INPUT->Mouse.Movement.y),_target->transform.rotation.z+=INPUT->Mouse.Movement.x, 0, 1, 0);
	}
}

