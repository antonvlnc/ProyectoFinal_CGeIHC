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

//para iluminaci n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "controladorLuces.h"

//Para sonido
#include <irrklang.h>
using namespace irrklang;

//VARIABLES Y CONSTANTES
const float toRadians = 3.14159265f / 180.0f;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

//Para animaci n
bool alaIzq;
bool alaDer;
bool controlDeltaTimeDesborde0;
float giraAlaIzq;
float giraAlaDer;
float anguloAlaIzq;
float anguloAlaDer;
float giraAlaOffset;
float movAlaOffset;
float giraRotonda;
float giraRotondaOffset;

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
bool  flagBus0, flagBus1, flagBus2, flagBus3, flagBus4, flagBus5, flagBus6, flagBus7, flagBus8, flagBus9, flagBus10, flagBus11, flagBus12, flagBus13;
float rotacionAutomaticaRuedaZ, rotacionAutomaticaRuedaOffSet;
float metrobusX, metrobusY, metrobusZ;
float traslacionMetrobusOffSet;
float tiempoTranscurrido;
float radioCircunferencia;
float auxiliarDesbordamiento;
float diferenciaParaCalcularOrigen;
float valorUnitario;
float preview;
float giroDeMB;
float giroDeMBOffSet;
//Animacion AE86
float movAE86;
float giraAE86Offset;
float giraAE86LlantaOffset;
float movAE86Llantas;

//Animacion Letras
float rotacionLetras;
float rotacionLetrasOffset;
bool giraLetras;

//Animacion planta
bool MueveCabeza;
float anguloCabeza;
float giraCabeza;
float movCabezaOffset;
float giraCabezaOffset;
bool MueveMandibula;
float anguloMandibula;
float giraMandibula;
float movMandibulaOffset;
float giraMandibulaOffset;

//Animacion bus
bool mueveBus;
float busZ;
float busOffset;

//para luces
// luz direccional
DirectionalLight mainLight;
//Objeto para el manejo de todas las luces del escenario
controladorLuces lightControl;

GLfloat duracionCicloDiayNoche = 15.0;	//cantidad de segundos que va a durar el ciclo de dia/noche.
GLboolean esDeDia = false;				//Variable para controlar eventos ligados al ciclo de dia y de noche




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

Camera* currentCamera;
Camera camaraAvatar;
Camera camaraLibre;
Camera camaraAerea;
//Para ajustar la camara del avatar
glm::vec4 camoffset(0.0f, 15.0f, -55.0f, 1.0f);
glm::mat4 camRot(1.0);
glm::vec3 camPos(0.0f);



//Declcaración de texturas

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture reforma_layout; //piso
Texture reforma_layout_baked; //piso
Texture AstrodomoTexture;
Texture grass;


//DECLARACION DE MODELOS


//Dexter
MainAvatar dexter;
Edificio casaDexter;

Model nave_cabina;
Model nave_extra;
Model prueba;




//GENERAL
Model luminaria;
Model angel_independencia;
Model angel_independencia_ala;
Model bbva;

Model helicoptero_base;
Model helicoptero_helice;
Model camellon;
Model metrobus;
Model metrobus_llanta_izq;
Model metrobus_llanta_der;
Model puerta_reja;
Model reja_izq;
Model reja_der;
Model traffic_light;

Model brick_wall;
Model brick_wall_corner;


Model banqueta;
Model reflector;
Model banqueta_luz;
Model banqueta_esquina;
Model street_lamp;

Edificio dianaCazadora;
Edificio BBVA_Pixies;
Edificio estelaDeLuz;
Model banqueta_trunca;
Model AE86;
Model AE86_Llanta;
Model AE86_LlantaI;
Model jacaranda;


Lampara luminariaP8;

Model RoadBlock;
Model BusStop;


//Padrinos Magicos
Model bus_padrinos;

Model big_wand;
Model letrero_dimsdale;
Model letras_letrero_dimsdale;
Edificio dimmadome;

Model taxi;


Edificio letras_dimmsdale;
Edificio letrero_dimmsdale;

Edificio bigWand;
Edificio CasaTimmy;

Edificio letrero_dimmsdale_baked;
Model doidle;




//Ratatouille
Model vespa;

Edificio gusteaus;
Edificio gusteau_sign;
Edificio gusteaus_extra;
Edificio eiffel;
Model trashcan;
Model banca;
Edificio fountain;



//Mucha Lucha
Model laPulga;

Edificio astrodomo;
Edificio slamminDonuts;

Model tienda_donas;
Model laPulgaInferior;
Model laPulgaSuperior;
Model tokyo_tree;
Edificio academy;
Edificio poster1;
Edificio poster2;
Model cactus;
Edificio ring;
Model perro_ricochet;
Model fish;
Model mutant_plant;
Model mutant_tallo;
Model mutant_Sup;
Model mutant_Inf;
Model Astrodomo;
Model AstrodomoLetras;



//SKYBOX
Skybox skybox;	//Default
Skybox currentSkybox; //Skybox que se renderiza
Skybox dia;
Skybox noche;
Skybox amanecer;
Skybox atardecer;

//MATERIALES
Material Material_brillante;
Material Material_opaco;



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
void InitializeSkyboxes();
void InitializeLights();
void InitializeCameras();

void selectSkybox(int skyboxNumber);
void setCamera(GLint cameraNumber);

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
//void renderEstela(); //prueba para textura con iluminacion cocinada

void renderBanquetasGenerales();	//Las que no cambiarán

void renderBanquetaNormal();		//Las que cambiarán en el día
void renderBanquetaBaked();			//Las que cambiarán de noche

void renderReflector();

void renderBrickWall();

void renderLuminarias();

void renderPerroRicochet();

void renderFishyFish();

void renderMutantPlant();

void renderCactus();

void renderDoidle();

//void renderAE86();

void renderLetrasAstrodomo();
void renderBancas();

void renderTrashcan();

void renderJacarandas();

void renderTokyoTree();

void renderRoadBlock();

void renderBusStop();

void renderPrueba();

void renderTrafficLight();


