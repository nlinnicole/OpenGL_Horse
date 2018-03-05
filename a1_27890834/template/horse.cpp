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
	setUpperArmL(0.0f);
	setUpperArmR(0.0f);
	setUpperLegL(0.0f);
	setUpperLegR(0.0f);
	setTail(0.0f);
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
	glm::mat4 upperArmL;
	scale = glm::scale(upperArmL, glm::vec3(0.15f, 0.9f, 0.15f));
	rotate = glm::rotate(upperArmL, glm::radians(0.0f + angle), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(upperArmL, glm::vec3(-5.4f, -1.5f, 3.0f));
	upperArmL *= torsoObj.matrix * scale * rotate * translate; 
	colValues[0] = 0.690f;
	colValues[1] = 0.769f;
	colValues[2] = 0.871f;

	upperArmLObj = { upperArmL, *colValues };
	components.push_back(&upperArmLObj); 

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
	components.push_back(&lowerArmLObj);
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
	components.push_back(&upperArmRObj); // push upperArmR to transformations

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
	components.push_back(&lowerArmRObj);
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
	components.push_back(&upperLegLObj); 

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
	components.push_back(&lowerLegLObj);
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
	components.push_back(&upperLegRObj); 

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
	components.push_back(&lowerLegRObj);
}

void Horse::setTail(float angle)
{
	glm::mat4 tail;
	scale = glm::scale(tail, glm::vec3(0.5f, 0.3f, 0.3f));
	rotate = glm::rotate(tail, glm::radians(10.0f + angle), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(tail, glm::vec3(3.0f, 1.5f, 0.0f));
	tail *= torsoObj.matrix * scale * rotate * translate; //use torso
	colValues[0] = 0.118f;
	colValues[1] = 0.565f;
	colValues[2] = 1.000f;

	tailObj = { tail, *colValues };
	components.push_back(&tailObj);
}

