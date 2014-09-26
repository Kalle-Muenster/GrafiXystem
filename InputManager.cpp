#include "InputManager.h"

InputManager* instance;

InputManager* InputManager::getInstance() 
{
	if(!instance) 
	{
		instance = new InputManager();
	}

	return instance;
}

InputManager::InputManager(void)
{
	this->keyListener = std::vector<IObserver*>();
	this->specialListener = std::vector<IObserver*>();
	this->mouseMoveListener = std::vector<IObserver*>();
	this->mouseClickListener = std::vector<IObserver*>();

	Mouse.X=Mouse.Y=0;
	Mouse.Position.x=Mouse.Position.y=0.0f;
	LEFTnewState=MIDDLEnewState=RIGHTnewState=false;
}

InputManager::~InputManager(void)
{

}

void InputManager::attachMouseMove(IObserver* obs) 
{
	if(obs->checkForObservability(OBSERVATE_MOUSE))
		this->mouseMoveListener.push_back(obs);
}

void InputManager::attachKey(IObserver* obs) 
{
	if(obs->checkForObservability(OBSERVATE_KEYBOARD))
	this->keyListener.push_back(obs);
}

void InputManager::attachSpecial(IObserver* obs) 
{
	if(obs->checkForObservability(OBSERVATE_KEYBOARD))
	this->specialListener.push_back(obs);
}

void InputManager::attachMouseClick(IObserver* obs)
{
		if(obs->checkForObservability(OBSERVATE_MOUSE)||obs->checkForObservability(OBSERVATE_CLICKS)||obs->checkForObservability(OBSERVATE_WHEELS))
			this->mouseClickListener.push_back(obs);
}

void InputManager::notifySpecialKey(int key) 
{
	for(auto it = this->specialListener.begin(); it != this->specialListener.end(); ++it) 
	{
		((IInteractive*)(*it))->specialKeyPressed(key);
	}
}

void InputManager::notifyKey(char key) 
{
	for(auto it = this->keyListener.begin(); it != this->keyListener.end(); ++it) 
	{
		((IInteractive*)(*it))->keyPress(key);
	}
}

void InputManager::notifyMouse(int x, int y) 
{
	_setMousePosition(x,y);
	for(auto it = this->mouseMoveListener.begin(); it != this->mouseMoveListener.end(); ++it) 
	{
		((IInteractive*)(*it))->mouseMotion(x,y);
	}
}

void
InputManager::UbdateMouseButtons(int button,int state,int x,int y)
{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			LEFTnewState = state;
			break;
		case GLUT_MIDDLE_BUTTON:
			MIDDLEnewState =  state;
			break;
		case GLUT_RIGHT_BUTTON:
			RIGHTnewState = state;
			break;
		}
		_setMousePosition(x,y);

		for(auto it=mouseClickListener.begin();it!=mouseClickListener.end();it++)
		{
			if((*it)->checkForObservability(OBSERVATE_KEYBOARD))
				((IInteractive*)(*it))->mouseQlicks(button,state==GLUT_DOWN,Mouse.Position);
		}
}

void
InputManager::UpdateMouseWheel(int wheel,int state,int x,int y)
{
		Mouse.WheelV = Mouse.WheelH = 0;

		if(wheel == 0)  // the first mouswheel -> veretical scroll
			Mouse.WheelV = (WHEEL)state;
		else 
		if(wheel == 1)   // the second mousewheel (if your Mouse has one...)
			Mouse.WheelH = (WHEEL)state;
		

}


void InputManager::_setMousePosition(int x,int y)
{
	Mouse.Movement.x = x-Mouse.Position.x;
	Mouse.Movement.y = y-Mouse.Position.y;
	Mouse.Position.x = Mouse.X = x;
	Mouse.Position.y = Mouse.Y = y;
}

void
InputManager::_setMouseButtons()
{
	Mouse.LEFT.RELEASE = Mouse.LEFT.HOLD? !(Mouse.LEFT.HOLD = LEFTnewState):false;
	Mouse.LEFT.CLICK = Mouse.LEFT.CLICK? !(Mouse.LEFT.HOLD = LEFTnewState): !Mouse.LEFT.HOLD? LEFTnewState:false;

	Mouse.RIGHT.RELEASE = Mouse.RIGHT.HOLD? !(Mouse.RIGHT.HOLD = RIGHTnewState):false;
	Mouse.RIGHT.CLICK = Mouse.RIGHT.CLICK? !(Mouse.RIGHT.HOLD = RIGHTnewState): !Mouse.RIGHT.HOLD? RIGHTnewState:false;

	Mouse.MIDDLE.RELEASE = Mouse.MIDDLE.HOLD? !(Mouse.MIDDLE.HOLD = MIDDLEnewState):false;
	Mouse.MIDDLE.CLICK = Mouse.MIDDLE.CLICK? !(Mouse.MIDDLE.HOLD = MIDDLEnewState): !Mouse.MIDDLE.HOLD? MIDDLEnewState:false;

	Mouse.WheelV = Mouse.WheelH = 0;

	if(Mouse.LEFT.CLICK)
	{
		for(auto it = this->mouseClickListener.begin(); it != this->mouseClickListener.end(); ++it) 
		{
			if((*it)->checkForObservability(OBSERVATE_CLICKS))
				((IQlickable*)(*it))->LeftClick(Mouse.Position);
		}
	}

	if(Mouse.RIGHT.CLICK)
	{
		for(auto it = this->mouseClickListener.begin(); it != this->mouseClickListener.end(); ++it) 
		{
			if((*it)->checkForObservability(OBSERVATE_CLICKS))
				((IQlickable*)(*it))->RightClick(Mouse.Position);
		}
	}

	if(Mouse.MIDDLE.CLICK)
	{
		for(auto it = this->mouseClickListener.begin(); it != this->mouseClickListener.end(); ++it) 
		{
			if((*it)->checkForObservability(OBSERVATE_CLICKS))
				((IQlickable*)(*it))->MiddleClick(Mouse.Position);
		}
	}
}

void
InputManager::PerFrameReset(void)
{
	_setMouseButtons();
}

bool
IObserver::checkForObservability(int flag)
{
	return ((observedEvents/flag)<=1);
}

IInteractive::IInteractive()
{
	observedEvents |= OBSERVATE_MOUSE|OBSERVATE_KEYBOARD;
}

IQlickable::IQlickable()
{
	observedEvents |= OBSERVATE_CLICKS|OBSERVATE_MOUSE;
}

IWheelee::IWheelee()
{
	observedEvents |= OBSERVATE_MOUSE|OBSERVATE_WHEELS;
}