int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	InitializeModels();
	InitializeTextures();
	InitializeLights();
	InitializeSkyboxes();
	InitializeCameras();

	//camera = Camera(glm::vec3(0.0f, 100.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.5f, 0.5f);


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
	controlDeltaTimeDesborde0 = true;
	giraAlaIzq = 0.0f;
	giraAlaDer = 0.0f;
	anguloAlaIzq = 90.0f;
	anguloAlaDer = 90.0f;
	giraAlaOffset = 1.0f;
	movAlaOffset = 1.0f;
	giraRotonda = 0.0f; 
	giraRotondaOffset = 0.5f;

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

	//Animacion AE86
	movAE86 = 0.0f;
	giraAE86Offset = 1.5f;
	giraAE86LlantaOffset = 5.0f;
	movAE86Llantas = 0.0f;

	//Animacion Letras Astrodomo
	rotacionLetras = 0.0f;
	rotacionLetrasOffset = 0.5;
	giraLetras = true;

	//Animacion planta
	MueveCabeza = true;
	anguloCabeza = 0.0f;
	giraCabeza = 0.0f;
	movCabezaOffset = 1.0f;
	giraCabezaOffset = 1.0;
	MueveMandibula = true;
	anguloMandibula = 0.0f;
	giraMandibula = 0.0f ;
	movMandibulaOffset = 3.0;
	giraMandibulaOffset = 3.0;

	//Animacion Bus
	mueveBus = true;
	busZ = 0.0f;
	busOffset = 1.0f;

	//Animacion metrobus //------------------SONIDO-----------------------//------------------SONIDO-----------------------//------------------SONIDO-----------------------//------------------SONIDO-----------------------//------------------SONIDO-----------------------//------------------SONIDO-----------------------//------------------SONIDO-----------------------//------------------SONIDO-----------------------
	flagBus0 = true;
	flagBus4 = true;
	flagBus1 = flagBus2 = flagBus3 = flagBus5 = flagBus6 = flagBus7 = flagBus8 = flagBus9 = flagBus10 = flagBus11 = flagBus12 = flagBus13 = false;
	rotacionAutomaticaRuedaZ = 0.0f;
	rotacionAutomaticaRuedaOffSet = 3.0f;
	traslacionMetrobusOffSet = 0.5f;
	metrobusX = metrobusY = 0.0f;
	metrobusZ = -350.0f;
	controlDeltaTimeDesborde2 = true;
	radioCircunferencia = 0.0f;
	valorUnitario = 1.0f;
	preview = 0.0f;
	giroDeMB = 0.0f;
	giroDeMBOffSet = 0.0f;
	//------------------SONIDO-----------------------
	////Ambiental
	//ISoundEngine* Ambiental = createIrrKlangDevice();
	//Ambiental->play2D("Sound/Ambiental.wav", true);
	//Ambiental->setSoundVolume(0.8f);

	//////Pista de fondo
	//ISoundEngine* Intro = createIrrKlangDevice();
	//Intro->play2D("Sound/Dexter_Pista.wav", true); //cambiar a cancion en loop sin la voz
	//Intro->setSoundVolume(0.1f);

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

		//Luz Direccional, seleccion de skybox
		esDeDia = lightControl.recalculateDirectionalLight(deltaTime);
		lightControl.setSkyboxNumber();
		selectSkybox(lightControl.getSkyboxNumber());


		//Recibir eventos del usuario
		glfwPollEvents();
		/*camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());*/

		setCamera(mainWindow.getTipoCamara());
		/*camRot = glm::rotate(camRot, glm::radians(mainWindow.getRotacionAvatar()), glm::vec3(0.0f, 1.0f, 0.0f));
		camPos = dexter.getPos() + glm::vec3(camRot * camoffset);
		camaraAvatar.mouseControl( mainWindow.getRotacionAvatar(), 0.0f);
		camaraAvatar.setPosicionX(camPos.x);
		camaraAvatar.setPosicionY(camPos.y);
		camaraAvatar.setPosicionZ(camPos.z);*/
		//-------------------------------------------------------------------------

		/*model = glm::mat4(1.0);
		dexRotPos = glm::vec4(dexter.getPos(), 1.0);

		model = glm::rotate(model, glm::radians(dexter.getRotY()), glm::vec3(0.0f, 1.0f, 0.0f));

		dexRotPos = model * dexRotPos;*/

		//

		//-------------------------------------------------------------------------

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		currentSkybox.DrawSkybox((*currentCamera).calculateViewMatrix(), projection);
		shaderList[0].UseShader();

		//---------INICIACILIZACION DE VARIABLES UNIFORM-------------
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//informaci n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr((*currentCamera).calculateViewMatrix()));
		glUniform3f(uniformEyePosition, (*currentCamera).getCameraPosition().x, (*currentCamera).getCameraPosition().y, (*currentCamera).getCameraPosition().z);

		//----------------LUCES-----------


		lightControl.chooseSpotLightsArray(esDeDia);
		lightControl.choosePointLightsArray(mainWindow.getLuzActivable());

		//informaci n al shader de fuentes de iluminaci n
		shaderList[0].SetDirectionalLight(&mainLight); //referencia a la mainlight del objeto light control;
		shaderList[0].SetPointLights(lightControl.getPointlightArray(), lightControl.getPointlightCount());
		shaderList[0].SetSpotLights(lightControl.getSpotlightArray(), lightControl.getSpotLightCount());


		//-------------------------PISO-----------------------------
		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(450.0f, 1.0f, 700.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		//reforma_layout.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);


		////RENDERIZAMOS EL PISO
		//meshList[2]->RenderMesh();

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
		/*renderEstela();*/

		//angel de la independencia
		renderAngelIndependencia();


		//camellon por piezas
		renderCamellon();

		//Metrobus
		renderMetrobus();

		//banqueta normal

		
		renderBanquetasGenerales();


		renderBrickWall();

		/*renderPrueba();*/ //Modelo de Rodrigo que me obligó a hacer
		

		renderTrafficLight();


		if (esDeDia) {
			renderBanquetaNormal();

			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(450.0f, 1.0f, 700.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));

			reforma_layout.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);


			//RENDERIZAMOS EL PISO
			meshList[2]->RenderMesh();
		}
		else {
			renderBanquetaBaked();

			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(450.0f, 1.0f, 700.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));

			reforma_layout_baked.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);


			//RENDERIZAMOS EL PISO
			meshList[2]->RenderMesh();
		}

		//Banqueta con luz cocinada


		//reflector
		renderReflector();

		renderLuminarias();

		//Jacarandas
		renderJacarandas();

		//Road Block}
		renderRoadBlock();

		//BusStop
		renderBusStop();


		//Puerta con reja
		renderPuertaReja();

		
		//-------------Modelos Mucha Lucha------------------

		//ASTRODOMO
		renderLetrasAstrodomo();

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
		renderCactus();

		//Ring
		ring.renderModel();

		//Perro de Ricochet
		renderPerroRicochet();

		//Fishy Fish
		renderFishyFish();

		//Mutant Plant
		renderMutantPlant();

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
		if (esDeDia) {
			letrero_dimmsdale.renderModel();
		}
		else
		{
			letrero_dimmsdale_baked.renderModel();
		}
		
		

		//Doidle
		renderDoidle();


		//------------------Modelos - Ratatouille------------

		//Vespa
		renderVespa();

		//Restaurante Gusteau
		gusteaus.renderModel();

		//Gusteau Sign
		gusteau_sign.renderModel();

		//más artículos de Gusteau's
		gusteaus_extra.renderModel();

		//Banca
		renderBancas();

		//Bote de basura
		renderTrashcan();

		//Torre Eiffel
		eiffel.renderModel();

		//fuente
		fountain.renderModel();

		//-------------------Modelos - Laboratorio de Dexter---------------------
		dexter.setUniformModel(uniformModel);
		dexter.setMovimiento(mainWindow.getMovimientoAvatar(), mainWindow.getRotacionAvatar(), mainWindow.getBanderaCaminata(), deltaTime);
		dexter.renderMainAvatar();


		//Casa de dexter
		casaDexter.renderModel();


		//tokyo tree
		renderTokyoTree();

		//nave dexter
		renderNaveDexter();


		//MODELO DE LUMINARIA PARA REPORTE 08
		//luminariaP8.renderModel();

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
		-1.0f, 0.0f, -1.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f, //0
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

