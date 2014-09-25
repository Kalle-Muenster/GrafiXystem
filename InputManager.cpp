#include "InputManager.h"

InputManager* instance;

InputManager InputManager::getInstance() 
{
	if(!instance) 
	{
		instance = new InputManager();
	}

	return (*instance);
}

InputManager::InputManager(void)
{
	this->keyListener = std::vector<IObserver*>();
	this->specialListener = std::vector<IObserver*>();
	this->mouseListener = std::vector<IObserver*>();
}

InputManager::~InputManager(void)
{
	//if(instance)
	//	delete instance;
}

void InputManager::attachMouse(IObserver* obs) 
{
	this->mouseListener.push_back(obs);
}

void InputManager::attachKey(IObserver* obs) 
{
	this->keyListener.push_back(obs);
}

void InputManager::attachSpecial(IObserver* obs) 
{
	this->specialListener.push_back(obs);
}

void InputManager::notifySpecialKey(int key) 
{
	for(auto it = this->specialListener.begin(); it != this->specialListener.end(); ++it) 
	{
		(*it)->specialKeyPressed(key);
	}
}

void InputManager::notifyKey(char key) 
{
	for(auto it = this->keyListener.begin(); it != this->keyListener.end(); ++it) 
	{
		(*it)->keyPress(key);
	}
}

void InputManager::notifyMouse(int x, int y) 
{
	for(auto it = this->mouseListener.begin(); it != this->mouseListener.end(); ++it) 
	{
		(*it)->mouseMotion(x,y);
	}
}

void
InputManager::UbdateMouseButtons(int button,int state,int x,int y)
{

}

void
InputManager::UpdateMouseWheel(int wheel,int state,int x,int y)
{

}