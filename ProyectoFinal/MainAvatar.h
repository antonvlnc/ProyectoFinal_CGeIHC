#pragma once

#include "Model.h"

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

class MainAvatar
{
public:
	MainAvatar();
	MainAvatar(glm::vec3 posInicial, GLfloat rotInicial, glm::vec3 scale, GLfloat velocidad);	
	glm::vec3 getPos();

	glm::vec3 getDirection();

	glm::vec3 getUpVector();


	void setUniformModel(GLint uniform);
	void setMovimiento(GLfloat movimientoAvatar, GLfloat rotacionAvatar, GLboolean rotacionBrazos, GLfloat deltaTime);

	float getRotY() { return rotacionInicial; }
	void renderMainAvatar();

private:
	Model body, arm, leg;
	glm::mat4 posAvatar;
	GLint uniformModel;
	glm::vec3  escala;
	GLfloat movimiento, rotacionInicial, rotacion, rotacionExtremidades; //Para recibir valores de los datos que se modifican por teclado
	GLfloat velocidadMovimiento;
	GLboolean banderaAnimacionCaminata;
	void loadmodels();
	
	

};