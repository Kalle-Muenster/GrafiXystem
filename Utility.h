#ifndef __UTILITY_H__
#define __UTILITY_H__


#include "projectGrafics.h"
#include <bass.h>
#include <bass_fx.h>
#include <vector>
#include <iostream>


struct Transform 
{
	
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	glm::vec3 *forward,*right,*up;
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