//Funciones de inicializacion
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
	estelaDeLuz = Edificio("Models/Estela.obj", &uniformModel, glm::vec3(245.0f, -1.0f, 740.0f), glm::vec3(5.0f));
	/*estela_de_luz = Model();
	estela_de_luz.LoadModel("Models/Estela.obj");*/

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

	traffic_light = Model();
	traffic_light.LoadModel("Models/TrafficLight.obj");


	//LUMINARIA PARA REPORTE 08

	luminariaP8 = Lampara("Models/luminaria_text.obj", &uniformModel, glm::vec3(-90.0f, -0.95f, -100.0f), glm::vec3(4.0f));

	//Puerta con reja
	puerta_reja = Model();
	puerta_reja.LoadModel("Models/PuertaReja.obj");

	reja_der = Model();
	reja_der.LoadModel("Models/RejaDer.obj");

	reja_izq = Model();
	reja_izq.LoadModel("Models/RejaIzq.obj");

	//barda de ladrillo

	brick_wall = Model();
	brick_wall.LoadModel("Models/BrickWall.obj");

	brick_wall_corner = Model();
	brick_wall_corner.LoadModel("Models/BrickWallCorner.obj");

	//Banqueta normal
	banqueta = Model();
	banqueta.LoadModel("Models/Banqueta.obj");


	//Banqueta esquina
	banqueta_esquina = Model();
	banqueta_esquina.LoadModel("Models/BanquetaEsquina.obj");

	//Banqueta trunca
	banqueta_trunca = Model();
	banqueta_trunca.LoadModel("Models/BanquetaTrunca.obj");

	//Banqueta con luz cocinada
	banqueta_luz = Model();
	banqueta_luz.LoadModel("Models/BanquetaLuz.obj");

	//reflector
	reflector = Model();
	reflector.LoadModel("Models/Reflector.obj");


	//LUMINARIA
	street_lamp = Model();
	street_lamp.LoadModel("Models/StreetLamp.obj");

	//AE86
	AE86 = Model();
	AE86.LoadModel("Models/AE86.obj");
	
	//Árbol de jacarandas
	jacaranda = Model();
	jacaranda.LoadModel("Models/Jacaranda.obj");

	//Road Block
	RoadBlock = Model();
	RoadBlock.LoadModel("Models/RoadBlock.obj");

	//BusStop
	BusStop = Model();
	BusStop.LoadModel("Models/BusStop.obj");


	//AE86_Neumatico
	AE86_Llanta = Model();
	AE86_Llanta.LoadModel("Models/Llanta_AE86.obj");

	//AE86_Neumatico
	AE86_LlantaI = Model();
	AE86_LlantaI.LoadModel("Models/Llanta_AE86I.obj");


	//----------Modelos Mucha Lucha---------------------

	Astrodomo = Model();
	Astrodomo.LoadModel("Models/MuchaLucha/Astrodomo.obj");

	AstrodomoLetras = Model();
	AstrodomoLetras.LoadModel("Models/MuchaLucha/AstrodomoLetras.obj");


	slamminDonuts = Edificio("Models/MuchaLucha/SlamminDonuts.obj", &uniformModel, glm::vec3(-275.0f, 0.5f, -580.0), glm::vec3(1.6f));
	slamminDonuts.setRotY(90.0f);

	laPulgaInferior = Model();
	laPulgaInferior.LoadModel("Models/MuchaLucha/LaPulga_Inferior.obj");


	laPulgaSuperior = Model();
	laPulgaSuperior.LoadModel("Models/MuchaLucha/LaPulga_Superior.obj");

	tokyo_tree = Model();
	tokyo_tree.LoadModel("Models/MuchaLucha/TokyoTree.obj");

	academy = Edificio("Models/MuchaLucha/Academy.obj", &uniformModel, glm::vec3(-320.0f, 0.0f, -360.0), glm::vec3(12.0f));
	academy.setRotY(90.0f);

	poster1 = Edificio("Models/MuchaLucha/Poster1.obj", &uniformModel, glm::vec3(-246.0f, 100.0f, -290.0), glm::vec3(12.0f));
	poster1.setRotY(90.0f);

	poster2 = Edificio("Models/MuchaLucha/Poster2.obj", &uniformModel, glm::vec3(-246.0f, 100.0f, -430.0), glm::vec3(12.0f));
	poster2.setRotY(90.0f);

	cactus = Model();
	cactus.LoadModel("Models/MuchaLucha/Cactus.obj");

	ring = Edificio("Models/MuchaLucha/Ring.obj", &uniformModel, glm::vec3(220.0f, 1.0f, -30.0), glm::vec3(40.0f));
	ring.setRotY(270.0f);

	perro_ricochet = Model();
	perro_ricochet.LoadModel("Models/MuchaLucha/PerroRicochet.obj");

	fish = Model();
	fish.LoadModel("Models/MuchaLucha/FishyFish.obj");


	//----------Modelos Padrinos Magicos---------------------


	bus_padrinos = Model();
	bus_padrinos.LoadModel("Models/Padrinos/Bus.obj");

	dianaCazadora = Edificio("Models/DianaCupido.obj", &uniformModel, glm::vec3(0.0f, -1.0f, 175.0f), glm::vec3(3.5f, 4.5f, 3.5f));
	dianaCazadora.setRotY(-180.0f);

	bigWand = Edificio("Models/Padrinos/BigWand.obj", &uniformModel, glm::vec3(-190.0f, -0.5f, 265.0), glm::vec3(20.0f));
	bigWand.setRotY(90.0f);

	CasaTimmy = Edificio("Models/Padrinos/TimmyH_Tex2.obj", &uniformModel, glm::vec3(370.0f, 1.0f, 600.0), glm::vec3(34.0f));
	CasaTimmy.setRotY(270.0f);

	dimmadome = Edificio("Models/Padrinos/Dimmadome.obj", &uniformModel, glm::vec3(310.0f, 1.0f, -300.0), glm::vec3(18.0f));
	dimmadome.setRotY(270.0f);

	taxi = Model();
	taxi.LoadModel("Models/Padrinos/Taxi.obj");

	letras_dimmsdale = Edificio("Models/Padrinos/Dimmsdale.obj", &uniformModel, glm::vec3(0.0f, 0.0f, 995.0), glm::vec3(75.0f));
	letras_dimmsdale.setRotY(180.0f);

	letrero_dimmsdale = Edificio("Models/Padrinos/DimsdaleSign.obj", &uniformModel, glm::vec3(230.0f, 1.0f, -620.0), glm::vec3(1.9f));
	letrero_dimmsdale.setRotY(180.0f);

	letrero_dimmsdale_baked = Edificio("Models/Padrinos/DimsdaleSignBaked.obj", &uniformModel, glm::vec3(230.0f, 1.0f, -620.0), glm::vec3(1.9f));
	//letrero_dimmsdale_baked.setRotY(180.0f);

	doidle = Model();
	doidle.LoadModel("Models/Padrinos/Doidle.obj");




	//----------Modelos Lab. de Dexter---------------------

	casaDexter = Edificio("Models/DextersLab/CasaDexter.obj", &uniformModel, glm::vec3(-380.0f, -0.5f, 310.0), glm::vec3(40.0f));
	casaDexter.setRotY(90.0f);

	nave_cabina = Model();
	nave_cabina.LoadModel("Models/DextersLab/NaveDomo.obj");

	nave_extra = Model();
	nave_extra.LoadModel("Models/DextersLab/NaveCierra.obj");

	mutant_plant = Model();
	mutant_plant.LoadModel("Models/DextersLab/MutantPlant.obj");

	mutant_tallo = Model();
	mutant_tallo.LoadModel("Models/DextersLab/Tallo_Prueba.obj");

	mutant_Sup = Model();
	mutant_Sup.LoadModel("Models/DextersLab/Mand_Sup_Prueba.obj");

	mutant_Inf = Model();
	mutant_Inf.LoadModel("Models/DextersLab/Mand_Inf_Prueba.obj");

	//AVATAR (DEXTER)

	dexter = MainAvatar(glm::vec3(0.0f, 0.5f, -650.0f), 0.0f, glm::vec3(3.0f, 3.0f, 3.0f), 0.3); //dexter = MainAvatar(glm::vec3(0.0f, 0.5f, -650.0f), 15.0f, glm::vec3(3.0f, 3.0f, 3.0f));


	//-------------------------Modelos Ratatouille-----------------------------------------

	//moto del chef chaparro
	vespa = Model();
	vespa.LoadModel("Models/Ratatouille/vespa.obj");

	//Gusteau's

	gusteaus = Edificio("Models/Ratatouille/gusteaus.obj", &uniformModel, glm::vec3(-390.0f, -6.0f, 575.0), glm::vec3(30.0f));
	//gusteaus.setRotY(90.0f);

	//Objetos extra Gusteau's
	gusteaus_extra = Edificio("Models/Ratatouille/gusteaus_extra.obj", &uniformModel, glm::vec3(-350.0f, 2.0f, 575.0), glm::vec3(15.0f));
	gusteaus_extra.setRotY(90.0f);


	//Anuncio Gusteau's

	gusteau_sign = Edificio("Models/Ratatouille/GusteauSign.obj", &uniformModel, glm::vec3(-357.0f, 145.0f, 575.0), glm::vec3(35.0f));
	gusteau_sign.setRotY(90.0f);

	//Torre Eiffel

	eiffel = Edificio("Models/Ratatouille/eiffel.obj", &uniformModel, glm::vec3(-357.0f, 0.0f, 720.0), glm::vec3(2.0f));
	eiffel.setRotY(90.0f);

	trashcan = Model();
	trashcan.LoadModel("Models/Ratatouille/trashcan.obj");

	banca = Model();
	banca.LoadModel("Models/Ratatouille/banca.obj");

	fountain = Edificio("Models/Ratatouille/fountain.obj", &uniformModel, glm::vec3(-210.0f, 0.0f, 575.0), glm::vec3(25.0f));
	fountain.setRotY(90.0f);








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

	reforma_layout = Texture("Textures/reforma_layout.png"); //piso normal
	reforma_layout.LoadTextureA();

	reforma_layout_baked = Texture("Textures/reforma_layout_baked.png"); //piso para la noche (luces cocinadas)
	reforma_layout_baked.LoadTextureA();

	grass = Texture("Textures/grass.png");
	grass.LoadTextureA();


	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

}

