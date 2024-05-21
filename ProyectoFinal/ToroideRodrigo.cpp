#include "ToroideRodrigo.h"

ToroideRodrigo::ToroideRodrigo() {
	radioExterno = 1.0f;
	radioInterno = 0.5f;

	numCirculos = 30;
	resCirculos = 20;

	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

void  ToroideRodrigo::createToroide() {

	int rInt, rOut; //contadores para los ciclos

	int circActual, circSiguiente;

	float x, y, z;

	/*x = 0.0f;
	y = 0.0f;
	z = 0.0f;*/

	float deltaAnguloAlfa, deltaAnguloBeta; // incremento en los ángulos de los circulos que se utilizan para trazar el toroide, anguloAlfa es el ángulo para el circulo "interno", beta para el círculo externo.

	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	deltaAnguloAlfa = (glm::radians(360.0f) / (float)resCirculos);
	deltaAnguloBeta = (glm::radians(360.0f) / (float)numCirculos);

	//Necesito introducir los vértices de dos círculos aledaños de forma alternada para que esto funcione
	// esto es

	for (rOut = 0; rOut <= numCirculos; rOut++) {

		circActual = rOut;
		circSiguiente = circActual + 1;

		/*if (circSiguiente == numCirculos) {
			circSiguiente = 0;
		}*/

		for (rInt = 0; rInt <= resCirculos; rInt++) {

			x = (radioExterno + radioInterno * (cos(rInt * deltaAnguloAlfa))) * cos(circActual * deltaAnguloBeta);
			y = radioInterno * sin(rInt * deltaAnguloAlfa);
			z = (radioExterno + radioInterno * (cos(rInt * deltaAnguloAlfa))) * sin(circActual * deltaAnguloBeta);

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			x = (radioExterno + radioInterno * (cos(rInt * deltaAnguloAlfa))) * cos(circSiguiente * deltaAnguloBeta);
			z = (radioExterno + radioInterno * (cos(rInt * deltaAnguloAlfa))) * sin(circSiguiente * deltaAnguloBeta);

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);


		}

		/*x = (radioExterno + radioInterno * (cos(0))) * cos(circActual * deltaAnguloBeta);
		y = radioInterno * sin(0);
		z = (radioExterno + radioInterno * (cos(0))) * sin(circActual * deltaAnguloBeta);

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);*/
	}

	for (int i = 0; i < vertices.size(); i++) {
		indices.push_back(i);
	}
	/*printf("V size %i \n", vertices.size());
	printf("I size %i \n", indices.size());

	for (int i = 0; i < vertices.size(); i+=3) {
		printf("%f \t %f\t %f\t \n", vertices[i], vertices[i + 1], vertices[i + 2]);
		
	}

	printf("\n\n\n");

	for (int i = 0; i < indices.size(); i+= 3) {
		printf("%i \t %i \t %i \t \n", indices[i], indices[i + 1], indices[i + 2]);
	}*/


	createMesh(vertices, indices, vertices.size(), indices.size());

}


void ToroideRodrigo::createMesh(std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices, unsigned int numOfVertices, unsigned int numberOfIndices) {

	indexCount = numberOfIndices;
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numberOfIndices, indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void ToroideRodrigo::renderToroideRodrigo() {
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, indexCount);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLE_STRIP, indexCount , GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ToroideRodrigo::~ToroideRodrigo() {

}