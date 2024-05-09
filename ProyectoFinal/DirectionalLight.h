#pragma once
#include "Light.h"

class DirectionalLight :
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
					GLfloat aIntensity, GLfloat dIntensity,
					GLfloat xDir, GLfloat yDir, GLfloat zDir);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientcolorLocation,
		GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	~DirectionalLight();

	void setDirection(GLfloat xdirection, GLfloat ydirection, GLfloat zDirection);
	void setIntensity(GLfloat ambient, GLfloat diffuse);
	void setColor(GLfloat red,GLfloat green, GLfloat blue);

private:
	glm::vec3 direction;
};

