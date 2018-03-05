#pragma once
#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>

struct HorseObject {
	glm::mat4 matrix;
	float colour[4];
};

using namespace std;
class Horse
{
public:
	Horse();
	~Horse();

	std::vector<HorseObject*> components;

	void Horse::setTorso(glm::vec3 horseScale, float horseRotateAngle, glm::vec3 horseRotation, glm::vec3 horseTranslation);
	void setNeck(float angle);
	void setHead(float angle);
	void setUpperArmL(float angle);
	void setLowerArmL(float angle);
	void setUpperArmR(float angle);
	void setLowerArmR(float angle);
	void setUpperLegL(float angle);
	void setLowerLegL(float angle);
	void setUpperLegR(float angle);
	void setLowerLegR(float angle);
	void setTail(float angle);

	glm::vec3 horseScale = glm::vec3(2.0f, 1.0f, 1.0f);
	glm::vec3 horseRotation = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 horseTranslation = glm::vec3(0.0f, 4.0f, 0.0f);
	float horseRotateAngle = 0.0f;

private:



	float colValues[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glm::mat4 scale;
	glm::mat4 translate;
	glm::mat4 rotate;

	HorseObject torsoObj;
	HorseObject neckObj;
	HorseObject headObj;
	HorseObject upperArmLObj;
	HorseObject lowerArmLObj;
	HorseObject upperArmRObj;
	HorseObject lowerArmRObj;
	HorseObject upperLegLObj;
	HorseObject lowerLegLObj;
	HorseObject upperLegRObj;
	HorseObject lowerLegRObj;
	HorseObject tailObj;
};

