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

	//Setters
	void setDirection(GLfloat xDireccion,  GLfloat yDirection, GLfloat zDirection);
	void setColor(GLfloat red, GLfloat green, GLfloat blue );
	void setAmbientIntensity(GLfloat ambient);
	void setDiffuseIntensity(GLfloat diffuse);
	~DirectionalLight();

private:
	glm::vec3 direction;
};

