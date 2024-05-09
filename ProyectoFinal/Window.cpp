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

	articulacion_capo = 0.0f;

	articulacion_puerta = 0.0f;
	articulacion_puerta2 = 0.0f;

	articulacion_avanza = 0.0f;
	articulacion_reversa = 0.0f;


	articulacion_gira_der = 0.0f;
	articulacion_gira_izq = 0.0f;


	avanza_retrocede = 0.0f;

	avanza_retrocede_helicoptero = 0.0f;

	MusicaSi = true;

	muevex = 2.0f;

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
	if (key == GLFW_KEY_V)
	{
		if (theWindow->tipoCamara == 1) {
			if (action == GLFW_PRESS) {
				theWindow->movimientoAvatar = 1.0f;
				theWindow->banderaCaminata = true;

			}
			if (action == GLFW_RELEASE) {
				theWindow->banderaCaminata = false;
				theWindow->movimientoAvatar = 0.0f;
			}
		}
		


	}
	if (key == GLFW_KEY_B)
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
	if (key == GLFW_KEY_C)
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




	//CAPO ARRIBA
	if (key == GLFW_KEY_E)
	{
		if (theWindow->articulacion_capo > 45)
		{

		}
		else
		{
			theWindow->articulacion_capo += 10.0;
		}

	}
	//CAPO ABAJO
	if (key == GLFW_KEY_H)
	{
		if (theWindow->articulacion_capo < 5)
		{

		}
		else
		{
			theWindow->articulacion_capo -= 10.0;
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



	//RUEDA GIRA DER
	if (key == GLFW_KEY_L)
	{
		theWindow->articulacion_gira_der += 10.0;

	}



	//RUEDA GIRA IZQ
	if (key == GLFW_KEY_J)
	{
		theWindow->articulacion_gira_izq -= 10.0;

	}




	////ARTICULACION AVANZA
	//if (key == GLFW_KEY_I)
	//{

	//	theWindow->luz_tras = 0.0; //apagamos la luz trasera

	//	theWindow->articulacion_avanza += 10.0;
	//	//AUTO HACE TRANSLATE (AVANZA O RETROCEDE)
	//	theWindow->avanza_retrocede += 1.0;


	//	

	//	//AQU� LA LUZ DELANTERA (AZUL) DEBE ENCENDERSE, POR DEFECTO DEBE ESTAR ENCENDIDA
	//	theWindow->luz_del = 1.0;

	//}
	//ARTICULACION REVERSA
	if (key == GLFW_KEY_K)
	{
		theWindow->luz_del = 0.0; //apagamos la luz delantera

		theWindow->articulacion_avanza -= 10.0;
		//AUTO HACE TRANSLATE (AVANZA O RETROCEDE)
		theWindow->avanza_retrocede -= 1.0;

		//AQU� LA LUZ TRASERA (ROJA) DEBE ENCENDERSE, POR DEFECTO DEBE ESTAR APAGADA
		theWindow->luz_tras = 1.0;
	}


	//MOVIMIENTO HELIC�PTERO
	if (key == GLFW_KEY_N)
	{
		theWindow->avanza_helicoptero += 10.0;
		//AUTO HACE TRANSLATE (AVANZA O RETROCEDE)
		theWindow->avanza_retrocede_helicoptero += 1.0;

	}
	//ARTICULACION REVERSA
	if (key == GLFW_KEY_M)
	{
		theWindow->retrocede_helicoptero -= 10.0;
		//AUTO HACE TRANSLATE (AVANZA O RETROCEDE)
		theWindow->avanza_retrocede_helicoptero -= 1.0;

	}

	if (key == GLFW_KEY_Z)
	{
		theWindow->anguK += 10.0;
	}

	if (key == GLFW_KEY_X)
	{
		theWindow->anguK -= 10.0;
	}


	//PARA ENCENDER Y APAGAR LAS LUCES PUNTUALES DE DESK_LAMP Y LUMINARIA

	if (key == GLFW_KEY_1)
	{
		theWindow->K = 1;
		if (action == GLFW_PRESS) {
			theWindow->banderaLuzActivable = !theWindow->banderaLuzActivable;
		}
	}
	if (key == GLFW_KEY_0)
	{
		theWindow->K = 0;
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