void InitializeSkyboxes() {

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/sky-right.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-left.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-down.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-up.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-front.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-back.jpg");

	skybox = Skybox(skyboxFaces);

	//Dia caricatura
	std::vector<std::string> skyboxFaces2;
	skyboxFaces2.push_back("Textures/CartoonSkybox/Day/Right.2048x2048.png");
	skyboxFaces2.push_back("Textures/CartoonSkybox/Day/Left.2048x2048.png");
	skyboxFaces2.push_back("Textures/CartoonSkybox/Day/Down.2048x2048.png");
	skyboxFaces2.push_back("Textures/CartoonSkybox/Day/Up.2048x2048.png");
	skyboxFaces2.push_back("Textures/CartoonSkybox/Day/Front.2048x2048.png");
	skyboxFaces2.push_back("Textures/CartoonSkybox/Day/BAck.2048x2048.png");

	dia = Skybox(skyboxFaces2);

	std::vector<std::string> skyboxFaces3;
	skyboxFaces3.push_back("Textures/CartoonSkybox/Day6/Right.2048x2048.png");
	skyboxFaces3.push_back("Textures/CartoonSkybox/Day6/Left.2048x2048.png");
	skyboxFaces3.push_back("Textures/CartoonSkybox/Day6/Down.2048x2048.png");
	skyboxFaces3.push_back("Textures/CartoonSkybox/Day6/Up.2048x2048.png");
	skyboxFaces3.push_back("Textures/CartoonSkybox/Day6/Front.2048x2048.png");
	skyboxFaces3.push_back("Textures/CartoonSkybox/Day6/BAck.2048x2048.png");

	noche = Skybox(skyboxFaces3);

	std::vector<std::string> skyboxFaces4;
	skyboxFaces4.push_back("Textures/CartoonSkybox/Day8/Right.2048x2048.png");
	skyboxFaces4.push_back("Textures/CartoonSkybox/Day8/Left.2048x2048.png");
	skyboxFaces4.push_back("Textures/CartoonSkybox/Day8/Down.2048x2048.png");
	skyboxFaces4.push_back("Textures/CartoonSkybox/Day8/Up.2048x2048.png");
	skyboxFaces4.push_back("Textures/CartoonSkybox/Day8/Front.2048x2048.png");
	skyboxFaces4.push_back("Textures/CartoonSkybox/Day8/BAck.2048x2048.png");

	amanecer = Skybox(skyboxFaces4);

	std::vector<std::string> skyboxFaces5;
	skyboxFaces5.push_back("Textures/CartoonSkybox/Day9/Right.2048x2048.png");
	skyboxFaces5.push_back("Textures/CartoonSkybox/Day9/Left.2048x2048.png");
	skyboxFaces5.push_back("Textures/CartoonSkybox/Day9/Down.2048x2048.png");
	skyboxFaces5.push_back("Textures/CartoonSkybox/Day9/Up.2048x2048.png");
	skyboxFaces5.push_back("Textures/CartoonSkybox/Day9/Front.2048x2048.png");
	skyboxFaces5.push_back("Textures/CartoonSkybox/Day9/BAck.2048x2048.png");

	atardecer = Skybox(skyboxFaces5);



	currentSkybox = noche;

}

void InitializeLights() {
	//APARTADO DE LUCES
	//luz direccional, s lo 1 y siempre debe de existir

	//contador de luces puntuales
	lightControl = controladorLuces(duracionCicloDiayNoche, limitFPS, esDeDia, &mainLight);
	lightControl.initializeSpotlights(dianaCazadora.getPos(), glm::vec3(5.0f, -1.0f, -530.0), ring.getPos());
	lightControl.initializePointlights(letras_dimmsdale.getPos(), estelaDeLuz.getPos(), bigWand.getPos());

}

