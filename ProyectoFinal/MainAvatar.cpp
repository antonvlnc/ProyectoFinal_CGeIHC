#include "MainAvatar.h"

using vec3df = glm::dvec3;

MainAvatar::MainAvatar() {

}

//Constructor del avatar
// vec3 Posicion incial: traslación incial del personaje
// vec3 Rotacion inicial: rotacion inicial del personaje
MainAvatar::MainAvatar(glm::vec3 posInicial, GLfloat rotInicial, glm::vec3 scale, GLfloat velocidad) { 

	posAvatar = glm::mat4(1.0);
	posAvatar = glm::translate(posAvatar, posInicial);
	posAvatar = glm::rotate(posAvatar, glm::radians(rotInicial), glm::vec3(0.0f, 1.0f, 0.0f));
	posAvatar = glm::scale(posAvatar, scale);

	uniformModel = 0;


	movimiento = 0;
	velocidadMovimiento = velocidad;
	//velocidad movimiento
	rotacion = 0;

	

	rotacionExtremidades = 0;
	rotacionInicial = rotInicial;
	escala = scale;
	banderaAnimacionCaminata = true;
	loadmodels();
}

void MainAvatar::loadmodels() {

	body = Model();
	arm = Model();
	leg = Model();

	body.LoadModel("Models/Dexterslab/DexterBody.obj");
	arm.LoadModel("Models/Dexterslab/DexterArm.obj");
	leg.LoadModel("Models/DextersLab/DexterLeg.obj");


}
void MainAvatar::setUniformModel(GLint uniform) {
	uniformModel = uniform;
}

void MainAvatar::setMovimiento(GLfloat movimientoAvatar, GLfloat rotacionAvatar, GLboolean rotacionBrazos, GLfloat deltaTime) {
	movimiento = velocidadMovimiento * movimientoAvatar * deltaTime;
	rotacion = rotacionAvatar * deltaTime;
	if (rotacionBrazos) {
		if (banderaAnimacionCaminata) {
			if (rotacionExtremidades <= 30.0) {
				rotacionExtremidades += 3.0f * deltaTime;
			}
			else {
				banderaAnimacionCaminata = !banderaAnimacionCaminata;
			}
		}
		else {
			if (rotacionExtremidades >= -30.0) {
				rotacionExtremidades -= 3.0f * deltaTime;
			}
			else {
				banderaAnimacionCaminata = !banderaAnimacionCaminata;
			}
		}
		
	}
	else {
		rotacionExtremidades = 0.0;
	}
}

glm::vec3 MainAvatar::getPos() {
	glm::vec3 pos = (posAvatar[3]);
	return pos;
}

glm::vec3 MainAvatar::getDirection(){
	// La dirección es simplemente la primera columna de la matriz de rotación
	return glm::vec3(posAvatar[0][2], posAvatar[1][2], posAvatar[2][2]);
}

glm::vec3 MainAvatar::getUpVector(){
	// El vector hacia arriba es la segunda columna de la matriz de rotación
	return glm::vec3(posAvatar[0][1], posAvatar[1][1], posAvatar[2][1]);
}


void MainAvatar::renderMainAvatar() {
	
	glm::mat4 model = this->posAvatar;
	glm::mat4 modelaux(1.0);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, movimiento));
	model = glm::rotate(model, glm::radians(rotacion), glm::vec3(0.0f, 1.0f, 0.0f));
	this->posAvatar = model;
	modelaux = model;

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	body.RenderModel();


	model = glm::translate(model, glm::vec3(-0.34f, 0.05f, 0.0f)); // Pierna Derecha
	model = glm::rotate(model, glm::radians(rotacionExtremidades), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	leg.RenderModel();

	model = modelaux; //Pierna Izquierda
	model = glm::translate(model, glm::vec3(0.34f, 0.05f, 0.0f));
	model = glm::rotate(model, glm::radians((-1) * rotacionExtremidades), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	leg.RenderModel();


	model = modelaux; //Brazo Derecho
	model = glm::translate(model, glm::vec3(-0.8f, 0.39f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionExtremidades), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	arm.RenderModel();

	model = modelaux;  //Brazo Izquierdo
	model = glm::translate(model, glm::vec3(0.8f, 0.39f, 0.0f));
	model = glm::rotate(model, glm::radians((-1) * rotacionExtremidades), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	arm.RenderModel();

}

