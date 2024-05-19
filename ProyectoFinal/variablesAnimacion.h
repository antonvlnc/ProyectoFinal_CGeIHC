#pragma once
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

//fishy fishy
const float radioFuenteDiana = 9.5f;
float anguloFishy, anguloFishyOffset;

//Reja Entrada
const float maxDistanciaPuerta = 100.0f;
glm::vec3 puertaPos;
bool isOpenDoor, openDoor;
float anguloPuerta, anguloPuertaOffset;
float distanciaPuerta;




void initializeFishyVariables() {

	anguloFishy = 0.0f;
	anguloFishyOffset = 0.5f;
}

void initializeRejaVariables() {
	puertaPos = glm::vec3(-3.0f, -0.95f, -780.0f);
	isOpenDoor = false;
	openDoor = false;

	if (isOpenDoor) {
		anguloPuerta = 90.0f;
	}
	else {
		anguloPuerta = 0.0f;
	}

	anguloPuertaOffset = 1.0f; 
}

void initializeAnimationVars() {
	initializeFishyVariables();
	initializeRejaVariables();
}