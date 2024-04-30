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
bool controlDeltaTimeDesborde;
float movHelice;
float giraHeliceOffset;
float rotacionHelicopteroOffset;
float movHelicopteroX, movHelicopteroY, movHelicopteroZ, movHelicopteroOffset;
float inclinacion, rotacionHelicopteroY;
clock_t tiempoInicial;
float tiempoTranscurrido;



//para luces
unsigned int pointLightCount = 0;
unsigned int pointLightCount2 = 0;
unsigned int spotLightCount = 0; //ARREGLO 0 -> TODAS LAS LUCES ENCENDIDAS
unsigned int spotLightCount2 = 0;

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



//Padrinos Magicos
Model bus_padrinos;
Model big_wand;
Model letrero_dimsdale;
Model letras_letrero_dimsdale;

//Laboratorio de Dexter
Model casa_dexter;
Model dexter_body;
Model dexter_leg;
Model dexter_arm;

//Ratatouille
Model vespa;

//Mucha Lucha
Model tienda_donas;


//SKYBOX
Skybox skybox;


//MATERIALES
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;



//DECLARACION DE LAS LUCEs
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
void renderAngelIndependencia();
void renderTimmyBus();
void renderVespa();
void renderHelicoptero();

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
	

	//------------------SONIDO-----------------------
	//Sonido ambiental
	ISoundEngine* Ambiental = createIrrKlangDevice();
	Ambiental->play2D("Sound/Ambiental.wav", true);
	Ambiental->setSoundVolume(0.2f);

	//Pista de fondo
	ISoundEngine* Intro = createIrrKlangDevice();
	Intro->play2D("Sound/Lab_Dexter.wav", true);
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


		//PISO
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


		//INSTANCIAMIENTO DE LOS MODELOS
		//X para ancho del mapa y Z para largo del mapa


		//Modelos Generales del mundo

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


		//Modelos Mucha Lucha

		//ASTRODOMO
		astrodomo.renderModel();

		//Slammin Donuts
		slamminDonuts.renderModel();

		//Modelos - Padrinos Mágicos

		//Big Wand
		bigWand.renderModel();


		//Bus
		renderTimmyBus();

		//Modelos - Ratatouille
		renderVespa();



		//Modelos - Laboratorio de Dexter
		dexter.setUniformModel(uniformModel);
		dexter.setMovimiento(mainWindow.getMovimientoAvatar(), mainWindow.getRotacionAvatar(), mainWindow.getrotBrazoPiernas());
		dexter.renderMainAvatar();

		//Casa de dexter
		casaDexter.renderModel();

		//casa timmy
		CasaTimmy.renderModel();


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
	angel_independencia = Model();
	angel_independencia.LoadModel("Models/Angel.obj");

	angel_independencia_ala = Model();
	angel_independencia_ala.LoadModel("Models/AngelAla.obj");

	BBVA_Pixies = Edificio("Models/BBVA.obj", &uniformModel, glm::vec3(350.0f, -1.0f, 350.0f), glm::vec3(220.0f));
	BBVA_Pixies.setRotY(270.0f);

	estelaDeLuz = Edificio("Models/Estela.obj", &uniformModel, glm::vec3(200.0f, -1.0f, 620.0f), glm::vec3(5.0f));

	helicoptero_base = Model();
	helicoptero_base.LoadModel("Models/Helicoptero_Base.obj");

	helicoptero_helice = Model();
	helicoptero_helice.LoadModel("Models/Helicoptero_Helice.obj");

	//----------Modelos Mucha Lucha---------------------

	astrodomo = Edificio("Models/MuchaLucha/Astrodomo.obj", &uniformModel, glm::vec3(-355.0f, -2.0f, -320.0f), glm::vec3(5.0f));
	astrodomo.setRotY(-270.0f);

	slamminDonuts = Edificio("Models/MuchaLucha/SlamminDonuts.obj", &uniformModel, glm::vec3(-300.0f, -6.0f, -10.0), glm::vec3(1.6f));
	slamminDonuts.setRotY(90.0f);

	//----------Modelos Padrinos Magicos---------------------


	bus_padrinos = Model();
	bus_padrinos.LoadModel("Models/Padrinos/Bus.obj");

	dianaCazadora = Edificio("Models/DianaCupido.obj", &uniformModel, glm::vec3(0.0f, -1.0f, 175.0f), glm::vec3(4.0f, 5.0f, 4.0f));
	dianaCazadora.setRotY(-180.0f);

	bigWand = Edificio("Models/Padrinos/BigWand.obj", &uniformModel, glm::vec3(-180.0f, -2.0f, 245.0), glm::vec3(17.0f));
	bigWand.setRotY(90.0f);

	CasaTimmy = Edificio("Models/Padrinos/TimmyH_Tex2.obj", &uniformModel, glm::vec3(-350.0f, 0.0f, 340.0), glm::vec3(30.0f));
	CasaTimmy.setRotY(90.0f);


	//----------Modelos Lab. de Dexter---------------------

	casaDexter = Edificio("Models/DextersLab/CasaDexter.obj", &uniformModel, glm::vec3(370.0f, -2.0f, -40.0), glm::vec3(40.0f));
	casaDexter.setRotY(270.0f);

	//AVATAR (DEXTER)

	dexter = MainAvatar(glm::vec3(250.0f, 0.5f, 350.0f), 15.0f, glm::vec3(3.0f, 3.0f, 3.0f));


	//----------Modelos Ratatouille---------------------
	vespa = Model();
	vespa.LoadModel("Models/Ratatouille/vespa.obj");



	//LUMINARIA PARA REPORTE 08

	luminariaP8 = Lampara("Models/luminaria_text.obj", &uniformModel, glm::vec3(-90.0f, -0.95f, -100.0f), glm::vec3(4.0f));

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




void renderVespa() {

	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-35.0f, -0.5f, -300.0));
	model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
	//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	vespa.RenderModel();

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
		camera.setPosicionX(350.0f + movHelicopteroX);
		camera.setPosicionY(702.0f + movHelicopteroY);
		camera.setPosicionZ(285.0 + movHelicopteroZ);

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
	model = glm::translate(model, glm::vec3(-35.0f, -0.5f, -380.0));
	model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	bus_padrinos.RenderModel();

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


*/