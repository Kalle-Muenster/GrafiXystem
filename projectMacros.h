#ifndef _POJECT_MACROS__
#define _POJECT_MACROS__


#include "InputManager.h"
#include "SceneGraph.h"
#include "UpdateManager.h"
#include "BassAudio.h"


#define SCREENWIDTH (800)
#define SCREENHEIGHT (600)


#include <windows.h>



#define INPUT InputManager::getInstance()
#define SCENE SceneGraph::GetInstance()
#define UPDATE UpdateManager::getInstance()
#define AUDIO BassAudio::GetInstance()

#endif