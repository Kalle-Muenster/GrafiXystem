#include "projectMacros.h"
#include "projectGrafics.h"
#include "Utility.h"

Vector3::Vector3(void)
{
	x=y=z=0.0f;
}

Vector3::Vector3(float X,float Y,float Z)
{
	bassVector.x = x = X;
	bassVector.y = y = Y;
	bassVector.z = z = Z;
}
Vector3::Vector3(glm::vec3 glVector)
{
	bassVector.x = x = glVector.x;
	bassVector.y = y = glVector.y;
	bassVector.z = z = glVector.z;
}
Vector3::operator BASS_3DVECTOR()
{
	return BASS_3DVECTOR(this->x,this->y,this->z);
}

Vector3
Vector3::operator+(Vector3 adder)
{
	return Vector3(this->x + adder.x,this->y + adder.y,this->z + adder.z);
}

Vector3
Vector3::operator-(Vector3 subtractor)
{
	return Vector3(this->x - subtractor.x,this->y - subtractor.y,this->z - subtractor.z);
}

BASS_3DVECTOR*
Vector3::asBassVector(void)
{
	bassVector.x = this->x;
	bassVector.y = this->y;
	bassVector.z = this->z;
	return &bassVector;
}

void
Utility::loadObj(const char* filename,  std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals)
{
	std::vector<unsigned int> vertexIndices, vertexTextureIndices, normalIndices;

	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempVertexTextures;
	std::vector<glm::vec3> tempNormals;

	FILE* file = fopen(filename, "r");

	if(file == NULL) 
	{
		std::cerr << "File not found" << filename << std::endl;
		exit(1);
	}

	while(1) 
	{
		char line[32];

		int res = fscanf(file, "%s", line);

		if(res == -1) 
		{
			break;
		}

		if(strcmp(line, "v") == 0) 
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		}
		else if(strcmp(line, "vt") == 0) 
		{
			glm::vec2 vertexTexture;
			fscanf(file, "%f %f\n", &vertexTexture.x, &vertexTexture.y);
			tempVertexTextures.push_back(vertexTexture);
		}
		else if(strcmp(line, "vn") == 0) 
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		}
		else if(strcmp(line, "f") == 0) 
		{
			unsigned int tempVertexIndex[3], tempVertexTextureIndex[3],
				tempNormalIndex[3];

			fscanf(file, "%d/%d %d/%d %d/%d\n", 
				&tempVertexIndex[0], &tempVertexTextureIndex[0],
				&tempVertexIndex[1], &tempVertexTextureIndex[1],
				&tempVertexIndex[2], &tempVertexTextureIndex[2]
			);

			vertexIndices.push_back(tempVertexIndex[0]);
			vertexTextureIndices.push_back(tempVertexTextureIndex[0]);
			normalIndices.push_back(tempNormalIndex[0]);

			vertexIndices.push_back(tempVertexIndex[1]);
			vertexTextureIndices.push_back(tempVertexTextureIndex[1]);
			normalIndices.push_back(tempNormalIndex[0]);

			vertexIndices.push_back(tempVertexIndex[2]);
			vertexTextureIndices.push_back(tempVertexTextureIndex[2]);
			normalIndices.push_back(tempNormalIndex[0]);
		}
	}

	for(int i = 0; i < vertexIndices.size(); i++) 
	{
		glm::vec3 vertex = tempVertices[vertexIndices[i] -1];
		vertices.push_back(vertex);
	}

	for(int i = 0; i < vertexTextureIndices.size(); i++) 
	{
		glm::vec2 uv = tempVertexTextures[vertexTextureIndices[i] - 1];
		uvs.push_back(uv);
	}
}


GLuint
Utility::loadTexture(const char* filename)
{

	glload::LoadTest loadTest = glload::LoadFunctions();

	try
	{
		std::auto_ptr<glimg::ImageSet> pImageSet(glimg::loaders::stb::LoadFromFile(filename));
		return glimg::CreateTexture(pImageSet.get(), 0);
	}
	catch(glimg::loaders::stb::StbLoaderException &e)
	{
		std::cerr << "Failed loading file";
	}
	catch(glimg::TextureGenerationException &e)
	{
		std::cerr << "Texture creation failed";
	}

	return 0;
}



