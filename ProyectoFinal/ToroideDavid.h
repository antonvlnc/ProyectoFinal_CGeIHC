#pragma once

#include <vector>
#include <string>
#include<glew.h>
#include<glm.hpp>
#include<glfw3.h>
#include <gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>

class ToroideDavid {

public:

	ToroideDavid();

	ToroideDavid(float inRadius, float outRadius, int nSides, int nRings);

	void generateTorus(); //Realiza los cálculos de los vértices, los mete a los vectores de índices y llama al procedimiento que hacer lo del VAO y eso

	void initBuffers(std::vector<float>& vertices);

	void render();


	~ToroideDavid();

private:
	float R, r ;

	int numMinorSegments, numMajorSegments, vertexCount;

	GLuint vao, vboVertices;


};
