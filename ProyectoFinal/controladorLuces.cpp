#include "controladorLuces.h"

//Solo para que no este vacio el constructor
controladorLuces::controladorLuces() {
	spotlightCount = 0;
	currentSpolightCount = 0;
	for (int i = 0; i < (sizeof(pointlightCount) / sizeof(unsigned int)); i++) {
		pointlightCount[i] = 0;
	}
	currentPointlightCount = 1;
	incrementoAngulo = 0;
	angulo = 0;
}
controladorLuces::controladorLuces(float duracionDia, float fps, GLboolean esDia, DirectionalLight* luzDireccional) {
	maxAngle = 180.0f;
	esDeDia = esDia;
	incrementoAngulo = (maxAngle / duracionDia) * fps;
	angulo = 0;

	spotlightCount = 0;
	currentSpolightCount = 0;
	for (int i = 0; i < (sizeof(pointlightCount) / sizeof(unsigned int)); i++) {
		pointlightCount[i] = 0;
	}
	currentPointlightCount = 0;
	
	mainLight = luzDireccional;
	if (esDia) {
		skyboxNumber = 1;
	}
	else {
		skyboxNumber = 2;
	}

	initializeDirectionalLight();
}

controladorLuces::~controladorLuces() {

}

void controladorLuces::initializeDirectionalLight() {
	*mainLight =  DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
}

GLboolean controladorLuces::recalculateDirectionalLight(GLfloat deltaTime) {
	GLfloat intensity = 0.4f, dintensity = 0.5f;
	GLfloat xDir, yDir, red, green, blue;



	if (angulo >= 180.0) {
		angulo = 0.0f;
		esDeDia = !esDeDia;
	}
	else {
		angulo += incrementoAngulo * deltaTime;
	}

	xDir = cos(glm::radians(angulo));
	yDir = (-1.0) * sin(glm::radians(angulo));

	if (esDeDia) {
		red = 0.8f + 0.2 * sin(glm::radians(angulo));
		green = 0.6f + 0.4 * sin(glm::radians(angulo));
		blue = 0.6f + 0.4 * sin(glm::radians(angulo));
		intensity = 0.6f;
		dintensity = 0.5f;
		skyboxNumber = 1;
	}
	else {
		red = 0.6f - 0.1 * sin(glm::radians(angulo));
		green = 0.6f - 0.1 * sin(glm::radians(angulo));
		blue = 0.6f + (0.4 * sin(glm::radians(angulo)));
		intensity = 0.2f;
		dintensity = 0.2f;
		skyboxNumber = 2;
	}


	//Agregar setters a directional light para no crear nuevos objetos con cada llamada.
	*mainLight = DirectionalLight(red, green, blue,
		intensity, dintensity,
		xDir, yDir, 0.0f);
	return esDeDia;
}

void controladorLuces::setSkyboxNumber() {
	if (esDeDia) {
		if ((angulo >= 0.0 && angulo <= 30.0) ) {
			skyboxNumber = 1; //Amanecer
		}
		else if (angulo >= 150.0 && angulo <= 180.0){
			skyboxNumber = 3; //atardecer
		}
		else {
			skyboxNumber = 2; //dia
		}
	}
	else {
		if ((angulo >= 0.0 && angulo <= 30.0)) {
			skyboxNumber = 1; //Atardecer con tonalidades mas oscuras falta implementar
		}
		else if (angulo >= 160.0 && angulo <= 150.0) {
			skyboxNumber = 3; //amanecer con tonalidades mas oscuras
		}
		else {
			skyboxNumber = 4; //noche
		}
	}
}