void InitializeCameras() {
	
	camRot = glm::rotate(camRot, glm::radians(dexter.getRotY()), glm::vec3(0.0f ,1.0f, 0.0f));

	camPos = dexter.getPos() + glm::vec3(camRot * camoffset);

	camaraAvatar = Camera( camPos , glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 1.0f, -1.0f); //
	camaraAerea = Camera(glm::vec3(0.0f, 400.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -90.0f, 5.5f, 0.5f);
	camaraLibre = Camera(glm::vec3(0.0f, 200.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 90.0f, 5.5f, 0.5f);


	currentCamera = &camaraLibre;
}

//Otros 
void selectSkybox(int skyboxNumber) {
	//Asigna el skybox que se va a renderizar a current.

	switch (skyboxNumber) {
	case 1:
		currentSkybox = amanecer;
		break;
	case 2:
		currentSkybox = dia;
		break;
	case 3:
		currentSkybox = atardecer;
		break;
	case 4:
		currentSkybox = noche;
		break;
	default:
		currentSkybox = skybox;
		break;
	}


}

void setCamera(GLint cameraNumber) {
	//Camara 1 camara del avatar, camara 2 camara aerea, camara 3 camara libre

	//Calculo de la rotacion del avatar
	camRot = glm::rotate(camRot, glm::radians(mainWindow.getRotacionAvatar() * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
	camPos = dexter.getPos() + glm::vec3(camRot * camoffset);
	camaraAvatar.mouseControl(mainWindow.getRotacionAvatar() * deltaTime, 0.0f);
	switch (cameraNumber)
	{
	case 1:
		
		camaraAvatar.setPosicionX(camPos.x);
		camaraAvatar.setPosicionY(camPos.y);
		camaraAvatar.setPosicionZ(camPos.z);
		currentCamera = &camaraAvatar;
		break;
	case 2:
		camaraAerea.keyControlAerea(mainWindow.getsKeys(), deltaTime);
		//camaraAerea.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		currentCamera = &camaraAerea;
		break;
	case 3:
		camaraLibre.keyControl(mainWindow.getsKeys(), deltaTime);
		camaraLibre.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		currentCamera = &camaraLibre;
		break;
	default:
		camaraLibre.keyControl(mainWindow.getsKeys(), deltaTime);
		camaraLibre.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		currentCamera = &camaraLibre;
		break;
	}
}

//------------------------------------Funciones para renderizado--------------------------------
void renderAngelIndependencia() {

	movAE86Llantas += giraAE86LlantaOffset * deltaTime;

	giraRotonda -= giraRotondaOffset * deltaTime;

	if (alaIzq)
	{
		if (anguloAlaIzq >= 0.0f)
		{
			anguloAlaIzq -= movAlaOffset * deltaTime;
			giraAlaIzq += giraAlaOffset * deltaTime;
			anguloAlaDer -= movAlaOffset * deltaTime;
			giraAlaDer -= giraAlaOffset * deltaTime;

			if (controlDeltaTimeDesborde0) {
				anguloAlaIzq = 90.0f;
				anguloAlaDer = 90.0f;
				controlDeltaTimeDesborde = false;
			}
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
	glm::mat4 model, modelaux2, modelauxAE86;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(5.0f, -1.0f, -530.0));
	model = glm::scale(model, glm::vec3(7.0f, 8.0f, 7.0f));
	model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelaux2 = model;
	angel_independencia.RenderModel();

	model = glm::translate(model, glm::vec3(0.0f, 28.5f, -0.5f));
	model = glm::rotate(model, -70 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, giraAlaIzq * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	//Ala del angel 1
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	angel_independencia_ala.RenderModel();


	model = modelaux2;

	model = glm::translate(model, glm::vec3(0.0f, 28.5f, -0.5f));
	model = glm::rotate(model, 70 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, giraAlaDer * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	//Ala del angel 2
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	angel_independencia_ala.RenderModel();

	model = modelaux2;

	//AE86
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, giraRotonda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	model = glm::translate(model, glm::vec3(12.0f, 0.6f, 12.0));
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	model = glm::rotate(model, -190 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelauxAE86 = model;
	AE86.RenderModel();

	model = glm::translate(model, glm::vec3(-0.25f, -0.15f, 0.6f));
	model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, movAE86Llantas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	AE86_Llanta.RenderModel();

	model = modelauxAE86;

	model = glm::translate(model, glm::vec3(-0.25f, -0.15f, -0.65f));
	model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, movAE86Llantas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	AE86_LlantaI.RenderModel();

	model = modelauxAE86;

	model = glm::translate(model, glm::vec3(-2.37f, -0.15f, 0.6f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, movAE86Llantas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	AE86_Llanta.RenderModel();

	model = modelauxAE86;

	model = glm::translate(model, glm::vec3(-2.37f, -0.15f, -0.65f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, movAE86Llantas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	AE86_LlantaI.RenderModel();

}



//void renderEstela() {
//	glm::mat4 model, modelaux;
//
//	model = glm::mat4(1.0);
//
//	model = glm::translate(model, glm::vec3(315.0f, -1.0f, 805.0f));
//	modelaux = model;
//	model = glm::scale(model, glm::vec3(5.0f));
//	/*model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
//	//material brillante
//	//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess); //esto afecta a todo el mundo
//	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//	estela_de_luz.RenderModel();
//
//	model = modelaux;
//}


void renderVespa() {

	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-280.0f, -0.5f, 660.0));
	model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	vespa.RenderModel();

}

void renderBanquetasGenerales() {

	//26 para largo es lo óptimo

	//para derecha arriba
	/*model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));*/

	//para derecha abajo
	/*model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));*/

	//son solo las truncas?
	glm::mat4 model, modelaux;


	//-----------------------Lado Izquierdo-----------------------------


	//abajo izquierda
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(105.0f, -1.0f, -394.0f)); //--110 en x
	model = glm::scale(model, glm::vec3(43.5f, 16.0f, 26.0f)); //35 original
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta_trunca.RenderModel();

	//enmedio arriba izquierda
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(105.0f, -1.0f, 252.0f)); //--110 en x
	model = glm::scale(model, glm::vec3(43.5f, 16.0f, 42.0f)); //35 original
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta_trunca.RenderModel();


	//RECTA antes de enmedio abajo izquierda
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(105.0f, 2.2f, -68.0f)); //--110 en x
	model = glm::scale(model, glm::vec3(43.5f, 16.0f, 130.0f)); //35 original
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta.RenderModel();



	//enmedio abajo izquierda
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(105.0f, 2.2f, 85.0f)); //--110 en x
	model = glm::scale(model, glm::vec3(43.5f, 16.0f, 26.0f)); //35 original
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta_trunca.RenderModel();

	//RECTA FINAL izquierda
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(105.0f, 2.2f, 585.0f)); //--110 en x
	model = glm::scale(model, glm::vec3(43.5f, 16.0f, 125.0f)); //35 original
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta.RenderModel();


	//----------------------------------Lado derecho------------------------------------------------

	// abajo derecha
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-110.0f, 2.0f, -394.0f)); //--110 en x
	model = glm::scale(model, glm::vec3(38.5f, 16.0f, 26.0f)); //35 original
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	//model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta_trunca.RenderModel();

#	//RECTA entre abajo derecha y el que cambia
	model = glm::mat4(1.0);
	modelaux = model;
	model = glm::translate(model, glm::vec3(-110.0f, -1.0f, -276.0f));
	model = glm::scale(model, glm::vec3(38.5f, 16.0f, 95.0f)); //35 original, 75 a lo largo original
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta.RenderModel();


	//RECTA entre la que cambia y enmedio abajo derecha
	model = glm::mat4(1.0);
	modelaux = model;
	model = glm::translate(model, glm::vec3(-110.0f, -1.0f, 24.0f));
	model = glm::scale(model, glm::vec3(38.5f, 16.0f, 40.0f)); //35 original, 75 a lo largo original
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta.RenderModel();


	//enmedio abajo derecha
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-110.0f, -1.0f, 90.0f)); //--110 en x
	model = glm::scale(model, glm::vec3(38.5f, 16.0f, 26.0f)); //35 original
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta_trunca.RenderModel();



	//enmedio arriba derecha
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-110.0f, 2.5f, 249.0f)); //--110 en x
	model = glm::scale(model, glm::vec3(38.5f, 16.0f, 30.0f)); //35 original
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	//model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta_trunca.RenderModel();


	//RECTA entre arriba derecha y el que cambia
	model = glm::mat4(1.0);
	modelaux = model;
	model = glm::translate(model, glm::vec3(-110.0f, -1.0f, 386.0f));
	model = glm::scale(model, glm::vec3(38.5f, 16.0f, 110.0f)); //35 original, 75 a lo largo original
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta.RenderModel();

	//RECTA entre el que cambia y final (corto)
	model = glm::mat4(1.0);
	modelaux = model;
	model = glm::translate(model, glm::vec3(-110.0f, -1.0f, 685.0f));
	model = glm::scale(model, glm::vec3(38.5f, 16.0f, 25.0f)); //35 original, 75 a lo largo original
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta.RenderModel();

}

