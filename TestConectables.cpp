#include "TestConectables.h"









void
YetiInteractive::keyPress(char key)
{
	if(this->Connection()->GetObjectID() == (SCENE->camera->GetTarget()->GetObjectID()) )
	{
		float X,Y;
		X=this->Connection()->getTransform()->position.x;
		Y=this->Connection()->getTransform()->position.z;
		switch (key)
			{
			case 'w':
				X+=0.01;
			//	this->Connection()->move(this->Connection()->transform.forward);
				break;
			case 's':
				X-=0.01;
			//	this->Connection()->move(-this->Connection()->transform.forward);
				break;
			case 'a':
				Y+=0.01;
				break;
			case 'd':
				Y-=0.01;
				break;
			}
		this->Connection()->move(Vector3(X,this->Connection()->getTransform()->position.y,Y));
		printf("Keypress (\"%c\") recieved in Connectable,Interactive,Observer ! \n",key);
	}
}


//void
//YetiInteractive::mouseMotion(int x, int y)
//{
//	if(this->Connection()->GetObjectID() == (SCENE->camera->GetTarget()->GetObjectID()) )
//	{
//		if(INPUT->Mouse.LEFT.HOLD)
//			this->Connection()->rotate(glm::vec3(this->Connection()->getTransform()->rotation.x+INPUT->Mouse.Movement.x,this->Connection()->getTransform()->rotation.y,this->Connection()->getTransform()->rotation.z));
//		else if(INPUT->Mouse.MIDDLE.HOLD)
//			this->Connection()->rotate(glm::vec3(this->Connection()->getTransform()->rotation.x,this->Connection()->getTransform()->rotation.y,this->Connection()->getTransform()->rotation.z+INPUT->Mouse.Movement.x));
//		else if(INPUT->Mouse.RIGHT.HOLD)
//		{
//			this->Connection()->rotate(glm::vec3(this->Connection()->getTransform()->rotation.x,this->Connection()->getTransform()->rotation.y+INPUT->Mouse.Movement.x,this->Connection()->getTransform()->rotation.z));
//			this->Connection()->rotate(glm::vec3(this->Connection()->getTransform()->rotation.x,this->Connection()->getTransform()->rotation.y,this->Connection()->getTransform()->rotation.z+INPUT->Mouse.Movement.y));
//		}
//	}
//}