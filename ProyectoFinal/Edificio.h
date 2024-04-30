#pragma once
#include "Model.h"

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <stdio.h>

class Edificio {
public:
	Edificio();
	Edificio(std::string fileName, GLuint* uniform); //apuntador a uniform para no tener que modificar los valores manualmente
	Edificio(std::string fileName, GLuint* uniform, glm::vec3 posInicial, glm::vec3 escalaInicial);

	void renderModel();
	//setters
	void setPos(float xPos, float yPos, float zPos);
	void setRotX(float rotX);
	void setRotY(float rotY);
	void setRotZ(float rotZ);
	void setNonUniformScale(float xScale, float yScale, float zScale);
	void setUniformScale(float scale);

	//getters
	glm::vec3 getPos();
	glm::vec3 getScale();
private:
	Model edificioModel;
	glm::vec3 posicion, escala;
	GLfloat rotacionX, rotacionY, rotacionZ;
	GLuint* uniformModel; //apuntado
	void loadModels(std::string fileName);
	
};