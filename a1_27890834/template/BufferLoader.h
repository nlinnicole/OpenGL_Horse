#pragma once
#include "objloader.hpp"

class BufferLoader
{
public:
	BufferLoader();
	~BufferLoader();

	GLuint getHorseVAO();
	GLuint getGroundVAO();
	GLuint getAxisVAO();

private:
	GLuint VAO[3];
	GLuint VBO[4];
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

