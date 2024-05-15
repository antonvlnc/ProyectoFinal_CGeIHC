#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();


	//Animación puerta
	GLfloat getarticulacion_puerta() { return articulacion_puerta; }
	GLfloat getarticulacion_puerta2() { return articulacion_puerta2; }

	//Movimiento Avatar
	GLfloat getBanderaCaminata() { return banderaCaminata; }
	GLfloat getMovimientoAvatar() { return movimientoAvatar; }
	GLfloat getRotacionAvatar() { return rotAvatar; }

	//Camara
	GLint getTipoCamara() { return tipoCamara; }


	//Luces
	GLboolean getLuzActivable() { return banderaLuzActivable; }


	//PARA EL CONTROL DE LAS LUCES CUANDO EL AUTO AVANCE/RETROCEDA
	GLint getLuzDel() { return luz_del; }
	GLint getLuzTras() { return luz_tras; }

	//PARA LA MUSICA
	GLboolean getMusica() { return MusicaSi; }



	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);
	}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }

	~Window();
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;

	GLint luz_del = 1;
	GLint luz_tras = 0;

	bool mouseFirstMoved;
	GLboolean MusicaSi;
	//Avatar
	GLfloat movimientoAvatar, rotAvatar;
	GLboolean banderaCaminata;
	//Camara
	GLint tipoCamara; //1- camara ligada al avatar, 2 camara aerea, 3 la camara que hemos utilizado para las pr�cticas 
	//Luces
	GLboolean banderaLuzActivable;
	//Puerta
	GLfloat  articulacion_puerta, articulacion_puerta2;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};
