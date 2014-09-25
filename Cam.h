#ifndef __CAMERA__
#define __CAMERA__

#include "Utility.h"
#include "InputManager.h"

class Cam : private IObserver
{

private:

	bool			_isFollowingTarget;
	glm::vec3		*camTarget;

public:
					Cam(void);
	virtual			~Cam(void);
	void specialKeyPressed(int key);
	void keyPress(char key);
	void mouseMotion(int x, int y);
	Transform		transform;
	void			SetTarget(Transform&);
	const glm::vec3 GetTargetPosition(void);
	void			followTarget(void);
	void			StopFollowing(void);
	void			Update(void);

};

#endif