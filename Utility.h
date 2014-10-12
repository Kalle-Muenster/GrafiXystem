#ifndef __UTILITY_H__
#define __UTILITY_H__


#include "projectGrafics.h"
#include <bass.h>
#include <bass_fx.h>
#include <vector>
#include <iostream>

struct Vector3 : public glm::vec3
{
private:
	BASS_3DVECTOR bassVector;
public:
	Vector3(void);
	Vector3(float,float,float);
	Vector3(glm::vec3);
	operator BASS_3DVECTOR();
	Vector3 operator+(Vector3);
	Vector3 operator-(Vector3);
	BASS_3DVECTOR* asBassVector(void);
};

struct Transform 
{
	
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	glm::vec3 forward,right,up;
};

struct TransformA
{
	
	Vector3 position;
	Vector3 scale;
	BASS_3DVECTOR movement;
	Vector3 rotation;

	Vector3 forward,right,up;
};

class Utility 
{
private:
	Utility();
	virtual ~Utility();
public:
	static void loadObj(const char*,  std::vector<glm::vec3> &, std::vector<glm::vec2> &, std::vector<glm::vec3> &);
	static GLuint loadTexture(const char *);

};

#endif