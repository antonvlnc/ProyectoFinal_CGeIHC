#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
									GLfloat aIntensity, GLfloat dIntensity,
									GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(red, green, blue, aIntensity, dIntensity)
{
	direction = glm::vec3(xDir, yDir, zDir);
}

void DirectionalLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientcolorLocation,
	GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
	glUniform3f(ambientcolorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

void DirectionalLight::setDirection(GLfloat xDireccion, GLfloat yDirection, GLfloat zDirection) {
	direction.x = xDireccion;
	direction.y = yDirection;
	direction.z = zDirection;
}

void DirectionalLight::setColor(GLfloat red, GLfloat green, GLfloat blue) {
	color.x = red;
	color.y = green;
	color.z = blue;
}

void DirectionalLight::setAmbientIntensity(GLfloat ambient) {
	ambientIntensity = ambient;

}

void DirectionalLight::setDiffuseIntensity(GLfloat diffuse) {
	diffuseIntensity = diffuse;
}

DirectionalLight::~DirectionalLight()
{
}
