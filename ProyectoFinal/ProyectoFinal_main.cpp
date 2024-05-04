/*
Proyecto Final: CDMX ISEKAI

Integrantes:

- Francisco Hernandez Arturo
- Tapia Navarro Rodrigo
- Toledo Valencia Jesus Antonio
- Valenzuela Vigil Angel David
*/


#define STB_IMAGE_IMPLEMENTATION

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

//para probar el importer
//#include<assimp/Importer.hpp>


#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"
#include "MainAvatar.h"
#include "Edificio.h"
#include "Lampara.h"

//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

//Para sonido
#include <irrklang.h>
using namespace irrklang;

//VARIABLES Y CONSTANTES
const float toRadians = 3.14159265f / 180.0f;
const float maxAngle = 180.0f;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

//Para animaci�n
bool alaIzq = true;
bool alaDer = true;
float giraAlaIzq;
float giraAlaDer;
float anguloAlaIzq;
float anguloAlaDer;
float giraAlaOffset;
float movAlaOffset;

//Para la animación del helicoptero
bool avanzaHelicoptero, avanzaHelicoptero2, avanzaHelicoptero3, avanzaHelicoptero4, avanzaHelicoptero5, avanzaHelicoptero6;
bool controlDeltaTimeDesborde, controlDeltaTimeDesborde2;
float movHelice;
float giraHeliceOffset;
float rotacionHelicopteroOffset;
float movHelicopteroX, movHelicopteroY, movHelicopteroZ, movHelicopteroOffset;
float inclinacion, rotacionHelicopteroY;
clock_t tiempoInicial;

//Animacion de la nave de Dexter
float movBaseNave;
float giraBaseOffset;
bool movNave;
float movNaveZ, movNaveX;
float avanzaNave;
bool avanzaNave2, avanzaNave3, avanzaNave4, avanzaNave5, avanzaNave6;
float rotacionNave, inclinacionNave;
float rotacionNaveOffset;
float movNaveOffset;

//Animacion La pulga
bool subeTorso;
float sube;
float giraTorsoOffset;
float movTorsoOffset;
float anguloTorso;


//Animacion metrobus -----------------------------------------------------------------------------------------------------------------------------------------------
bool flagBus1, flagBus2, flagBus3, flagBus4, flagBus5, flagBus6, flagBus7, flagBus8, flagBus9, flagBus10, flagBus11, flagBus12, flagBus13;
float rotacionAutomaticaRuedaZ, rotacionAutomaticaRuedaOffSet;
float metrobusX, metrobusY, metrobusZ;
float traslacionMetrobusOffSet;

//para luces
unsigned int pointLightCount = 0;
unsigned int pointLightCount2 = 0;
unsigned int spotLightCount = 0; //ARREGLO 0 -> TODAS LAS LUCES ENCENDIDAS
unsigned int spotLightCount2 = 0;
float tiempoTranscurrido;
GLfloat duracionCicloDiayNoche = 40.0; //cantidad de segundos que va a durar el ciclo de dia/noche, el dia dura 2*duracionCicloDiaYNoche
//GLfloat lightDirectionIncrement = 0.5f;
GLfloat lightDirectionIncrement = maxAngle / (duracionCicloDiayNoche * 60.0);
GLboolean esDeDia = true;
GLfloat anguloLuz = -10.0f;


//Uniforms

GLuint uniformProjection;
GLuint uniformModel;
GLuint uniformView;
GLuint uniformEyePosition;
GLuint uniformSpecularIntensity;
GLuint uniformShininess;
GLuint uniformColor;

//VENTANAS
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

//CAMARAS
Camera camera;


//Declcaración de texturas

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture reforma_layout; //piso
Texture AstrodomoTexture;
Texture grass;


//DECLARACION DE MODELOS

//Dexter
MainAvatar dexter;
Edificio dianaCazadora;
Edificio BBVA_Pixies;
Edificio estelaDeLuz;
Edificio astrodomo;
Edificio slamminDonuts;
Edificio bigWand;
Edificio casaDexter;
Edificio CasaTimmy;



Lampara luminariaP8;

//GENERAL
Model luminaria;
Model angel_independencia;
Model angel_independencia_ala;
Model bbva;
Model estela_de_luz;
Model helicoptero_base;
Model helicoptero_helice;
Model camellon;
Model metrobus;
Model metrobus_llanta_izq;
Model metrobus_llanta_der;
Model puerta_reja;
Model reja_izq;
Model reja_der;




//Padrinos Magicos
Model bus_padrinos;
Model big_wand;
Model letrero_dimsdale;
Model letras_letrero_dimsdale;
Edificio dimmadome;
Model taxi;
Edificio letras_dimmsdale;
Edificio letrero_dimmsdale;

//Laboratorio de Dexter
Model casa_dexter;
Model dexter_body;
Model dexter_leg;
Model dexter_arm;
Model nave_cabina;
Model nave_extra;

//Ratatouille
Model vespa;
Edificio gusteaus;
Edificio gusteau_sign;

//Mucha Lucha
Model tienda_donas;
Model laPulgaInferior;
Model laPulgaSuperior;
Edificio tokyo_tree;
Edificio academy;
Edificio poster1;
Edificio poster2;
Edificio cactus;
Edificio ring;


