#include "IGobject.h"
#include "Utility.h"

IGobject::IGobject(void)
{
	IsVisible=false;
}


IGobject::~IGobject(void)
{

}


void IGobject::init(const char* objFile, const char* textureFile)
{
	Utility::loadObj(objFile,this->verts,this->uvs,this->norms);
	this->textureID = Utility::loadTexture(textureFile);

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec3), &verts[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	IsVisible = true;
}

const Transform IGobject::getTransform()
{
	return this->transform;
}

void IGobject::move(glm::vec3 to)
{
	this->transform.position = to;
}

void IGobject::scale(glm::vec3 to)
{
	this->transform.scale = to;
}

void IGobject::rotate(glm::vec3 to)
{
	this->transform.rotation = to;
}

void IGobject::draw()
{
	if(IsVisible)
	{
		//todo drawcode...
	}
}