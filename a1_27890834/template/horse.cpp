#include "stdafx.h"
#include "Horse.h"


Horse::Horse()
{
	setTorso(horseScale, horseRotateAngle, horseRotation, horseTranslation);
}


Horse::~Horse()
{
}

void Horse::setTorso(glm::vec3 horseScale, float horseRotateAngle, glm::vec3 horseRotation, glm::vec3 horseTranslation) {
	glm::mat4 torso;
	scale = glm::scale(torso, horseScale);
	rotate = glm::rotate(torso, horseRotateAngle, horseRotation);
	translate = glm::translate(torso, horseTranslation);
	torso*= scale * rotate * translate;
	colValues[0] = 0.275f;
	colValues[1] = 0.510f;
	colValues[2] = 0.706f;

	torsoObj = { torso, *colValues };
	components.push_back(&torsoObj); //push torso to transformations
	
	setNeck(0.0f);
}

void Horse::setNeck(float angle) {
	glm::mat4 neck;
	scale = glm::scale(neck, glm::vec3(0.5f, 0.5f, 0.5f));
	rotate = glm::rotate(neck, glm::radians(-25.0f + angle), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(neck, glm::vec3(-3.2f, 0.5f, 0.0f));
	neck *= torsoObj.matrix * scale * rotate * translate;
	colValues[0] = 0.529f;
	colValues[1] = 0.808f;
	colValues[2] = 0.922f;
	
	neckObj = { neck, *colValues };
	components.push_back(&neckObj);

	setHead(0.0f);
}

void Horse::setHead(float angle)
{
	glm::mat4 head;
	scale = glm::scale(head, glm::vec3(0.5f, 0.8f, 0.8f));
	rotate = glm::rotate(head, glm::radians(160.0f + angle), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(head, glm::vec3(1.0f, 2.0f, 0.0f));
	head *= neckObj.matrix * scale * rotate * translate; //use neck
	colValues[0] = 0.690f;
	colValues[1] = 0.878f;
	colValues[2] = 0.902f;

	headObj = { head, *colValues };
	components.push_back(&headObj);
}

void Horse::setUpperArmL(float angle)
{
}

void Horse::setLowerArmL(float angle)
{
}

void Horse::setUpperArmR(float angle)
{
}

void Horse::setLowerArmR(float angle)
{
}

void Horse::setUpperLegL(float angle)
{
}

void Horse::setLowerLegL(float angle)
{
}

void Horse::setUpperLegR(float angle)
{
}

void Horse::setLowerLegR(float angle)
{
}

void Horse::setTail(float angle)
{
}

