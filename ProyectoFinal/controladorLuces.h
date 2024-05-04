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


	//Por si se requiere modificar algun valor de una luz en tiempo de ejecucion
	//void updateLights(); 

	//Inicializan y añaden a los arreglos necesarios las luces. Reciben como argumento los vectores de posicion de los objetos a los cuales se les va a ligar la luz.
	void initializeSpotlights(glm::vec3 posLuz1, glm::vec3 posLuz2, glm::vec3 posLuz3);
	void initializePointlights(glm::vec3 posLuz1, glm::vec3 posLuz2, glm::vec3 posLuz3);

	//escoge el arreglo y la cuenta de luces que se va a utilizar 
	void chooseSpotLightsArray(GLboolean esDia);
	void choosePointLightsArray( GLboolean luzActivableEncendida);
	GLboolean recalculateDirectionalLight(GLfloat deltaTime);
	void setSkyboxNumber();

	SpotLight* getSpotlightArray() { return spotlights; };
	unsigned int getSpotLightCount() { return currentSpolightCount; }

	PointLight* getPointlightArray() { return currentPointlight; }
	unsigned int getPointlightCount() { return currentPointlightCount; }
	int getSkyboxNumber() { return skyboxNumber; }


private:
	//Apuntador a MainLight para que modifique directamente la luz del archivo main.
	DirectionalLight* mainLight;
	//Angulo máximo de la luz direccional, 180 para que el recorrido sea un semicirculo
	float maxAngle = 180.0f; 
	//VAriable booleana indica si es de dia o de noche.
	GLboolean esDeDia;
	//El incremento del angulo. Esta en funcion de la duracion del dia el angulo máximo y la cantidad de fps
	float incrementoAngulo;
	//Angulo de la luz direccional, para poder calcular el vector de dirección de la luz.
	float angulo;
	//El numero indica el skybox que se va a renderizar: 1) amanecer 2) dia 3)aterdecer 4) noche
	int skyboxNumber;


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