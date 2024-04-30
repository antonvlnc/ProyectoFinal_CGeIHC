#include "Lampara.h"

Lampara::Lampara() {
	posicion = glm::vec3(0.0f, 0.0f, 0.0f);
	escala = glm::vec3(1.0f, 1.0f, 1.0f);
	rotacionX = 0.0f;
	rotacionY = 0.0f;
	rotacionZ = 0.0f;
	uniformModel = NULL;
}

Lampara::Lampara(std::string fileName, GLuint* uniform,  glm::vec3 posInicial, glm::vec3 scale) {
	posicion = posInicial;
	escala = scale;
	rotacionX = 0.0f;
	rotacionY = 0.0f;
	rotacionZ = 0.0f;
	uniformModel = uniform;
	loadModels(fileName);
}

Lampara::~Lampara() {

}

//Setters
void Lampara::setPos(glm::vec3 pos) {
	posicion = pos;
}

void Lampara::setRotX(GLfloat rotX) {
	rotacionX = rotX;
}

void Lampara::setRotY(GLfloat rotY) {
	rotacionY = rotY;
}

void Lampara::setRotZ(GLfloat rotZ) {
	rotacionZ = rotZ;
}

void Lampara::setUniform(GLuint *uniform) {
	uniformModel = uniform;
}
void Lampara::setNonUniformScale(GLfloat xScale, GLfloat yScale, GLfloat zScale) {
	escala = glm::vec3(xScale, yScale, zScale);
}

void Lampara::loadModels(std::string fileName) {
	LamparaModel = Model();
	LamparaModel.LoadModel(fileName);
}

//Para cuando se agreguen luces cocinadas
//void Lampara::changeModel(std::string fileName) {
//	
//
//}

void Lampara::renderModel() {

	glm::mat4 model(1.0);

	model = glm::mat4(1.0);
	model = glm::translate(model, posicion);
	model = glm::scale(model, escala);
	model = glm::rotate(model, glm::radians(rotacionX), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionZ), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(*uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	LamparaModel.RenderModel();
}

//En caso de que se quiera utilizar una posición diferente
void Lampara::renderModel(glm::vec3 pos) {

	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, pos);
	model = glm::scale(model, escala);
	model = glm::rotate(model, glm::radians(rotacionX), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionZ), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(*uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	LamparaModel.RenderModel();
}