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

	void setTorso();
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

	void translateHorse(glm::vec3 translation);
	void scaleHorse(glm::vec3 scale);
	void rotateHorse(float angle, glm::vec3 rotation);

	void animateHorse();
	void resetHorse();

	void moveHorse();

	//COLLISION
	HorseObject hColObj;
	void Horse::setCol();
	int getStepCounter();

private:
	float colValues[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glm::vec3 initScale = glm::vec3(2.0f, 1.0f, 1.0f);
	glm::vec3 initRotation = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 initTranslation = glm::vec3(0.0f, 4.0f, 0.0f);

	glm::vec3 scaling;
	float angle;
	glm::vec3 rotation;
	glm::vec3 translation;

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

	void setHorseRender();

	//HORSE ANIMATION
	GLfloat deltaX = 0.3;
	GLfloat aniAngle[5];
	int maxAngle = 20.0f;
	int minAngle = -20.0f;
	bool maxAngleReached = false;

	float stepSize = 0.1f;

	//COLLISION
	bool hitObject = false;
	int stepCounter = 0;

};