//SKYBOX
Skybox skybox;


//MATERIALES
Material Material_brillante;
Material Material_opaco;
//Sphere cabeza = Sphere(0.5, 20, 20);

//DECLARACION DE LAS LUCES

// luz direccional
DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
PointLight pointLights2[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotLights2[MAX_SPOT_LIGHTS];


//SHADERS
// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";
// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

//DECLARACION DE FUNCIONES. La implementación se encuentra al final del código

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset);
void CreateObjects();
void CreateShaders();
void InitializeModels();
void InitializeTextures();
void InitializeLights();
DirectionalLight calcSunlight();
void renderAngelIndependencia();
void renderTimmyBus();
void renderVespa();
void renderHelicoptero();
void renderLaPulga();
void renderTaxi();
void renderNaveDexter();
void renderCamellon();
void renderMetrobus();
void renderPuertaReja();

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	InitializeModels();
	InitializeTextures();
	InitializeLights();

	//CAMARAS
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.5f, 0.5f);


	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0); //PARA EL CHASIS
	glm::mat4 modelaux2(1.0);
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	uniformProjection = 0;
	uniformModel = 0;
	uniformView = 0;
	uniformEyePosition = 0;
	uniformSpecularIntensity = 0;
	uniformShininess = 0;
	uniformColor = 0;

	//Animaciones
	alaIzq = true;
	alaDer = true;
	giraAlaIzq = 0.0f;
	giraAlaDer = 0.0f;
	anguloAlaIzq = 90.0f;
	anguloAlaDer = 90.0f;
	giraAlaOffset = 1.0f;
	movAlaOffset = 1.0f;

	//Animacion helicoptero
	avanzaHelicoptero = controlDeltaTimeDesborde = true;
	avanzaHelicoptero2 = avanzaHelicoptero3 = avanzaHelicoptero4 = avanzaHelicoptero5 = avanzaHelicoptero6 = false;
	movHelice = 0.0f;
	giraHeliceOffset = 20.0f;
	movHelicopteroX = movHelicopteroY = movHelicopteroZ = 0.0f;
	movHelicopteroOffset = 3.1f;
	inclinacion = rotacionHelicopteroY = 0.0;
	rotacionHelicopteroOffset = 1.0f;

	//Animacion nave Dexter
	movBaseNave = 0.0f;
	giraBaseOffset = 2.0f;
	movNave, avanzaNave = true;
	giraBaseOffset = 5.0f;
	movNaveZ, movNaveX = 0.0f;
	avanzaNave2, avanzaNave3, avanzaNave4, avanzaNave5, avanzaNave6 = false;
	rotacionNave = 90.0f;
	inclinacionNave = 20.0f;
	rotacionNaveOffset = 1.0f;
	movNaveOffset = 2.0f;

	//Animacion pulga
	subeTorso = true;
	sube = 0.0f;
	anguloTorso = 0.0f;
	giraTorsoOffset = 0.5f;
	movTorsoOffset = 0.5f;

	//Animacion metrobus
	flagBus1 = true;
	flagBus2 = flagBus3 = flagBus4 = flagBus5 = flagBus6 = flagBus7 = flagBus8 = flagBus9 = flagBus10 = flagBus11 = flagBus12 = flagBus13 = false;
	rotacionAutomaticaRuedaZ = 0.0f;
	rotacionAutomaticaRuedaOffSet = 3.0f;
	traslacionMetrobusOffSet = 0.01f;
	metrobusX = metrobusY = metrobusZ = -10.0f;
	controlDeltaTimeDesborde2 = true;
	//------------------SONIDO-----------------------
	//Sonido ambiental
	//ISoundEngine* Ambiental = createIrrKlangDevice();
	//Ambiental->play2D("Sound/Ambiental.wav", true); 
	//Ambiental->setSoundVolume(0.2f);

	////Pista de fondo
	ISoundEngine* Intro = createIrrKlangDevice();
	Intro->play2D("Sound/Dexter_Pista.wav", true); //cambiar a cancion en loop sin la voz
	Intro->setSoundVolume(0.15f);

	////Sonido con teclado (Pendiente)
	/*ISoundEngine* AstrodomoSound = createIrrKlangDevice();
	AstrodomoSound->play2D("Sound/Mucha_Lucha.wav", true);
	AstrodomoSound->setSoundVolume(0.1f);*/


	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//----------------ANIMACIONES-------------- Aquí irán las funciones de las animaciones
		mainLight = calcSunlight();


		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();

		//---------INICIACILIZACION DE VARIABLES UNIFORM-------------
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//----------------LUCES-----------
		// luz ligada a la c�mara de tipo flash
		//sirve para que en tiempo de ejecuci�n (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		//spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		/*shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);*/


		//-------------------------PISO-----------------------------
		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(450.0f, 1.0f, 700.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		reforma_layout.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);


		//RENDERIZAMOS EL PISO
		meshList[2]->RenderMesh();

		model = modelaux;

		//PISO 2

		//Más piso para el letrero y letras de Dimmsdale

		/*glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);*/

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 850.0f));
		model = glm::scale(model, glm::vec3(450.0f, 1.0f, 150.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		grass.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		//Piso 3

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -850.0f));
		model = glm::scale(model, glm::vec3(450.0f, 1.0f, 150.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		grass.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();



		//INSTANCIAMIENTO DE LOS MODELOS
		//X para ancho del mapa y Z para largo del mapa


		//--------------------Modelos Generales del mundo-------------------

		//Diana cazadora
		dianaCazadora.renderModel();

		//Edificio BBVA/Pixies
		BBVA_Pixies.renderModel();

		//Helicoptero
		renderHelicoptero();

		//Estela de Luz
		estelaDeLuz.renderModel();


		//angel de la independencia
		renderAngelIndependencia();


		//camellon por piezas
		renderCamellon();

		//Metrobus
		renderMetrobus();

		//Puerta con reja
		renderPuertaReja();

		//-------------Modelos Mucha Lucha------------------

		//ASTRODOMO
		astrodomo.renderModel();

		//La pulga
		renderLaPulga();

		//Slammin Donuts
		slamminDonuts.renderModel();

		//Academy
		academy.renderModel();

		//Poster 1
		poster1.renderModel();

		//Poster 2
		poster2.renderModel();

		//Cactus
		cactus.renderModel();

		//Ring
		ring.renderModel();

		//--------------Modelos - Padrinos Mágicos------------

		//Big Wand
		bigWand.renderModel();


		//Bus
		renderTimmyBus();

		//Dimmadome
		dimmadome.renderModel();

		//Taxi
		renderTaxi();

		//casa timmy
		CasaTimmy.renderModel();

		//letras dimmsdale
		letras_dimmsdale.renderModel();

		
		//letrero dimmsdale
		letrero_dimmsdale.renderModel();
		//

		//------------------Modelos - Ratatouille------------
		
		//Vespa
		renderVespa();

		//Restaurante Gusteau
		gusteaus.renderModel();

		//Gusteau Sign
		gusteau_sign.renderModel();



		//-------------------Modelos - Laboratorio de Dexter---------------------
		dexter.setUniformModel(uniformModel);
		dexter.setMovimiento(mainWindow.getMovimientoAvatar(), mainWindow.getRotacionAvatar(), mainWindow.getrotBrazoPiernas());
		dexter.renderMainAvatar();
		

		//Casa de dexter
		casaDexter.renderModel();


		//tokyo tree
		tokyo_tree.renderModel();

		//nave dexter
		renderNaveDexter();


		//MODELO DE LUMINARIA PARA REPORTE 08
		luminariaP8.renderModel();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}


void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};



	GLfloat floorVertices[] = {
		-1.0f, 0.0f, -1.0f,		0.0f, 0.0f,			0.0f, -1.0f, 0.0f, //0
		1.0f, 0.0f, -1.0f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f, //1
		-1.0f, 0.0f, 1.0f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f, //2
		1.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f //3
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1); //meshlist0

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2); //mesh list 1


	//PISO
	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3); //mesh list 2

	//-----------
	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4); //mesh list 3

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void InitializeModels() {
	//----------Modelos Generales---------------------

	//Angel de la independencia
	angel_independencia = Model();
	angel_independencia.LoadModel("Models/Angel.obj");

	//Alas del angel de la independencia
	angel_independencia_ala = Model();
	angel_independencia_ala.LoadModel("Models/AngelAla.obj");

	//Edificio BBVA
	BBVA_Pixies = Edificio("Models/BBVA.obj", &uniformModel, glm::vec3(350.0f, -1.0f, 350.0f), glm::vec3(220.0f));
	BBVA_Pixies.setRotY(270.0f);

	//Estela de luz
	estelaDeLuz = Edificio("Models/Estela.obj", &uniformModel, glm::vec3(315.0f, -1.0f, 805.0f), glm::vec3(5.0f));

	//Cuerpo del helicoptero
	helicoptero_base = Model();
	helicoptero_base.LoadModel("Models/Helicoptero_Base.obj");

	//helice del helicoptero
	helicoptero_helice = Model();
	helicoptero_helice.LoadModel("Models/Helicoptero_Helice.obj");

	//camellon por piezas

	camellon = Model();
	camellon.LoadModel("Models/Camellon.obj");

	//Metrobus

	metrobus = Model();
	metrobus.LoadModel("Models/Metrobus.obj");

	//Metrobus - Llanta Izquierda
	metrobus_llanta_izq = Model();
	metrobus_llanta_izq.LoadModel("Models/MetrobusLlantaIzq.obj");

	//Metrobus - Llanta Derecha
	metrobus_llanta_der = Model();
	metrobus_llanta_der.LoadModel("Models/MetrobusLlantaDer.obj");


	//LUMINARIA PARA REPORTE 08

	luminariaP8 = Lampara("Models/luminaria_text.obj", &uniformModel, glm::vec3(-90.0f, -0.95f, -100.0f), glm::vec3(4.0f));

	//Puerta con reja
	puerta_reja = Model();
	puerta_reja.LoadModel("Models/PuertaReja.obj");

	reja_der = Model();
	reja_der.LoadModel("Models/RejaDer.obj");

	reja_izq = Model();
	reja_izq.LoadModel("Models/RejaIzq.obj");





	//----------Modelos Mucha Lucha---------------------

	astrodomo = Edificio("Models/MuchaLucha/Astrodomo.obj", &uniformModel, glm::vec3(-295.0f, -2.0f, -50.0f), glm::vec3(5.0f));
	astrodomo.setRotY(-270.0f);

	slamminDonuts = Edificio("Models/MuchaLucha/SlamminDonuts.obj", &uniformModel, glm::vec3(-275.0f, 0.5f, -580.0), glm::vec3(1.6f));
	slamminDonuts.setRotY(90.0f);

	laPulgaInferior = Model();
	laPulgaInferior.LoadModel("Models/MuchaLucha/LaPulga_Inferior.obj");


	laPulgaSuperior = Model();
	laPulgaSuperior.LoadModel("Models/MuchaLucha/LaPulga_Superior.obj");

	tokyo_tree = Edificio("Models/MuchaLucha/TokyoTree.obj", &uniformModel, glm::vec3(-180.0f, 0.0f, -225.0), glm::vec3(5.0f));
	tokyo_tree.setRotY(90.0f);

	academy = Edificio("Models/MuchaLucha/Academy.obj", &uniformModel, glm::vec3(-320.0f, 0.0f, -360.0), glm::vec3(12.0f));
	academy.setRotY(90.0f);

	poster1 = Edificio("Models/MuchaLucha/Poster1.obj", &uniformModel, glm::vec3(-246.0f, 100.0f, -290.0), glm::vec3(12.0f));
	poster1.setRotY(90.0f);

	poster2 = Edificio("Models/MuchaLucha/Poster2.obj", &uniformModel, glm::vec3(-246.0f, 100.0f, -430.0), glm::vec3(12.0f));
	poster2.setRotY(90.0f);

	cactus = Edificio("Models/MuchaLucha/Cactus.obj", &uniformModel, glm::vec3(185.0f, 3.5f, 270.0), glm::vec3(8.0f));
	cactus.setRotY(90.0f);

	ring = Edificio("Models/MuchaLucha/Ring.obj", &uniformModel, glm::vec3(220.0f, 1.0f, -30.0), glm::vec3(40.0f));
	ring.setRotY(270.0f);






	//----------Modelos Padrinos Magicos---------------------


	bus_padrinos = Model();
	bus_padrinos.LoadModel("Models/Padrinos/Bus.obj");

	dianaCazadora = Edificio("Models/DianaCupido.obj", &uniformModel, glm::vec3(0.0f, -1.0f, 175.0f), glm::vec3(4.0f, 5.0f, 4.0f));
	dianaCazadora.setRotY(-180.0f);

	bigWand = Edificio("Models/Padrinos/BigWand.obj", &uniformModel, glm::vec3(-315.0f, -0.5f, 805.0), glm::vec3(20.0f));
	//bigWand.setRotY(90.0f);

	CasaTimmy = Edificio("Models/Padrinos/TimmyH_Tex2.obj", &uniformModel, glm::vec3(370.0f, 1.0f, 600.0), glm::vec3(34.0f));
	CasaTimmy.setRotY(270.0f);

	dimmadome= Edificio("Models/Padrinos/Dimmadome.obj", &uniformModel, glm::vec3(310.0f, 1.0f, -300.0), glm::vec3(18.0f));
	dimmadome.setRotY(270.0f);

	taxi = Model();
	taxi.LoadModel("Models/Padrinos/Taxi.obj");

	letras_dimmsdale = Edificio("Models/Padrinos/Dimmsdale.obj", &uniformModel, glm::vec3(0.0f, 1.0f, 845.0), glm::vec3(25.0f));
	letras_dimmsdale.setRotY(180.0f);

	letrero_dimmsdale = Edificio("Models/Padrinos/DimsdaleSign.obj", &uniformModel, glm::vec3(230.0f, 1.0f, -620.0), glm::vec3(1.9f));
	letrero_dimmsdale.setRotY(180.0f);




	//----------Modelos Lab. de Dexter---------------------

	casaDexter = Edificio("Models/DextersLab/CasaDexter.obj", &uniformModel, glm::vec3(-380.0f, -0.5f, 370.0), glm::vec3(40.0f));
	casaDexter.setRotY(90.0f);

	nave_cabina = Model();
	nave_cabina.LoadModel("Models/DextersLab/NaveDomo.obj");

	nave_extra = Model();
	nave_extra.LoadModel("Models/DextersLab/NaveCierra.obj");



	//AVATAR (DEXTER)

	dexter = MainAvatar(glm::vec3(0.0f, 0.5f, -650.0f), 15.0f, glm::vec3(3.0f, 3.0f, 3.0f));


	//-------------------------Modelos Ratatouille-----------------------------------------

	//moto del chef chaparro
	vespa = Model();
	vespa.LoadModel("Models/Ratatouille/vespa.obj");

	//Gusteau's

	gusteaus = Edificio("Models/Ratatouille/gusteaus.obj", &uniformModel, glm::vec3(-265.0f, 1.0f, 575.0), glm::vec3(13.0f));
	gusteaus.setRotY(90.0f);

	//Anuncio Gusteau's

	gusteau_sign = Edificio("Models/Ratatouille/GusteauSign.obj", &uniformModel, glm::vec3(-255.0f, 145.0f, 575.0), glm::vec3(35.0f));
	gusteau_sign.setRotY(90.0f);




	

	//camera = Camera(glm::vec3(370.0f, 712.0f, 285.0), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.5f, 0.5f);

}

