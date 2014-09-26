#ifndef __SCENEGRAPH__
#define __SCENEGRAPH__
#include <vector>
#include "IGobject.h"
#include "Cam.h"

class SceneGraph
{
private:
	SceneGraph(void);
	
	std::vector<IGobject*> drawables;
public:
	~SceneGraph(void);
	static SceneGraph* GetInstance();
	void Add(IGobject*);
	void DrawAll();
	Cam* camera;
};

#endif