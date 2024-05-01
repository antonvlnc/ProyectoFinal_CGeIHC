#include "Edificio.h"

//Para edificios que no tengan ningun tipo de jerarquia. Se puede agregar un segundo modelos con luces cocinadas y agregar la lógica de programacion aquí mismo
//Interfaces P/ las clases
Edificio::Edificio() {

}

Edificio::Edificio(std::string fileName, GLuint* uniform) {
	posicion = glm::vec3(0.0f, 0.0f, 0.0f);
	escala = glm::vec3(0.0f, 0.0f, 0.0f);
	rotacionX = 0.0f;
	rotacionY = 0.0f;
	rotacionZ = 0.0f;
	uniformModel = uniform;
	loadModels(fileName);

}

Edificio::Edificio(std::string fileName, GLuint* uniform, glm::vec3 posInicial, glm::vec3 escalaInicial) {
	posicion = posInicial;
	escala = escalaInicial;
	rotacionX = 0.0f;
	rotacionY = 0.0f;
	rotacionZ = 0.0f;
	uniformModel = uniform;
	loadModels(fileName);
}

//Agregar posible constructor que incluya posiciones, escalas y rotaciones directamente;

void Edificio::loadModels(std::string fileName) {
	edificioModel = Model();
	edificioModel.LoadModel(fileName);

}

//Setters
void Edificio::setPos(float xPos, float yPos, float zPos) {
	posicion = glm::vec3(xPos, yPos, zPos);
}
void Edificio::setRotX(float rotX) {
	rotacionX = rotX;
}

void Edificio::setRotY(float rotY) {
	rotacionY = rotY;
}

void Edificio::setRotZ(float rotZ) {
	rotacionZ = rotZ;
}

void Edificio::setNonUniformScale(float xScale, float yScale, float zScale) {
	escala = glm::vec3(xScale, yScale, zScale);
}

void Edificio::setUniformScale(float scale) {
	escala = glm::vec3(scale, scale, scale);
}

//Getters
glm::vec3 Edificio::getPos() {
	return posicion;
}

glm::vec3 Edificio::getScale() {
	return escala;
}

//Metodos de clase

void Edificio::renderModel() {
	glm::mat4 model;


	model = glm::mat4(1.0);
	model = glm::translate(model, posicion);
	model = glm::rotate(model, glm::radians(rotacionX), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionZ), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, escala);
	glUniformMatrix4fv(*uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	edificioModel.RenderModel();

}

