#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include <vector>


class IObserver 
{
public:
	virtual void specialKeyPressed(int key) = 0;
	virtual void keyPress(char key) = 0;
	virtual void mouseMotion(int x, int y) = 0;
};

class InputManager
{
private:
	std::vector<IObserver*> mouseListener;
	std::vector<IObserver*> keyListener;
	std::vector<IObserver*> specialListener;

	InputManager(void);

public:
	static InputManager getInstance();
	virtual void attachMouse(IObserver* obs);
	virtual void attachKey(IObserver* obs);
	virtual void attachSpecial(IObserver* obs);

	virtual void notifySpecialKey(int key);
	virtual void notifyKey(char key);
	virtual void notifyMouse(int x, int y);

	virtual ~InputManager(void);

	void UbdateMouseButtons(int,int,int,int);
	void UpdateMouseWheel(int,int,int,int);

};

#endif