void controladorLuces::initializeSpotlights(glm::vec3 posLuz1, glm::vec3 posLuz2, glm::vec3 posLuz3) {
	 

	//SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue,
	//	GLfloat aIntensity, GLfloat dIntensity,
	//	GLfloat xPos, GLfloat yPos, GLfloat zPos,
	//	GLfloat xDir, GLfloat yDir, GLfloat zDir,
	//	GLfloat con, GLfloat lin, GLfloat exp,
	//	GLfloat edg) : PointLight(red, green, blue, aIntensity, dIntensity, xPos, yPos, zPos, con, lin, exp)

	// agregar algo que tome en cuenta la escala y el desplazamiento de la luz con respecto al centro del modelo.
	SpotLight letrasDimmsdale = SpotLight(0.5f, 0.0f, 0.8f, //Diana rojo
		1.0f, 1.0f,
		posLuz1.x, posLuz1.y + (1.0 * 5.0), posLuz1.z - 35.0,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.01f, 0.0f ,
		80.0f);

	SpotLight letrerosDimmsdale = SpotLight(0.0f, 0.0f, 0.7f, //Angel 0.7f ,0.0f ,0.7f
		1.0f, 1.0f,
		posLuz2.x, posLuz2.y  , posLuz2.z,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.01f, 0.0f ,
		80.0f);

	SpotLight x = SpotLight(0.7f, 0.7f, 0.0f, // Ring 0.7f, 0.7f, 0.0f
		1.0f, 1.0f,
		posLuz3.x, posLuz3.y + 50.0f, posLuz3.z,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.01f, 0.0f,
		80.0f);

	spotlights[0] = letrasDimmsdale;
	spotlights[1] = letrerosDimmsdale;
	spotlights[2] = x;
	spotlightCount = 3;

}


void controladorLuces::chooseSpotLightsArray(GLboolean esDia) {

	if (esDia) {
		currentSpolightCount = 0;
	}
	else {
		currentSpolightCount = spotlightCount;
	}

}

void controladorLuces::initializePointlights(glm::vec3 posLuz1, glm::vec3 posLuz2, glm::vec3 posLuz3) {

	/*PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
						GLfloat aIntensity, GLfloat dIntensity,
						GLfloat xPos, GLfloat yPos, GLfloat zPos,
						GLfloat con, GLfloat lin, GLfloat exp) : Light(red, green, blue, aIntensity, dIntensity)*/
	PointLight angel = PointLight(0.8f, 0.8f, 0.0f, //0.0f, 0.2f, 1.0f
		1.0f, 1.0f,
		posLuz1.x, posLuz1.y + 30.0f, posLuz1.z + 20.0f, //Letras Dimmsdale
		1.0f, 0.01f, 0.01f);

	PointLight diana = PointLight(0.8f, 0.8f, 0.0f, //0.5f, 0.0f, 0.5f
		1.0f, 1.0f,
		posLuz2.x, posLuz2.y + (70.0 * 1.9f), posLuz2.z, //Letrero Dimmsdale
		1.0f, 0.01f, 0.01f);

	PointLight bigWand = PointLight(1.0f, 1.0f, 0.0f,
		1.0f, 1.0f,
		posLuz3.x, posLuz3.y + (12.0 * 20.0), posLuz3.z, //Numero entre paréntesis es la altura a la que esta la fuente de iluminacion en el modelo original por la escala en y del model
		1.0f, 0.01f, 0.0f);
	//Para que no se envie un arreglo vacio
	PointLight defaultPointlight = PointLight(0.0f, 0.0f, 0.0f,
		1.0f, 1.0f,
		posLuz1.x, posLuz1.y, posLuz1.z,
		1.0f, 0.01f, 0.0f);;

	//Para la noche
	pointLights[0][0] = angel;
	pointLights[0][1] = diana;
	pointLights[0][2] = bigWand;
	pointlightCount[0] = 3;

	pointLights[1][0] = defaultPointlight;
	pointlightCount[1]++;
}

void controladorLuces::choosePointLightsArray(GLboolean esDia, GLboolean luzActivableEncendida) {

	if (esDia) {
		currentPointlight = pointLights[1];
		currentPointlightCount = pointlightCount[1];
	}
	else {
		currentPointlight = pointLights[0];
		if (luzActivableEncendida) {
			currentPointlightCount = pointlightCount[0];
		}
		else {
			currentPointlightCount = pointlightCount[0] - 1;
		}
	}

}