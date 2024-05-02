#pragma once
#include "SpotLight.h"

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

class controladorLuces {
public:
	controladorLuces();

	//solo llamarlas una vez!
	void setSpotlightLetrasDimmsdale(glm::vec3 color, glm::vec3 position, glm::vec3 direction, GLfloat intensity, GLfloat linear, GLfloat exponential, GLfloat edge); 
	void setSpotlightLetreroDimmsdale(glm::vec3 color, glm::vec3 position, glm::vec3 direction, GLfloat intensity, GLfloat linear, GLfloat exponential, GLfloat edge);

	//Por si se requiere algun valor de una luz en tiempo de ejecucion
	void updateLights(); 

	//inicializa los arreglos según las luces que se hayan inicializado usando los setters
	void initializeSpotlights();

	//escoge el arreglo y la cuenta de luces que se va a utilizar 
	void chooseSpotLightsArray(GLboolean esDia);


private:
	SpotLight spotlights[2][3]; // spotlights[0]: para luces de dia, arreglo con spotlight apagado,spotlights[1]: para la noche, spotlights prendidas;
	SpotLight* currentSpotLight;
	unsigned int spotlightCount[2];
	unsigned int currentSpolightCount;

	PointLight pointLights[2][3];
	PointLight* currentPointlight;
	unsigned int pointlightCount[2];
	unsigned int currentPointlightCount;


};