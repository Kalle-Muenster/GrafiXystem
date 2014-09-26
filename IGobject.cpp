#include "projectMacros.h"
#include "IGobject.h"
#include "Utility.h"

IGobject::IGobject(void)
{
	IsVisible=false;
}



IGobject::~IGobject(void)
{

}

void IGobject::init(const char* objFile,const char* textureFile,bool addToSceneGraph)
{
	this->init(objFile,textureFile);

	if(addToSceneGraph)
		SCENE->Add(this);
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

Transform* IGobject::getTransform()
{
	return &this->transform;
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
		glPushMatrix();
		{
		glBindTexture(GL_TEXTURE_2D, textureID);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
	
	
		//glRotatef(-90, 1, 0, 0);
		glTranslatef(this->transform.position.x, this->transform.position.y, this->transform.position.z);

		glDrawArrays(GL_TRIANGLES, 0, verts.size());
		}
		glPopMatrix();
	}
}