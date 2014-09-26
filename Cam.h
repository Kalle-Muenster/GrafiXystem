#ifndef __CAMERA__
#define __CAMERA__

#include "Utility.h"
#include "InputManager.h"
#include "IGobject.h"

class Cam : public IWheelee
{

private:

	bool			_isFollowingTarget;
	float           _distanceToTarget;
	glm::vec3		*camTarget;

public:
					Cam(void);
	virtual			~Cam(void);
	void specialKeyPressed(int key);
	void keyPress(char key);
	void mouseMotion(int x, int y);
	Transform		transform;
	void			SetTarget(IGobject*);
	const glm::vec3 GetTargetPosition(void);
	void			followTarget(void);
	void			StopFollowing(void);
	void			Update(void);

	
};

#endif