void renderBanquetaNormal() {

	glm::mat4 model, modelaux;

	//lado derecho, abajo
	model = glm::mat4(1.0);
	modelaux = model;
	model = glm::translate(model, glm::vec3(-110.0f, -1.0f, -100.0f));
	model = glm::scale(model, glm::vec3(38.5f, 16.0f, 89.0f)); //35 original, 75 a lo largo original
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta.RenderModel();

	//lado derecho, arriba
	model = glm::mat4(1.0);
	modelaux = model;
	model = glm::translate(model, glm::vec3(-110.0f, -1.0f, 575.0f));
	model = glm::scale(model, glm::vec3(38.5f, 16.0f, 89.0f)); //35 original, 75 a lo largo original
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta.RenderModel();



	//lado izquierdo, abajo
	model = glm::mat4(1.0);
	modelaux = model;
	model = glm::translate(model, glm::vec3(105.0f, -1.0f, -280.0f));
	model = glm::scale(model, glm::vec3(43.5f, 16.0f, 89.0f)); //41.5 en ancho no se ve mal, 75 a lo largo original
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta.RenderModel();

	//lado izquierdo, arriba

	model = glm::mat4(1.0);
	modelaux = model;
	model = glm::translate(model, glm::vec3(105.0f, -1.0f, 382.0f));
	model = glm::scale(model, glm::vec3(43.5f, 16.0f, 89.0f)); //41.5 en ancho no se ve mal, 75 a lo largo original
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta.RenderModel();

}

void renderBanquetaBaked() {

	glm::mat4 model, modelaux;

	//lado derecho, abajo
	model = glm::mat4(1.0);
	modelaux = model;
	model = glm::translate(model, glm::vec3(-110.0f, -1.0f, -100.0f));
	model = glm::scale(model, glm::vec3(38.5f, 16.0f, 89.0f)); //35 original, 75 a lo largo original
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta_luz.RenderModel();

	//lado derecho, arriba
	model = glm::mat4(1.0);
	modelaux = model;
	model = glm::translate(model, glm::vec3(-110.0f, -1.0f, 575.0f));
	model = glm::scale(model, glm::vec3(38.5f, 16.0f, 89.0f)); //35 original, 75 a lo largo original
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta_luz.RenderModel();



	//lado izquierdo, abajo
	model = glm::mat4(1.0);
	modelaux = model;
	model = glm::translate(model, glm::vec3(105.0f, -1.0f, -280.0f));
	model = glm::scale(model, glm::vec3(43.5f, 16.0f, 89.0f)); //41.5 en ancho no se ve mal, 75 a lo largo original
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta_luz.RenderModel();

	//lado izquierdo, arriba

	model = glm::mat4(1.0);
	modelaux = model;
	model = glm::translate(model, glm::vec3(105.0f, -1.0f, 382.0f));
	model = glm::scale(model, glm::vec3(43.5f, 16.0f, 89.0f)); //41.5 en ancho no se ve mal, 75 a lo largo original
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banqueta_luz.RenderModel();



}

