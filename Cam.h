#ifndef __CAMERA__
#define __CAMERA__

#include "Utility.h"
#include "InputManager.h"
#include "IGobject.h"
#include "Connectable.h"

class Cam : public IWheelee , public IConnectable
{

private:
	IGobject*			_target;
	bool				_isFollowingTarget;
	bool				_FollowFirstPerson;
	float				_distanceToTarget;
	glm::vec3			*camTarget;
	ConID				*targetConID;

public:
							Cam(void);
	virtual					~Cam(void);
	
	Transform				transform;
	void					SetTarget(IGobject*);
	void					SetFirstPerson(IGobject*);
	ConID*					SetFirstPerson(IConnectable*);
	IGobject*				GetTarget(void);
	const glm::vec3		GetTargetPosition(void);
	void					followTarget(void);
	void					StopFollowing(void);
	void					Update(void);
	void					SetTargetasFirstPerson(void);
	void					WheelVRoll(WHEEL state);
	
};

#endif