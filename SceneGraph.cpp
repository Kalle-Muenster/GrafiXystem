#include "SceneGraph.h"

SceneGraph* instance;

SceneGraph::SceneGraph(void)
{
	camera = new Cam();
}

SceneGraph::~SceneGraph(void)
{
	delete camera;
}

SceneGraph* SceneGraph::GetInstance()
{
	if(!instance)
		instance = new SceneGraph();

	return instance;
}

void SceneGraph::Add(IGobject* object)
{
	this->drawables.push_back(object);
}



void SceneGraph::DrawAll()
{
	for(auto it = drawables.begin();it!=drawables.end();it++)
		(*it)->draw();
}