#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;


	articulacion_puerta = 0.0f;
	articulacion_puerta2 = 0.0f;



	MusicaSi = false;


	//Movimiento Avatar

	banderaCaminata = false;

	movimientoAvatar = 0.0f;
	rotAvatar = 0.0f;
	banderaLuzActivable = false;

	//Camaras
	tipoCamara = 1;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicializaci�n de GLFW
	if (!glfwInit())
	{
		printf("Fall� inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Proyecto Final", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tama�o de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Fall� inicializaci�n de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
	// Asignar valores de la ventana y coordenadas

	//Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se est� usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	//Movimiento AVatar: Y -> avanzar hacia adelante, U -> rotar Avatar
	if (key == GLFW_KEY_W)
	{
		if (theWindow->tipoCamara == 1) {
			if (action == GLFW_PRESS) {
				theWindow->movimientoAvatar = 1.0f;
				theWindow->banderaCaminata = true;
				theWindow->MusicaSi = true;

			}
			if (action == GLFW_RELEASE) {
				theWindow->banderaCaminata = false;
				theWindow->MusicaSi = false;
				theWindow->movimientoAvatar = 0.0f;
			}
		}
	}

	if (key == GLFW_KEY_S)
	{
		if (theWindow->tipoCamara == 1) {
			if (action == GLFW_PRESS) {
				theWindow->movimientoAvatar = -1.0f;
				theWindow->banderaCaminata = true;
				theWindow->MusicaSi = true;

			}
			if (action == GLFW_RELEASE) {
				theWindow->banderaCaminata = false;
				theWindow->MusicaSi = false;
				theWindow->movimientoAvatar = 0.0f;
			}
		}
	}

	if (key == GLFW_KEY_D)
	{
		if ((theWindow->tipoCamara == 1)) {
			if (action == GLFW_RELEASE) {
				theWindow->rotAvatar = 0.0;
			}
			else {
				theWindow->rotAvatar = -3.0;
			}
		}
		


	}
	if (key == GLFW_KEY_A)
	{
		if ((theWindow->tipoCamara == 1)) {
			if (action == GLFW_RELEASE) {
				theWindow->rotAvatar = 0.0;
			}
			else {
				theWindow->rotAvatar = 3.0;
			}
		}
		


	}

	if (key == GLFW_KEY_Q)
	{
		if (action == GLFW_PRESS) {
			switch (theWindow->tipoCamara) {
			case 1:
				theWindow->tipoCamara = 2;
				break;

			case 2:
				theWindow->tipoCamara = 3;
				break;

			case 3:
				theWindow->tipoCamara = 1;
				break;

			default:
				theWindow->tipoCamara = 1;
				break;
			}



		}

	}


	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}


	
	//PUERTA Abrir
	if (key == GLFW_KEY_P)
	{
		if (theWindow->articulacion_puerta <= 100)
		{
			theWindow->articulacion_puerta += 1.0;
			theWindow->articulacion_puerta2 -= 1.0;
		}
		
	}

	//PUERTA cerrar
	if (key == GLFW_KEY_O)
	{
		if (theWindow->articulacion_puerta >= 00)
		{
			theWindow->articulacion_puerta -= 1.0;
			theWindow->articulacion_puerta2 += 1.0;
		}
	}

	//}
	//ARTICULACION REVERSA
	if (key == GLFW_KEY_K)
	{
		theWindow->luz_del = 0.0; //apagamos la luz delantera


		//AQU� LA LUZ TRASERA (ROJA) DEBE ENCENDERSE, POR DEFECTO DEBE ESTAR APAGADA
		theWindow->luz_tras = 1.0;
	}

	//PARA ENCENDER Y APAGAR LAS LUCES PUNTUALES DE DESK_LAMP Y LUMINARIA

	if (key == GLFW_KEY_1)
	{
		if (action == GLFW_PRESS) {
			theWindow->banderaLuzActivable = !theWindow->banderaLuzActivable;
		}
	}

	//Botones para reproducir musica
	if (key == GLFW_KEY_I)
	{
		theWindow->MusicaSi = true;
	}
	if (key == GLFW_KEY_O)
	{
		theWindow->MusicaSi = false;
	}

}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}