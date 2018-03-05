#pragma once
class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	GLuint loadBMP(const char * imagepath);
};

