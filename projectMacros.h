#ifndef _POJECT_MACROS__
#define _POJECT_MACROS__

#include "InputManager.h"
#include "SceneGraph.h"

#define INPUT InputManager::getInstance()
#define SCENE SceneGraph::GetInstance()
#define SCREENWIDTH (800)
#define SCREENHEIGHT (600)

#include <irrKlang.h>
#pragma comment(lib,"irrklang.lib")

using namespace irrklang;

#endif