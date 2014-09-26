#ifndef __ISCHMENA_H__
#define __ISCHMENA_H__


#include <vector>
#include <iostream>

#include "projectGrafics.h"
#include "Utility.h"

class IGobject
{
private:
	
	GLuint vertexBufferID;
	GLuint uvBufferID;
	GLuint textureID;
	Transform transform;
	std::vector<glm::vec3> verts;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> norms;

public:
	virtual Transform* getTransform();
	bool IsVisible;
	IGobject(void);
	virtual ~IGobject(void);
	virtual void draw();
	virtual void init(const char*, const char*);
	virtual void move(glm::vec3);
	virtual void scale(glm::vec3);
	virtual void rotate(glm::vec3);
};

#endif
