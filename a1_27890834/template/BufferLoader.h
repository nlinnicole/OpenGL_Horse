#pragma once
#include "objloader.hpp"
#include "SOIL.h"

class BufferLoader
{
public:
	BufferLoader();
	~BufferLoader();

	GLuint getHorseVAO();
	GLuint getGroundVAO();
	GLuint getAxisVAO();
	GLuint getGridVAO();

	GLuint getHorseTex();
	GLuint getGroundTex();

	void loadTex();
	void deleteTex();

private:
	GLuint VAO[4];
	GLuint VBO[8];
	GLuint EBO;
	GLuint tex[2];

	GLuint texLoc;

	std::vector<glm::vec3> hVertices;
	std::vector<glm::vec3> hNormals;
	std::vector<glm::vec2> hUvCoord;

	std::vector<glm::vec3> gVertices;
	std::vector<glm::vec3> gNormals;
	std::vector<glm::vec2> gUvCoord;

	std::vector<glm::vec3> ground;

	void setHorseVAO();
	void setGroundVAO();
	void setAxisVAO();
	void setGridVAO();
};

