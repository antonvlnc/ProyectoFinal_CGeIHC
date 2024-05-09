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
	angulo = 0.0f;

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

	banderaAnimacionSpotlight = true;
	anguloSpot = 90.0f;
	velocidadSpot = 0.2;
	xDirSpot = cos(glm::radians(anguloSpot));
	yDirSpot = sin(glm::radians(anguloSpot));
	blue = 0.5;
	red = 0.8f;

	now = 0;
	lastTime = clock();
	tiempoTranscurrido = 0.0;
	trafficRed = 0.0f;
	green = 0.0f;
	trafficBlue = 0.0f;
	xPosOffset = 0.4f * 17.0f;
	trafficLightState = 0;
	trafficLightStartingPos = glm::vec3(0.0f);

	initializeDirectionalLight();
}

controladorLuces::~controladorLuces() {

}

void controladorLuces::initializeDirectionalLight() {
	*mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
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
	}
	else {
		red = 0.6f - 0.1 * sin(glm::radians(angulo));
		green = 0.6f - 0.1 * sin(glm::radians(angulo));
		blue = 0.6f + (0.4 * sin(glm::radians(angulo)));
		intensity = 0.2f;
		dintensity = 0.2f;
	}

	(*mainLight).setColor(red, green, blue);
	(*mainLight).setDirection(xDir, yDir, 0.0f);
	(*mainLight).setIntensity(intensity, dintensity);

	return esDeDia;
}

void controladorLuces::setSkyboxNumber() {
	if (esDeDia) {
		if ((angulo >= 0.0 && angulo <= 30.0)) {
			skyboxNumber = 1; //Amanecer
		}
		else if (angulo >= 150.0 && angulo <= 180.0) {
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


	// agregar algo que tome en cuenta la escala y el desplazamiento de la luz con respecto al centro del modelo.
	//NOTA: Numero entre par�ntesis es la altura a la que esta la fuente de iluminacion en el modelo original por la escala en y del modelo
	SpotLight diana = SpotLight(1.0f, 0.0f, 1.0f, //Diana rojo
		1.0f, 1.0f,
		posLuz1.x, posLuz1.y + (1.0 * 5.0), posLuz1.z - 20.0,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.01f, 0.0f,
		50.0f);

	SpotLight angel = SpotLight(0.7f, 0.7f, 0.0f, //Angel 0.7f ,0.0f ,0.7f
		1.0f, 1.0f,
		posLuz2.x, posLuz2.y, posLuz2.z,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.005f, 0.0f,
		70.0f);

	SpotLight ring = SpotLight(0.7f, 0.7f, 0.0f, // Ring 0.7f, 0.7f, 0.0f
		1.0f, 1.0f,
		posLuz3.x, posLuz3.y + 50.0f, posLuz3.z,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.01f, 0.0f,
		80.0f);

	spotlights[0] = diana;
	spotlights[1] = angel;
	spotlights[2] = ring;
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


void controladorLuces::animateSpotlight(GLfloat deltaTime) {

	if (!esDeDia) {
		
		if (banderaAnimacionSpotlight) {
			if (anguloSpot <= 100.0f) {
				anguloSpot += velocidadSpot * deltaTime;
				
			}
			else {
				banderaAnimacionSpotlight = !banderaAnimacionSpotlight;
			}
		}
		else {
			if (anguloSpot >= 80.0f) {
				anguloSpot -= velocidadSpot * deltaTime;
			}
			else {
				banderaAnimacionSpotlight = !banderaAnimacionSpotlight;
			}
		}


		if (banderaColor) {
			if (blue <= 1.0) {
				blue += 0.01f * deltaTime;
			}
			else {
				banderaColor = !banderaColor;
			}
			
		}
		else {
			if (blue >= 0.1) {
				blue -= 0.01f * deltaTime;
			}
			else {
				banderaColor = !banderaColor;
			}

		}

		xDirSpot = cos(glm::radians(anguloSpot));
		yDirSpot = sin(glm::radians(anguloSpot));
		spotlights[0].setDirection(xDirSpot, yDirSpot, 0.0f);
		spotlights[0].setColor(red, 0.2f, blue);
	}
	else {
		anguloSpot = 90.0f;
	}

}


void controladorLuces::initializePointlights(glm::vec3 posLuz1, glm::vec3 posLuz2, glm::vec3 posLuz3) {

	//NOTA: Numero entre par�ntesis es la altura a la que esta la fuente de iluminacion en el modelo original por la escala en y del modelo

	trafficLightStartingPos = posLuz1;

	PointLight semaforo = PointLight(1.0f, 0.0f, 0.0f, //0.0f, 0.2f, 1.0f
		1.0f, 1.0f,
		posLuz1.x , posLuz1.y , posLuz1.z,
		0.8f, 0.1f, 0.01f);

	PointLight estelaLuz = PointLight(0.8f, 0.8f, 0.8f,
		0.8f, 1.0f,
		posLuz2.x, posLuz2.y + (45.0 * 5.0f), posLuz2.z,
		1.0f, 0.01f, 0.0001f);

	PointLight bigWand = PointLight(1.0f, 1.0f, 0.0f,
		1.0f, 1.0f,
		posLuz3.x, posLuz3.y + (12.0 * 20.0), posLuz3.z,
		1.0f, 0.05f, 0.0f);


	//Para la noche
	pointLights[0][0] = semaforo;
	pointLights[0][1] = estelaLuz;
	pointLights[0][2] = bigWand;
	pointlightCount[0] = 3;

	//Luz puntual apagada (negra) para que nunca se mande un arreglo "vacio"
	pointLights[1][0] = semaforo;
	pointlightCount[1]++;
	//Segunda luz big wand para que se puede activar por teclado durante el dia tambien
	pointLights[1][1] = bigWand;
	pointlightCount[1]++;
}

void controladorLuces::animateTrafficLight() {

	float xOffset = 0.0f;
	glm::vec3 newPosition(0.0);
	now = clock();
	tiempoTranscurrido = (float)(now - lastTime) / CLOCKS_PER_SEC;
	if (tiempoTranscurrido >= 4.0f) {
		lastTime = now;
		trafficLightState = (trafficLightState + 1) % 3;
	}

	switch (trafficLightState)
	{
	case 0:
		trafficRed = 1.0f;
		green = 0.0f;
		trafficBlue = 0.0f;
		break;
	case 1:
		trafficRed = 1.0f;
		green = 0.55f;
		trafficBlue = 0.0f;
		break;
	case 2:
		trafficRed = 0.0f;
		green = 1.0f;
		trafficBlue = 0.0f;
		break;
	default:
		trafficRed = 1.0f;
		green = 0.0f;
		trafficBlue = 0.0f;
		break;
	}

	xOffset = ((float)trafficLightState) * xPosOffset;

	newPosition = trafficLightStartingPos + glm::vec3(xOffset, 0.0f, 0.0f);

	pointLights[0][0].setPosition(newPosition);
	pointLights[0][0].setColor(trafficRed, green, trafficBlue);

	pointLights[1][0].setPosition(newPosition);
	pointLights[1][0].setColor(trafficRed, green, trafficBlue);
}

void controladorLuces::choosePointLightsArray(GLboolean luzActivableEncendida) {

	//ACtiva la luces de forma automatica cuando la bandera de esDia 
	if (esDeDia) {
		currentPointlight = pointLights[1];

		if (luzActivableEncendida) {
			currentPointlightCount = pointlightCount[1];
		}
		else {
			currentPointlightCount = pointlightCount[1] - 1;
		}
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

