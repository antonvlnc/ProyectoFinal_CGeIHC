#pragma once
#include "Model.h"

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <stdio.h>
#include <string.h>



class Lampara
{
public:
	Lampara();
	Lampara(std::string fileName, GLuint* uniform, glm::vec3 posInicial, glm::vec3 scale);
	void setUniform(GLuint* uniform);
	glm::vec3 getPos() { return posicion; }
	glm::vec3 getScale() { return escala; }
	//void changeModel(std::string fileName); // La luces de las Lamparas van a ser cocinadas, con esta funcion se cambia el modelo
	// 
	//setters
	void setPos(glm::vec3 pos);
	void setNonUniformScale(GLfloat xScale, GLfloat yScale, GLfloat zScale);
	void setUniformScale(GLfloat Scale);
	void setRotX(GLfloat rotX);
	void setRotY(GLfloat rotY);
	void setRotZ(GLfloat rotZ);

	//getters
	void renderModel();
	void renderModel(glm::vec3 pos);

	~Lampara();

private:
	GLuint* uniformModel;
	Model LamparaModel;
	glm::vec3 posicion, escala;
	GLfloat rotacionX, rotacionY, rotacionZ;
	void loadModels(std::string fileName);

};