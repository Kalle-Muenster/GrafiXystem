#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#define OBSERVATE_CLICKS       (0x1)
#define OBSERVATE_WHEELS       (0x2)
#define OBSERVATE_KEYBOARD     (0x4)
#define OBSERVATE_MOUSE        (0x8)

#include <vector>
#include "projectGrafics.h"

enum WHEEL{DOWN=-1,NONE=0,UP=1};

class IObserver
{
protected:
	int observedEvents;
public:
	bool checkForObservability(int flag);
};

class IInteractive : IObserver
{

public:
	IInteractive(void);
	virtual void specialKeyPressed(int key){};
	virtual void keyPress(char key){};
	virtual void mouseMotion(int x, int y){};
	virtual void mouseQlicks(int button,bool IsPressed,glm::vec2 position){};
	virtual void mouseWheel(int wheel,WHEEL state){};
};

class IQlickable : IObserver
{
public:
	IQlickable(void);
	virtual void LeftClick(glm::vec2 position){};
	virtual void RightClick(glm::vec2 position){};
	virtual void MiddleClick(glm::vec2 position){};
};

class IWheelee : IObserver
{
public:
	IWheelee(void);
	virtual void WheelVRoll(WHEEL state){};
	virtual void WheelHRoll(WHEEL state){};
};

struct MouseButton
{
public:
	bool CLICK,HOLD,RELEASE;
};






class InputManager
{
private:
	std::vector<IObserver*> mouseMoveListener;
	std::vector<IObserver*> keyListener;
	std::vector<IObserver*> specialListener;

	std::vector<IObserver*> mouseClickListener;

	InputManager(void);

	bool MouseHasUpdated,LEFTnewState,MIDDLEnewState,RIGHTnewState;
	void _setMouseButtons();
	void _setMousePosition(int,int);

public:
	static InputManager* getInstance();
	virtual void attachMouseMove(IObserver* obs);
	virtual void attachKey(IObserver* obs);
	virtual void attachSpecial(IObserver* obs);
	virtual void attachMouseClick(IObserver* obs);

 struct {
	short WheelV;
	short WheelH;
	MouseButton LEFT;
	MouseButton RIGHT;
	MouseButton MIDDLE;
	glm::vec2 Movement;
	glm::vec2 Position;
	int X,Y;
}   Mouse;

	


	virtual void notifySpecialKey(int key);
	virtual void notifyKey(char key);
	virtual void notifyMouse(int x, int y);

	virtual ~InputManager(void);

	void UbdateMouseButtons(int,int,int,int);
	void UpdateMouseWheel(int,int,int,int);
	void PerFrameReset(void);
};

#endif