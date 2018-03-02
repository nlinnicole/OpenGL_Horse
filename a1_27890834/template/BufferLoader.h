#pragma once
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
	GLuint VBO[3];

	void setHorseVAO();
	void setGroundVAO();
	void setAxisVAO();
};