void InitializeTextures() { //Texturas y skybox
	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();

	reforma_layout = Texture("Textures/reforma_layout.png");
	reforma_layout.LoadTextureA();

	grass = Texture("Textures/grass.png");
	grass.LoadTextureA();


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/sky-right.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-left.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-down.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-up.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-front.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-back.jpg");

	skybox = Skybox(skyboxFaces);

	//SKYBOX

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

}

void renderAngelIndependencia() {

	if (alaIzq && alaDer)
	{
		if (anguloAlaIzq >= 0.0f)
		{
			anguloAlaIzq -= movAlaOffset * deltaTime;
			giraAlaIzq += giraAlaOffset * deltaTime;
			anguloAlaDer -= movAlaOffset * deltaTime;
			giraAlaDer -= giraAlaOffset * deltaTime;
		}
		else
		{
			alaIzq = false;
			alaDer = false;
		}
	}

	else
	{
		if (anguloAlaIzq <= 90.0f)
		{
			anguloAlaIzq += movAlaOffset * deltaTime;
			giraAlaIzq -= giraAlaOffset * deltaTime;
			anguloAlaDer += movAlaOffset * deltaTime;
			giraAlaDer += giraAlaOffset * deltaTime;
		}
		else
		{
			alaIzq = true;
			alaDer = true;
		}
	}

	//Angel de la independencia
	glm::mat4 model, modelaux2;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(5.0f, -1.0f, -530.0));
	model = glm::scale(model, glm::vec3(7.0f, 8.0f, 7.0f));
	model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelaux2 = model;
	angel_independencia.RenderModel();

	model = glm::translate(model, glm::vec3(0.0f, 28.5f, -0.5f));
	model = glm::rotate(model, giraAlaIzq * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	//Ala del angel 1
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	angel_independencia_ala.RenderModel();


	model = modelaux2;

	model = glm::translate(model, glm::vec3(0.0f, 28.5f, -0.5f));
	model = glm::rotate(model, giraAlaDer * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	//Ala del angel 2
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	angel_independencia_ala.RenderModel();

}

void InitializeLights() {
	//APARTADO DE LUCES
//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);

	//contador de luces puntuales


	//Declaraci�n de primer luz puntual (magenta) | PARA LUMINARIA
	pointLights[0] = PointLight(1.0f, 0.0f, 1.0f,
		0.0f, 3.0f,
		-60.0f, 25.5f, 65.0f,
		1.0f, 0.045f, 0.0075f);
	pointLightCount++;

	//LUZ PUNTUAL PARA LA DESK LAMP
	pointLights[1] = PointLight(1.0f, 1.0f, 1.0f,
		0.0f, 3.0f,
		25.0f, 2.5f, 7.0f,
		1.0f, 0.14f, 0.07f);
	pointLightCount++;

	//LUZ NEGRA PARA APAGAR (ARREGLO 2 DE POINTLIGHTS)
	pointLights2[0] = PointLight(0.0f, 0.0f, 0.0f,
		0.0f, 24.0f,
		4.0f, 9.0f, 12.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount2++;

	//ARREGLO 1 -> CUANDO EL AUTO AVANZA
	   //unsigned int spotLightCount3 = 0; //ARREGLO 2 -> CUANDO EL AUTO RETROCEDE
	   //PRIMER ARREGLO DE SPOTLIGHTS (TODAS LAS SPOTLIGHTS ENCENDIDAS)
	   // Luz vehiculo delantera (azul)
	spotLights[0] = SpotLight(0.0f, 0.0f, 1.0f,
		1.0f, 2.0f,
		0.0f, 50.0f, -10.0f,
		0.0f, 0.0f, -10.0f,
		1.0f, 0.01f, 0.001f,
		20.0f);
	spotLightCount++;


	// Luz helicoptero
	spotLights[1] = SpotLight(1.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.01f, 0.001f,
		15.0f);
	spotLightCount++;

	//LUZ SPOTLIGHT QUE ILUMINA PUERTA DE REJA
	spotLights[2] = SpotLight(0.0f, 1.0f, 1.0f,
		3.0f, 5.0f,
		-2.0f, 12.0f, -5.0f,
		0.0f, 0.0f, 5.0f,
		1.0f, 0.01f, 0.001f,
		15.0f);
	spotLightCount++;



	// Luz vehiculo trasera (rojo) APAGADA
	spotLights[3] = SpotLight(0.0f, 0.0f, 0.0f,
		1.0f, 2.0f,
		0.0f, 50.0f, 10.0f,
		0.0f, 0.0f, 10.0f,
		1.0f, 0.01f, 0.001f,
		20.0f);
	spotLightCount++;
	//SEGUNDO ARREGLO (CUANDO EL AUTO RETROCEDE)
	// Luz vehiculo delantera (azul) APAGADA
	spotLights2[0] = SpotLight(0.0f, 0.0f, 0.0f,
		1.0f, 2.0f,
		0.0f, 50.0f, -10.0f,
		0.0f, 0.0f, -10.0f,
		1.0f, 0.01f, 0.001f,
		20.0f);
	spotLightCount2++;
	// Luz helicoptero
	spotLights2[1] = SpotLight(1.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.01f, 0.001f,
		15.0f);
	spotLightCount2++;

	//LUZ SPOTLIGHT QUE ILUMINA PUERTA DE REJA
	spotLights2[2] = SpotLight(0.0f, 1.0f, 1.0f,
		3.0f, 5.0f,
		-2.0f, 12.0f, -5.0f,
		0.0f, 0.0f, 5.0f,
		1.0f, 0.01f, 0.001f,
		15.0f);
	spotLightCount2++;


	//Luz trasera del auto ENCENDIDA
	spotLights2[3] = SpotLight(1.0f, 0.0f, 0.0f,
		1.0f, 2.0f,
		0.0f, 50.0f, 10.0f,
		0.0f, 0.0f, 10.0f,
		1.0f, 0.01f, 0.001f,
		20.0f);
	spotLightCount2++;
}

DirectionalLight calcSunlight() {
	GLfloat intensity = 0.4f;
	GLfloat xDir, yDir, red, green, blue;
	xDir = 0.0f;
	yDir = 0.0f;




	if (anguloLuz >= 180.0) {
		anguloLuz = 0.0f;
		esDeDia = !esDeDia;
	}
	else {
		anguloLuz += lightDirectionIncrement * deltaTime;
	}

	xDir = cos(glm::radians(anguloLuz));
	yDir = (-1.0) * sin(glm::radians(anguloLuz));

	if (esDeDia) {
		red = 0.8f + 0.2 * sin(glm::radians(anguloLuz));
		green = 0.6f + 0.4 * sin(glm::radians(anguloLuz));
		blue = 0.6f + 0.4 * sin(glm::radians(anguloLuz));
		intensity = 0.6f;
	}
	else {
		red = 0.6f - 0.1 * sin(glm::radians(anguloLuz));
		green = 0.6f - 0.1 * sin(glm::radians(anguloLuz));
		blue = 0.6f + (0.4 * sin(glm::radians(anguloLuz)));
		intensity = 0.3f;
	}



	DirectionalLight sol = DirectionalLight(red, green, blue,
		intensity, 0.5f,
		xDir, yDir, 0.0f);

	return sol;
}


void renderVespa() {

	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(45.0f, -0.5f, -300.0));
	model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	vespa.RenderModel();

}



void renderMetrobus() {
	//
	//// Esto será indefinido
	//rotacionAutomaticaRuedaZ += rotacionAutomaticaRuedaOffSet * deltaTime;
	//float radio1 = 10.0f;
	////metrobus rutina circunferencia
	////metrobusZ = sqrt(double(pow(metrobusX, 2)) + double(pow(radio1, 2)));
	//if (metrobusZ < 10.0f) {
	//	//metrobusZ += traslacionMetrobusOffSet * deltaTime;
	//}
	//if (controlDeltaTimeDesborde2) {
	//	metrobusZ = metrobusX = 0.0f;
	//	controlDeltaTimeDesborde2 = false;
	//}
	//printf("(%f,%f,%f)\n", sqrt(pow(metrobusZ, 2)), metrobusY, metrobusZ);
	glm::mat4 model,modelaux;

	model = glm::mat4(1.0);
	//0.0f, -1.0f, 175.0f
	model = glm::translate(model, glm::vec3(0.0f + sqrt(pow(100,2) - pow(metrobusZ,2)), 2.5f + metrobusY, 175.0f + metrobusZ));
	modelaux = model;
	model = glm::scale(model, glm::vec3(12.0f));	
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	metrobus.RenderModel();

	model = modelaux;

	//Llantas izquierdas

	//delantera
	model = glm::translate(model, glm::vec3(10.0f, 6.0f, 25.0));
	model = glm::scale(model, glm::vec3(12.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotacionAutomaticaRuedaZ * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	metrobus_llanta_izq.RenderModel();

	model = modelaux;


	//media
	model = glm::translate(model, glm::vec3(10.0f, 6.0f, -26.5));
	model = glm::scale(model, glm::vec3(12.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotacionAutomaticaRuedaZ * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	metrobus_llanta_izq.RenderModel();

	model = modelaux;


	//trasera
	model = glm::translate(model, glm::vec3(10.0f, 6.0f, -42.0));
	model = glm::scale(model, glm::vec3(12.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotacionAutomaticaRuedaZ * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	metrobus_llanta_izq.RenderModel();

	model = modelaux;



	//Llantas derechas
	
	//delantera
	model = glm::translate(model, glm::vec3(-10.0f, 6.0f, 25.0));
	model = glm::scale(model, glm::vec3(12.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotacionAutomaticaRuedaZ * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	metrobus_llanta_der.RenderModel();

	model = modelaux;

	//media
	model = glm::translate(model, glm::vec3(-10.0f, 6.0f, -26.5));
	model = glm::scale(model, glm::vec3(12.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotacionAutomaticaRuedaZ * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	metrobus_llanta_izq.RenderModel();

	model = modelaux;

	//trasera
	model = glm::translate(model, glm::vec3(-10.0f, 6.0f, -42.0));
	model = glm::scale(model, glm::vec3(12.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotacionAutomaticaRuedaZ * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	metrobus_llanta_izq.RenderModel();

	model = modelaux;


}





void renderHelicoptero(){

	//Helicoptero
		movHelice += giraHeliceOffset * deltaTime;

		// INICIALIZA LA ANIMACIÓN DEL RECORRIDO DEL HELICOPTERO
		if (avanzaHelicoptero) {
			//movHelicopteroX -= movHelicopteroOffset * deltaTime;
			if (movHelicopteroY < 5.0f) {
				movHelicopteroY += movHelicopteroOffset * deltaTime;
				if (controlDeltaTimeDesborde) {
					movHelicopteroY = 0.0f;
					controlDeltaTimeDesborde = false;
				}
			}
			else {
				avanzaHelicoptero = false;
				avanzaHelicoptero2 = true;
			}
		}
		if (avanzaHelicoptero2) {
			if (movHelicopteroX > -300.0f) {
				inclinacion = 0.4f;
				movHelicopteroX -= movHelicopteroOffset * deltaTime;
				if (movHelicopteroX < -50.0f) {
					movHelicopteroY -= movHelicopteroOffset * deltaTime;
				}
				
			}
			else {
				avanzaHelicoptero2 = false;
				avanzaHelicoptero3 = true;
			}
		}

		if (avanzaHelicoptero3){
			if (movHelicopteroZ > -850.0f) {
				if (rotacionHelicopteroY > 90.0f) {
					movHelicopteroZ -= movHelicopteroOffset * deltaTime;
				}
				else {
					rotacionHelicopteroY += rotacionHelicopteroOffset * deltaTime;
				}
			}
			else {
				avanzaHelicoptero3 = false;
				avanzaHelicoptero4 = true;
			}
		}

		if (avanzaHelicoptero4) {
			if (movHelicopteroZ < 0.0f){
				if (rotacionHelicopteroY > 270.0f) {
					movHelicopteroZ += movHelicopteroOffset * deltaTime;
				}
				else {
					rotacionHelicopteroY += rotacionHelicopteroOffset * deltaTime;
				}
			}
			else {
				avanzaHelicoptero4 = false;
				avanzaHelicoptero5 = true;
			}
		}

		if (avanzaHelicoptero5) {
			if (movHelicopteroX < 0.0f) {
				if (rotacionHelicopteroY > 180.0f) {
					rotacionHelicopteroY -= rotacionHelicopteroOffset * deltaTime;
				}
				else {
					movHelicopteroX += movHelicopteroOffset * deltaTime;
					if (movHelicopteroX < -50.0f) {
						movHelicopteroY += movHelicopteroOffset * deltaTime;
					}
				}
			}
			else {
				if (rotacionHelicopteroY > 0.0f) {
					if (inclinacion > 0.0f)
						inclinacion -= 0.01 * deltaTime;
					rotacionHelicopteroY -= rotacionHelicopteroOffset * deltaTime;
				}
				else {
					avanzaHelicoptero5 = false;
					avanzaHelicoptero6 = true;
				}
			}
		}
		
		if (avanzaHelicoptero6) {
			if (movHelicopteroY > 0.0f) {
				movHelicopteroY -= movHelicopteroOffset * deltaTime;
				tiempoInicial = clock();
			}
			else {
				tiempoTranscurrido = (double)(clock() - tiempoInicial) / CLOCKS_PER_SEC;
				if (tiempoTranscurrido > 5.0f) {
					avanzaHelicoptero6 = false;
					avanzaHelicoptero = true;
				}
			}
		}

		glm::mat4 model, modelauxHeli;
		//Helicoptero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(350.0f + movHelicopteroX, 702.0f + movHelicopteroY, 285.0 + movHelicopteroZ));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, -rotacionHelicopteroY * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, inclinacion, glm::vec3(0.0f, 0.0f, 01.0f));
		//model = glm::rotate(model, -15.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelauxHeli = model;
		helicoptero_base.RenderModel();
		
		//Mousequeherramienta misteriosa que nos servirá para despues
		//Previo prueba cambio de perspectiva
		/*camera.setPosicionX(350.0f + movHelicopteroX);
		camera.setPosicionY(702.0f + movHelicopteroY);
		camera.setPosicionZ(285.0 + movHelicopteroZ);*/

		model = glm::translate(model, glm::vec3(0.5f, 23.5f, 0.0f));
		model = glm::rotate(model, movHelice * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		helicoptero_helice.RenderModel();
}



void renderTimmyBus() {

	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-35.0f, -0.5f, -260.0));
	model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	bus_padrinos.RenderModel();

}

void renderLaPulga() {
	

	if (subeTorso)
	{
		if (anguloTorso > 0.0f)
		{
			
			anguloTorso -= movTorsoOffset * deltaTime;
			sube -= giraTorsoOffset * deltaTime;
			//printf("Sube %f \n", sube);

			if (controlDeltaTimeDesborde) {
				sube = 0.0f;
				controlDeltaTimeDesborde = false;
			}
		}
		else
		{
			subeTorso = false;
		}
	}

	else
	{
		if (anguloTorso < 50.0f)
		{
			anguloTorso += movTorsoOffset * deltaTime;
			sube += giraTorsoOffset * deltaTime;
			//printf("Sube %f \n", sube);
		}
		else
		{
			subeTorso = true;
		}
	}


	glm::mat4 model, modelauxPulga;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(170.0f, 10.0f, -95.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelauxPulga= model;
	laPulgaInferior.RenderModel();

	model = glm::translate(model, glm::vec3(0.0f, 0.5f, -1.0f));
	model = glm::rotate(model, sube * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	laPulgaSuperior.RenderModel();
	model = modelauxPulga;
}

void renderTaxi() {

	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(35.0f, -0.5f, 375.0));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	taxi.RenderModel();

}


void renderNaveDexter() {

	movBaseNave += giraBaseOffset * deltaTime;
	//tiempoInicial = clock();
	
	if (avanzaNave) {
		if (movNaveZ > -1275.0f) {
			movNaveZ -= movNaveOffset * deltaTime;
			//printf("ValorZ1: %f \n", movNaveZ);
			if (controlDeltaTimeDesborde) {
				movNaveZ = 0.0f;
				controlDeltaTimeDesborde = false;
			}
		}
		else {
			avanzaNave = false;
			rotacionNave = 180.0f;
			avanzaNave2 = true;

		}
	}

	if (avanzaNave2) {
		if (movNaveX > -240) {
			movNaveX -= movNaveOffset * deltaTime;
			//printf("ValorX1: %f \n", movNaveX);
		}
		else {
			avanzaNave2 = false;
			rotacionNave = 270.0f;
			avanzaNave3 = true;
		}
	}

	if (avanzaNave3) {
		if (movNaveZ < 0.0f) {
			movNaveZ += movNaveOffset * deltaTime;
		}
		else {
			avanzaNave3 = false;
			rotacionNave = 360.0f;
			avanzaNave4 = true;
		}
	}

	if (avanzaNave4) {
		if (movNaveX < 0.0f) {
			movNaveX += movNaveOffset * deltaTime;
			//printf("ValorX: %f \n", movNaveX);
		}
		else {
			avanzaNave4 = false;
			rotacionNave = 90.0f;
			avanzaNave = true;
		}
	}

	glm::mat4 model,modelauxNave;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(120.0f + movNaveX, 100.0f, 600.0 + movNaveZ));
	model = glm::scale(model, glm::vec3(18.0f, 18.0f, 18.0f));
	model = glm::rotate(model, rotacionNave * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, -inclinacionNave * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelauxNave = model;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	nave_cabina.RenderModel();


	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, movBaseNave * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	nave_extra.RenderModel();

	model = modelauxNave;

}


void renderPuertaReja() {
	//PUERTA METÁLICA CON MARCO PARA LETRERO, PARA PRACTICA 08
	glm::mat4 model, modelaux;


	model = glm::mat4(1.0);
	modelaux = model;

	model = glm::translate(model, glm::vec3(-3.0f, -0.95f, -815.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(65.0f));	
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	puerta_reja.RenderModel();
	
	model = modelaux;

	//REJA DERECHA (esta es la que rotaba)
	model = glm::translate(model, glm::vec3(-65.5f, 52.6f, 0.0f)); //52.5 en y antes, 65.0 en x
	model = glm::scale(model, glm::vec3(65.0f));
	model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	reja_der.RenderModel();

	model = modelaux;



	//REJA IZQUIERDA
	model = glm::translate(model, glm::vec3(36.5f, 1.0f, 0.0f)); //40 en x antes
	model = glm::scale(model, glm::vec3(65.0f));
	model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	reja_izq.RenderModel();

	model = modelaux;

}


void renderCamellon() {

	glm::mat4 model, modelaux;

	

	model = glm::mat4(1.0);
	modelaux = model;

	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, -337.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, -297.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, -257.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, -217.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, -177.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, -137.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, -97.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, -57.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, -17.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 23.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();


	//Despues de la diana cazadora

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 325.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;
	
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 365.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 405.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();


	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 445.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 485.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 525.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 565.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();

	model = modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 605.0));
	model = glm::scale(model, glm::vec3(6.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	camellon.RenderModel();
}



/*
Código retirado del main que no sé si se va a necesitar en algun momento;


	movCoche = 0.0f;
	movOffset = 0.8f;
	rotllanta = 0.0f;
	rotllantaOffset = 5.0f;
	rotPuertaOffset = 5.0f;
	avanza = true;
	abre = true;
	rotPuerta = 0.5f;

	//DEJO COMENTADO EL INSTANCIAMIENTO DEL AGAVE PARA PRUEBAS DE BLENDING

		////Agave �qu� sucede si lo renderizan antes del coche y el helic�ptero?
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		//model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		////blending: transparencia o traslucidez
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//AgaveTexture.UseTexture();
		////Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[3]->RenderMesh();
		//glDisable(GL_BLEND);

		asaDexter.setPos(letras_dimmsdale.getPos());
		casaDexter.setUniformScale(5.0f);
		casaDexter.renderModel();

			casaDexter.setPos(glm::vec3(- 380.0f, -0.5f, 370.0));
		casaDexter.setUniformScale(40.0f); //Codigo Para pruebas


*/