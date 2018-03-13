#include "stdafx.h"
#include "Horse.h"

Horse::Horse()
{
	setTorso(horseScale, horseRotateAngle, horseRotation, horseTranslation);
	setHorseRender();
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
	
	setNeck(0.0f);
	setUpperArmL(0.0f);
	setUpperArmR(0.0f);
	setUpperLegL(0.0f);
	setUpperLegR(0.0f);
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
}

void Horse::setUpperArmL(float angle)
{
	glm::mat4 upperArmL;
	scale = glm::scale(upperArmL, glm::vec3(0.15f, 0.9f, 0.15f));
	rotate = glm::rotate(upperArmL, glm::radians(0.0f + angle), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(upperArmL, glm::vec3(-5.4f, -1.5f, 3.0f));
	upperArmL *= torsoObj.matrix * scale * rotate * translate; 
	colValues[0] = 0.690f;
	colValues[1] = 0.769f;
	colValues[2] = 0.871f;

	upperArmLObj = { upperArmL, *colValues };
	setLowerArmL(0.0f);
}

void Horse::setLowerArmL(float angle)
{
	glm::mat4 lowerArmL;
	scale = glm::scale(lowerArmL, glm::vec3(1.2f, 1.0f, 1.2f));
	rotate = glm::rotate(lowerArmL, glm::radians(0.0f + angle), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(lowerArmL, glm::vec3(0.0f, -2.0f, 0.0f));
	lowerArmL *= upperArmLObj.matrix * scale * rotate * translate;
	colValues[0] = 0.392f;
	colValues[1] = 0.584f;
	colValues[2] = 0.929f;

	lowerArmLObj = { lowerArmL, *colValues };
}

void Horse::setUpperArmR(float angle)
{
	glm::mat4 upperArmR;
	scale = glm::scale(upperArmR, glm::vec3(0.15f, 0.9f, 0.15f));
	rotate = glm::rotate(upperArmR, glm::radians(0.0f + angle), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(upperArmR, glm::vec3(-5.4f, -1.5f, -3.0f));
	upperArmR *= torsoObj.matrix * scale * rotate * translate; //use torso
	colValues[0] = 0.690f;
	colValues[1] = 0.769f;
	colValues[2] = 0.871f;

	upperArmRObj = { upperArmR, *colValues };
	setLowerArmR(0.0f);
}

void Horse::setLowerArmR(float angle)
{
	glm::mat4 lowerArmR;
	scale = glm::scale(lowerArmR, glm::vec3(1.2f, 1.0f, 1.2f));
	rotate = glm::rotate(lowerArmR, glm::radians(0.0f + angle), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(lowerArmR, glm::vec3(0.0f, -2.0f, 0.0f));
	lowerArmR *= upperArmRObj.matrix * scale * rotate * translate; 
	colValues[0] = 0.392f;
	colValues[1] = 0.584f;
	colValues[2] = 0.929f;

	lowerArmRObj = { lowerArmR, *colValues };
}

void Horse::setUpperLegL(float angle)
{
	glm::mat4 upperLegL;
	scale = glm::scale(upperLegL, glm::vec3(0.15f, 0.9f, 0.15f));
	rotate = glm::rotate(upperLegL, glm::radians(0.0f + angle), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(upperLegL, glm::vec3(5.4f, -1.5f, 3.0f));
	upperLegL *= torsoObj.matrix * scale * rotate * translate; 
	colValues[0] = 0.690f;
	colValues[1] = 0.769f;
	colValues[2] = 0.871f;

	upperLegLObj = { upperLegL, *colValues };
	setLowerLegL(0.0f);
}

void Horse::setLowerLegL(float angle)
{
	glm::mat4 lowerLegL;
	scale = glm::scale(lowerLegL, glm::vec3(1.2f, 1.0f, 1.2f));
	rotate = glm::rotate(lowerLegL, glm::radians(0.0f + angle), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(lowerLegL, glm::vec3(0.0f, -2.0f, 0.0f));
	lowerLegL *= upperLegLObj.matrix * scale * rotate * translate; //use UpperLegL
	colValues[0] = 0.392f;
	colValues[1] = 0.584f;
	colValues[2] = 0.929f;

	lowerLegLObj = { lowerLegL, *colValues };
}

void Horse::setUpperLegR(float angle)
{
	glm::mat4 upperLegR;
	scale = glm::scale(upperLegR, glm::vec3(0.15f, 0.9f, 0.15f));
	rotate = glm::rotate(upperLegR, glm::radians(0.0f + angle), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(upperLegR, glm::vec3(5.4f, -1.5f, -3.0f));
	upperLegR *= torsoObj.matrix * scale * rotate * translate;
	colValues[0] = 0.690f;
	colValues[1] = 0.769f;
	colValues[2] = 0.871f;

	upperLegRObj = { upperLegR, *colValues };
	setLowerLegR(0.0f);
}

void Horse::setLowerLegR(float angle)
{
	glm::mat4 lowerLegR;
	scale = glm::scale(lowerLegR, glm::vec3(1.2f, 1.0f, 1.2f));
	rotate = glm::rotate(lowerLegR, glm::radians(0.0f + angle), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(lowerLegR, glm::vec3(0.0f, -2.0f, 0.0f));
	lowerLegR *= upperLegRObj.matrix * scale * rotate * translate; //use UpperLegR
	colValues[0] = 0.392f;
	colValues[1] = 0.584f;
	colValues[2] = 0.929f;

	lowerLegRObj = { lowerLegR, *colValues };
}

void Horse::setHorseRender() {
	components.push_back(&lowerLegRObj);
	components.push_back(&upperLegRObj);
	components.push_back(&lowerLegLObj);
	components.push_back(&upperLegLObj);
	components.push_back(&lowerArmRObj);
	components.push_back(&upperArmRObj);
	components.push_back(&lowerArmLObj);
	components.push_back(&upperArmLObj);
	components.push_back(&headObj);
	components.push_back(&neckObj);
	components.push_back(&torsoObj); //push torso to transformations
}