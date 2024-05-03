#pragma once
#include "SpotLight.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "CommonValues.h"

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

class controladorLuces {
public:
	controladorLuces();
	controladorLuces(float duracionDia, float limitFPS, GLboolean esDia, DirectionalLight* luzDireccional);
	~controladorLuces();
	//solo llamarlas una vez!
	void setSpotlights(SpotLight luz1, SpotLight luz2, SpotLight luz3);


	//Por si se requiere algun valor de una luz en tiempo de ejecucion
	//void updateLights(); 

	//inicializa los arreglos según las luces que se hayan inicializado usando los setters

	void initializeSpotlights(glm::vec3 posLuz1, glm::vec3 posLuz2, glm::vec3 posLuz3);
	void initializePointlights(glm::vec3 posLuz1, glm::vec3 posLuz2, glm::vec3 posLuz3);

	//escoge el arreglo y la cuenta de luces que se va a utilizar 
	void chooseSpotLightsArray(GLboolean esDia);
	void choosePointLightsArray(GLboolean esDia, GLboolean luzActivableEncendida);
	GLboolean recalculateDirectionalLight(GLfloat deltaTime);
	void setSkyboxNumber();

	SpotLight* getSpotlightArray() { return spotlights; };
	unsigned int getSpotLightCount() { return currentSpolightCount; }

	PointLight* getPointlightArray() { return currentPointlight; }
	unsigned int getPointlightCount() { return currentPointlightCount; }
	int getSkyboxNumber() { return skyboxNumber; }

	//DirectionalLight getDirectionalLight() { return mainLight; }

private:
	//MainLight
	DirectionalLight* mainLight;
	float maxAngle = 180.0f;
	GLboolean esDeDia;
	float incrementoAngulo;
	float angulo;
	int skyboxNumber;//1 Dia, 2 Noche


	SpotLight spotlights[MAX_SPOT_LIGHTS]; // Un solo arreglo p/ luces prendidas, mandar count = 0 para apagadas
	unsigned int spotlightCount=0; //Cuenta de luces en el arreglo
	unsigned int currentSpolightCount; // Cuenta de luces que se manda al shader

	PointLight pointLights[2][3];
	PointLight* currentPointlight;
	unsigned int pointlightCount[2];
	unsigned int currentPointlightCount;

	//Metodos
	//Para garantizar que siempre se inicializa una directional light en caso de cualquier error.
	void initializeDirectionalLight();


};