#include "controladorLuces.h"

controladorLuces::controladorLuces() {

	for (int i = 0; i < (sizeof(spotlightCount) / sizeof(unsigned int)); i++) {
		spotlightCount[i] = 0;
	}
	for (int i = 0; i < (sizeof(pointlightCount) / sizeof(unsigned int)); i++) {
		pointlightCount[i] = 0;
	}
	
}

void controladorLuces::setSpotlightLetrasDimmsdale(glm::vec3 color, glm::vec3 position, glm::vec3 direction, GLfloat intensity, GLfloat linear, GLfloat exponential, GLfloat edge) {

}
void controladorLuces::setSpotlightLetreroDimmsdale(glm::vec3 color, glm::vec3 position, glm::vec3 direction, GLfloat intensity, GLfloat linear, GLfloat exponential, GLfloat edge) {

}