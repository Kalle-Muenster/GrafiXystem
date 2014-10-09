#ifndef __ISCHMENA_H__
#define __ISCHMENA_H__


#include <vector>
#include <iostream>

#include "projectGrafics.h"
#include "Utility.h"
#include "UpdateManager.h"

class IConnectable;


typedef unsigned GobID;

class IGobject 
{
private:
	bool _idIsSet;
protected:
	GobID ID;
	GLuint vertexBufferID;
	GLuint uvBufferID;
	GLuint textureID;
	
	std::vector<glm::vec3> verts;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> norms;

public:
	Transform transform;
	virtual Transform* getTransform();
	bool IsVisible;
	IGobject(void);
	virtual ~IGobject(void);
	virtual void draw();
	virtual void init(const char* objFile,const char* textureFile);
	virtual void init(const char* objFile,const char* textureFile,bool addToSceneGraph);
	virtual void move(glm::vec3);

	virtual void scale(glm::vec3);
	virtual void rotate(glm::vec3);
	GobID GetObjectID(void);
	IConnectable* conXtor;

};



#endif
