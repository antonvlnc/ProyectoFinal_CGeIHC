#pragma once

#include <vector>
#include <string>
#include<glew.h>
#include<glm.hpp>
#include<glfw3.h>
#include <gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>

class ToroideRodrigo {
	
public:

	ToroideRodrigo();

	void createToroide(); //Realiza los c�lculos de los v�rtices, los mete a los vectores de �ndices y llama al procedimiento que hacer lo del VAO y eso

	void renderToroideRodrigo();


	~ToroideRodrigo();

private:
	float radioExterno, radioInterno;

	int numCirculos, resCirculos;

	GLuint VAO, VBO, IBO;
	GLsizei indexCount;

	void createMesh(std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices, unsigned int numOfVertices, unsigned int numberOfIndices);
};