void renderLuminarias() {
	glm::mat4 model;

	//abajo derecha
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-120.0f, 1.5f, -102.0f));
	model = glm::scale(model, glm::vec3(65.0f));
	//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	street_lamp.RenderModel();

	//arriba derecha
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-120.0f, 1.5f, 570.0f));
	model = glm::scale(model, glm::vec3(65.0f));
	//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	street_lamp.RenderModel();

	//abajo izquierda
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(120.0f, 1.5f, -275.0f));
	model = glm::scale(model, glm::vec3(65.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	street_lamp.RenderModel();

	//arriba izquierda
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(120.0f, 1.5f, 368.0f));
	model = glm::scale(model, glm::vec3(65.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	street_lamp.RenderModel();




}

void renderReflector() {

	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(230.0f, 0.5f, -750.0f));
	model = glm::scale(model, glm::vec3(5.0f));
	//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	reflector.RenderModel();

}

void renderMetrobus() {
	radioCircunferencia = 100.0f;
	glm::mat4 model, modelaux;

	model = glm::mat4(1.0);
	//printf("(%f,%f,%f)\n", sqrt(pow(radioCircunferencia, 2) - pow(metrobusZ, 2)), 2.5f + metrobusY, metrobusZ);
	model = glm::translate(model, glm::vec3(0.0f + metrobusX, 2.5f + metrobusY, 175.0f + metrobusZ));
	model = glm::scale(model, glm::vec3(0.6f));
	model = glm::rotate(model, giroDeMB * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
	
	//printf("\t---------> %d (%f < %f)\n", metrobusZ < radioCircunferencia, metrobusZ, radioCircunferencia);
	//metrobusZ = -200.0f;
	//printf("Estamos en: (%f,\t%f,\t%f)\n", camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
	if (flagBus0) {
		if (metrobusZ <= -100.0f) {
			auxiliarDesbordamiento = metrobusZ;
			metrobusZ += traslacionMetrobusOffSet * deltaTime;
			if (controlDeltaTimeDesborde2) {
				//printf("\t\t%f", auxiliarDesbordamiento);
				metrobusZ = auxiliarDesbordamiento;
				metrobusX = 30.0f;
				controlDeltaTimeDesborde2 = false;
			}
			giroDeMBOffSet = 0.8;
			if (metrobusZ >= -120.0f && metrobusZ < -55.0f) {
				giroDeMB += giroDeMBOffSet * deltaTime;
			}
		}
		else {
			flagBus0 = false;
			flagBus1 = true;
		}
	}

	if (flagBus1) {

		if (metrobusZ + 1 < radioCircunferencia - 4) {
			preview = sqrt(pow(radioCircunferencia, 2) - pow(metrobusZ, 2));
			metrobusX = (preview >= 30.0f) ? preview : 30.0f;
			metrobusZ += traslacionMetrobusOffSet * deltaTime;
			//<>
			giroDeMBOffSet = 0.4;
			if (metrobusZ < -55.0f) {
				giroDeMB += giroDeMBOffSet * deltaTime;
			}
			if (metrobusZ >= -55.0f && metrobusZ < 75.0f) {
				giroDeMB -= giroDeMBOffSet * deltaTime;
			}
			giroDeMBOffSet = 0.9;
			if (metrobusZ >= 75.0f && metrobusZ < 95.0f) {
				giroDeMB += giroDeMBOffSet * deltaTime;
			}

		}
		else {
			flagBus1 = false;
			flagBus2 = true;
		}
	}
	// -26 a 41 //33 de radio
//<>
	if (flagBus2) {
		if (metrobusZ < 460.0f) {
			metrobusZ += traslacionMetrobusOffSet * deltaTime;
		}
		else {
			flagBus2 = false;
			flagBus3 = true;
		}
	}

	if (flagBus3) {
		if (metrobusZ < 490.0f && flagBus4) {
			metrobusZ += traslacionMetrobusOffSet * deltaTime;
		}
		else {
			flagBus4 = false;
			flagBus5 = true;
			
		}
		

		if (flagBus5) {
			if (metrobusZ > 460.0f) {
				metrobusZ -= traslacionMetrobusOffSet * deltaTime;
				valorUnitario = -1.0f;
			}
			else {
				flagBus3 = false;
				flagBus6 = true;
			}
		}

		diferenciaParaCalcularOrigen = metrobusZ - 460.0f;
		radioCircunferencia = 30;
		//metrobusZ + 1 < radioCircunferencia - 8
		if (diferenciaParaCalcularOrigen + 1 < radioCircunferencia) {
			metrobusX = valorUnitario * sqrt(pow(radioCircunferencia, 2) - pow(diferenciaParaCalcularOrigen, 2)) + 12;
		}
		giroDeMBOffSet =1.5;
		giroDeMB -= giroDeMBOffSet * deltaTime;
	}

	if (flagBus6) {
		if (metrobusZ > 91.0f) {
			metrobusZ -= traslacionMetrobusOffSet * deltaTime;
		}
		else {
			flagBus6 = false;
			flagBus7 = true;
		}
	}
	//<>
	if (flagBus7) {
		radioCircunferencia = 100.0f;
		diferenciaParaCalcularOrigen = radioCircunferencia - (radioCircunferencia - metrobusZ);
		preview = valorUnitario * sqrt(pow(radioCircunferencia, 2) - pow(diferenciaParaCalcularOrigen, 2));
		
		if (preview < -60.0f) {
			metrobusX = preview;
			//(,0)
			if (metrobusZ >= 0.0f && metrobusZ < 100.0f) {
				giroDeMBOffSet = 0.2f;
				giroDeMB += giroDeMBOffSet * deltaTime;
			}
			else {
				if (preview < -60.0f) {
					giroDeMBOffSet = 0.2f;
					giroDeMB -= giroDeMBOffSet * deltaTime;
				}
			}
	
		}
		if (metrobusZ > -450.0f) {
			metrobusZ -= traslacionMetrobusOffSet * deltaTime;
		}
		else {
			flagBus7 = false;
		}
		
	}
}

void renderHelicoptero() {

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
		if (movHelicopteroX > -400.0f) {
			inclinacion = 0.4f;
			movHelicopteroX -= movHelicopteroOffset * deltaTime;
			if (movHelicopteroX < -20.0f) {
				movHelicopteroY -= movHelicopteroOffset * deltaTime;
			}

		}
		else {
			avanzaHelicoptero2 = false;
			avanzaHelicoptero3 = true;
		}
	}

	if (avanzaHelicoptero3) {
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
		if (movHelicopteroZ < 0.0f) {
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
	model = glm::translate(model, glm::vec3(-400, -0.5f, 190.0));
	model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
	//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	bus_padrinos.RenderModel();

}

void renderCactus() {

	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(250.0f, -0.5f, 260.0));
	model = glm::scale(model, glm::vec3(10.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cactus.RenderModel();

}

void renderRoadBlock() {

	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-150.0f, 0.0f, 130.0));
	model = glm::scale(model, glm::vec3(0.2f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	RoadBlock.RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-150.0f, 0.0f, 165.0));
	model = glm::scale(model, glm::vec3(0.2f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	RoadBlock.RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-150.0f, 0.0f, 200.0));
	model = glm::scale(model, glm::vec3(0.2f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	RoadBlock.RenderModel();

	//Lado izquierdo

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(150.0f, 0.0f, 130.0));
	model = glm::scale(model, glm::vec3(0.2f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	RoadBlock.RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(150.0f, 0.0f, 165.0));
	model = glm::scale(model, glm::vec3(0.2f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	RoadBlock.RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(150.0f, 0.0f, 200.0));
	model = glm::scale(model, glm::vec3(0.2f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	RoadBlock.RenderModel();

}

void renderBusStop() {

	glm::mat4 model;

	//Astrodomo
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-122.0f, 0.0f, -230.0));
	model = glm::scale(model, glm::vec3(0.7f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	BusStop.RenderModel();

	//Casa de Timmy
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(122.0f, 0.0f, 435.0));
	model = glm::scale(model, glm::vec3(0.7f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	BusStop.RenderModel();

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
	model = glm::translate(model, glm::vec3(170.0f, 10.0f, -90.0));
	model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelauxPulga = model;
	laPulgaInferior.RenderModel();

	model = glm::translate(model, glm::vec3(0.0f, 0.5f, -1.0f));
	model = glm::rotate(model, sube * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	laPulgaSuperior.RenderModel();
	model = modelauxPulga;
}

void renderPerroRicochet() {
	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(170.0f, 0.5f, -115.0));
	model = glm::scale(model, glm::vec3(4.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	perro_ricochet.RenderModel();
}



void renderBrickWall() {
	glm::mat4 model,modelaux;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(262.0f, 0.5f, -780.0));
	model = glm::scale(model, glm::vec3(184.0f, 50.0f, 12.0f));
	//model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brick_wall.RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-265.0f, 0.5f, -780.0));
	model = glm::scale(model, glm::vec3(185.0f, 50.0f, 12.0f));
	//model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brick_wall.RenderModel();


	//model = glm::mat4(1.0);
	//model = glm::translate(model, glm::vec3(380.0f, 0.5f, -750.0));
	//model = glm::scale(model, glm::vec3(10.0f, 30.0f, 10.0f));
	////model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//brick_wall_corner.RenderModel();


}


void renderFishyFish() {

	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, 15.0f, 145.0f));
	model = glm::scale(model, glm::vec3(5.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	fish.RenderModel();
}

void renderMutantPlant() {
	
	if (MueveCabeza)
	{
		if (anguloCabeza > 0.0f)
		{

			anguloCabeza -= movCabezaOffset * deltaTime;
			giraCabeza += giraCabezaOffset * deltaTime;
			//printf("gira1 %f \n", anguloCabeza);

			if (controlDeltaTimeDesborde) {
				sube = 0.0f;
				controlDeltaTimeDesborde = false;
			}
		}
		else
		{
			MueveCabeza = false;
		}
	}

	else
	{
		if (anguloCabeza < 90.0f)
		{
			anguloCabeza += movCabezaOffset * deltaTime;
			giraCabeza -= giraCabezaOffset * deltaTime;
			//printf("gira2 %f \n", anguloCabeza);
		}
		else
		{
			MueveCabeza = true;
		}
	}

	if (MueveMandibula)
	{
		if (anguloMandibula > 55.0f)
		{

			anguloMandibula -= movMandibulaOffset * deltaTime;
			giraMandibula += giraMandibulaOffset * deltaTime;
			//printf("gira1 %f \n", anguloMandibula);

			if (controlDeltaTimeDesborde) {
				sube = 0.0f;
				controlDeltaTimeDesborde = false;
			}
		}
		else
		{
			MueveMandibula = false;
		}
	}

	else
	{
		if (anguloMandibula < 100.0f)
		{
			anguloMandibula += movMandibulaOffset * deltaTime;
			giraMandibula -= giraMandibulaOffset * deltaTime;
			//printf("gira2 %f \n", anguloMandibula);
		}
		else
		{
			MueveMandibula = true;
		}
	}


	glm::mat4 model,modelAuxInf,modelAuxSup;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-320.0f, 0.0f, 265.0f));
	model = glm::scale(model, glm::vec3(12.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelAuxInf = modelAuxSup = model;
	mutant_tallo.RenderModel();

	model = glm::translate(model, glm::vec3(-0.7f, 2.1f, 0.0f));
	model = glm::rotate(model, 40 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, giraCabeza * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelAuxSup = model;
	mutant_Inf.RenderModel();

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, giraMandibula * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	mutant_Sup.RenderModel();

	//planta 2

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(270.0f, 0.0f, 410.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(12.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelAuxInf = modelAuxSup = model;
	mutant_tallo.RenderModel();

	model = glm::translate(model, glm::vec3(-0.7f, 2.1f, 0.0f));
	model = glm::rotate(model, 40 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, giraCabeza * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelAuxSup = model;
	mutant_Inf.RenderModel();

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, giraMandibula * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	mutant_Sup.RenderModel();

	//Planta 3
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(270.0f, 0.0f, 455.0f));
	model = glm::scale(model, glm::vec3(12.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelAuxInf = modelAuxSup = model;
	mutant_tallo.RenderModel();

	model = glm::translate(model, glm::vec3(-0.7f, 2.1f, 0.0f));
	model = glm::rotate(model, 40 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, giraCabeza * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelAuxSup = model;
	mutant_Inf.RenderModel();

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, giraMandibula * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	mutant_Sup.RenderModel();

}


void renderTrafficLight() {
	glm::mat4 model;

	//desde el angel
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(75.0f, 0.0f, 55.0f));
	model = glm::scale(model, glm::vec3(17.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	traffic_light.RenderModel();

	//desde la estela de luz
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-80.0f, 0.0f, 275.0f));
	model = glm::scale(model, glm::vec3(17.0f));
	//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	traffic_light.RenderModel();

}

void renderDoidle() {
	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-180.0f, 0.5f, 485.0f));
	model = glm::scale(model, glm::vec3(3.5f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	doidle.RenderModel();
}


void renderPrueba() {
	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-180.0f, 0.5f, 485.0f));
	model = glm::scale(model, glm::vec3(3.5f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	prueba.RenderModel();
}

void renderBancas() {
	glm::mat4 model;

	//Lado izquierdo
	/*model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-170.0f, -0.5f, 375.0));
	model = glm::scale(model, glm::vec3(24.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banca.RenderModel();*/

	//Lado derecho
	/*model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(170.0f, -0.5f, -175.0));
	model = glm::scale(model, glm::vec3(24.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banca.RenderModel();*/

	//Frente a mucha lucha
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-210.0f, -0.5f, -530.0));
	model = glm::scale(model, glm::vec3(24.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banca.RenderModel();
}

void renderTrashcan() {
	glm::mat4 model;

	//frente a ratatouille
	/*model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-170.0f, -0.5f, 340.0));
	model = glm::scale(model, glm::vec3(22.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	trashcan.RenderModel();*/

	//frente a Dimmadome
	/*model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(170.0f, -0.5f, -210.0));
	model = glm::scale(model, glm::vec3(22.0f));
	model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	trashcan.RenderModel();*/



	//frente a donuts
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-210.0f, -0.5f, -490.0));
	model = glm::scale(model, glm::vec3(19.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	trashcan.RenderModel();
}




void renderTaxi() {

	glm::mat4 model;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(35.0f, -0.5f, 375.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	taxi.RenderModel();

}

void renderTokyoTree() {

	glm::mat4 model;

	//Lado derecho

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-185.0f, 0.0f, -230.0f));
	model = glm::scale(model, glm::vec3(5.5f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	tokyo_tree.RenderModel();


	//al lado de Dexter's House
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-365.0f, 0.0f, 435.0f));
	model = glm::scale(model, glm::vec3(5.5f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	tokyo_tree.RenderModel();

	//Frente a casa timmy
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(260.0f, 0.0f, 545.0f));
	model = glm::scale(model, glm::vec3(5.5f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	tokyo_tree.RenderModel();

	//atrás de rampa dimmadome
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(215.0f, 0.0f, -130.0f));
	model = glm::scale(model, glm::vec3(5.5f));
	model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	tokyo_tree.RenderModel();

}


void renderJacarandas() {

	glm::mat4 model;

	//Lado izquierdo
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(170.0f, 0.0f, 695.0f));
	model = glm::scale(model, glm::vec3(34.0f, 42.0f, 30.0f));
	//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jacaranda.RenderModel();


	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(175.0f, 0.0f, 65.0f));
	model = glm::scale(model, glm::vec3(34.0f, 42.0f, 30.0f));
	//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jacaranda.RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(190.0f, 0.0f, -455.0f));
	model = glm::scale(model, glm::vec3(34.0f, 42.0f, 30.0f));
	//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jacaranda.RenderModel();

	//----------------------------------Lado derecho-----------------------------------
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-170.0f, 0.0f, 695.0f));
	model = glm::scale(model, glm::vec3(34.0f, 42.0f, 30.0f));
	//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jacaranda.RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-175.0f, 0.0f, 85.0f));
	model = glm::scale(model, glm::vec3(34.0f, 42.0f, 30.0f));
	//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jacaranda.RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-190.0f, 0.0f, -455.0f));
	model = glm::scale(model, glm::vec3(34.0f, 42.0f, 30.0f));
	//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jacaranda.RenderModel();





}


void renderNaveDexter() {

	movBaseNave += giraBaseOffset * deltaTime;
	//tiempoInicial = clock();

	if (avanzaNave) {
		if (movNaveZ > -1275.0f) {
			movNaveZ -= movNaveOffset * deltaTime;
			//printf("ValorZ1: %f \n", movNaveZ);
			if (controlDeltaTimeDesborde0) {
				movNaveZ = 0.0f;
				controlDeltaTimeDesborde0 = false;
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

	glm::mat4 model, modelauxNave;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(120.0f + movNaveX, 150.0f, 600.0 + movNaveZ));
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
	glm::mat4 model, modelauxPuerta;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-3.0f, -0.95f, -780.0f));
	model = glm::scale(model, glm::vec3(65.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelauxPuerta = model;
	puerta_reja.RenderModel();

	model = glm::translate(model, glm::vec3(-1.05f, 0.8f, 0.0f));
	model = glm::rotate(model, glm::radians(mainWindow.getarticulacion_puerta()), glm::vec3(0.0f, 1.0f, 0.0f));

	//REJA DERECHA
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); //52.5 en y antes, 65.0 en x
	model = glm::scale(model, glm::vec3(1.0f));
	model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	reja_der.RenderModel();

	model = modelauxPuerta;

	//REJA IZQUIERDA
	model = glm::translate(model, glm::vec3(1.05f, 0.85f, 0.0f));
	model = glm::rotate(model, glm::radians(mainWindow.getarticulacion_puerta2()), glm::vec3(0.0f, 1.0f, 0.0f));
	
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); //40 en x antes
	model = glm::scale(model, glm::vec3(1.0f));
	model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	reja_izq.RenderModel();
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

void renderLetrasAstrodomo() {
	
	rotacionLetras += rotacionLetrasOffset * deltaTime;

	glm::mat4 model, modelauxAstrodomo;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-305.0f, -2.0f, -55.0f));
	model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
	model = glm::rotate(model, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	modelauxAstrodomo = model;
	Astrodomo.RenderModel();

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, rotacionLetras * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 1.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	AstrodomoLetras.RenderModel();

}
/*
Código retirado del main que no sé si se va a necesitar en algun momento;.

	glm::mat4 dexRotPos(1.0f);

	dexRotPos = glm::rotate(dexRotPos, glm::radians(dexter.getRotY()), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec4 CamPos(dexter.getPos(), 1.0f);
	glm::vec4 desp(0.0f, 15.0f, -35.0f,0.0f);

	glm::vec4 CamPos(dexter.getPos(), 1.0f);

		////dexRotPos = glm::rotate(dexRotPos, glm::radians(dexter.getRotY()), glm::vec3(0.0f, 1.0f, 0.0f));
		//dexRotPos = glm::rotate(dexRotPos, glm::radians(mainWindow.getRotacionAvatar()), glm::vec3(0.0f, 1.0f, 0.0f));
		//CamPos = dexRotPos * (CamPos + desp);


		//camera.setPosicionX(CamPos.x);
		//camera.setPosicionY(CamPos.y);
		//camera.setPosicionZ(CamPos.z);

	movCoche = 0.0f;
	movOffset = 0.8f;
	rotllanta = 0.0f;
	rotllantaOffset = 5.0f;
	rotPuertaOffset = 5.0f;
	avanza = true;
	abre = true;
	rotPuerta = 0.5f;

	//DEJO COMENTADO EL INSTANCIAMIENTO DEL AGAVE PARA PRUEBAS DE BLENDING

		////Agave  qu  sucede si lo renderizan antes del coche y el helic ptero?
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


		DirectionalLight calcSunlight() {
	GLfloat intensity = 0.4f , dintensity = 0.5f;
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
		dintensity = 0.5f;
	}
	else {
		red = 0.6f - 0.1 * sin(glm::radians(anguloLuz));
		green = 0.6f - 0.1 * sin(glm::radians(anguloLuz));
		blue = 0.6f + (0.4 * sin(glm::radians(anguloLuz)));
		intensity = 0.2f;
		dintensity = 0.2f;
	}



	DirectionalLight sol = DirectionalLight(red, green, blue,
		intensity, dintensity,
		xDir, yDir, 0.0f);

	return sol;
}


*/