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
	void loadTex();


private:
	GLuint VAO[3];
	GLuint VBO[5];
	GLuint EBO;
	GLuint tex;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvCoord;

	std::vector<glm::vec3> ground;

	void setHorseVAO();
	void setGroundVAO();
	void setAxisVAO();
};

