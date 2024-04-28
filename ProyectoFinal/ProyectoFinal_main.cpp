/*
Proyecto Final: CDMX ISEKAI

Integrantes:

- Francisco Hernandez Arturo
- Tapia Navarro Rodrigo
- Toledo Valencia Jesus Antonio
- Valenzuela Vigil Angel David
*/


#define STB_IMAGE_IMPLEMENTATION


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

//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

//Para sonido
#include <irrklang.h>
using namespace irrklang;

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

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

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


//GENERAL
Model luminaria;
Model angel_independencia;
Model angel_independencia_ala;
Model bbva;
Model estela_de_luz;




//Padrinos Magicos
Model diana_cazadora;
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


//Mucha Lucha

Model Astrodomo;
Model tienda_donas;







//SKYBOX
Skybox skybox;





//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;



//Declaración de Luces


// luz direccional
DirectionalLight mainLight;


//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
PointLight pointLights2[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotLights2[MAX_SPOT_LIGHTS];
//SpotLight spotLights3[MAX_SPOT_LIGHTS];



// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//funci�n de calculo de normales por promedio de v�rtices 
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
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1); //meshlist0

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2); //mesh list 1


	//PISO
	Mesh *obj3 = new Mesh();
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
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}




int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.5f, 0.5f);

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








	//----------Modelos Generales---------------------
	angel_independencia = Model();
	angel_independencia.LoadModel("Models/Angel.obj");

	angel_independencia_ala = Model();
	angel_independencia_ala.LoadModel("Models/AngelAla.obj");

	bbva = Model();
	bbva.LoadModel("Models/BBVA.obj");

	estela_de_luz = Model();
	estela_de_luz.LoadModel("Models/Estela.obj");

	diana_cazadora = Model();
	diana_cazadora.LoadModel("Models/DianaCupido.obj");







	//----------Modelos Mucha Lucha---------------------
	Astrodomo = Model();
	Astrodomo.LoadModel("Models/MuchaLucha/Astrodomo.obj");

	tienda_donas = Model();
	tienda_donas.LoadModel("Models/MuchaLucha/SlamminDonuts.obj");


	//----------Modelos Padrinos Magicos---------------------
	
	big_wand = Model();
	big_wand.LoadModel("Models/Padrinos/BigWand.obj");

	bus_padrinos = Model();
	bus_padrinos.LoadModel("Models/Padrinos/Bus.obj");


	//----------Modelos Lab. de Dexter---------------------

	casa_dexter = Model();
	casa_dexter.LoadModel("Models/DextersLab/CasaDexter.obj");



	//AVATAR (DEXTER)

	dexter_body = Model();
	dexter_body.LoadModel("Models/DextersLab/DexterBody.obj");

	dexter_arm = Model();
	dexter_arm.LoadModel("Models/DextersLab/DexterArm.obj");

	dexter_leg = Model();
	dexter_leg.LoadModel("Models/DextersLab/DexterLeg.obj");
	



	//----------Modelos Ratatouille---------------------

 

	//LUMINARIA PARA REPORTE 08
	luminaria = Model();
	luminaria.LoadModel("Models/luminaria_text.obj");



	
	//SKYBOX
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/sky-right.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-left.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-down.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-up.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-front.jpg");
	skyboxFaces.push_back("Textures/Skybox/sky-back.jpg");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);



	//APARTADO DE LUCES



	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);


	//contador de luces puntuales

	unsigned int pointLightCount = 0;
	unsigned int pointLightCount2 = 0;
	/*unsigned int pointLightCount3 = 0;*/


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





	unsigned int spotLightCount = 0; //ARREGLO 0 -> TODAS LAS LUCES ENCENDIDAS
	unsigned int spotLightCount2 = 0; //ARREGLO 1 -> CUANDO EL AUTO AVANZA
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


	//luz trasera del auto ENCENDIDA

	spotLights2[3] = SpotLight(1.0f, 0.0f, 0.0f, 
		1.0f, 2.0f,
		0.0f, 50.0f, 10.0f,
		0.0f, 0.0f, 10.0f,
		1.0f, 0.01f, 0.001f,
		20.0f);
	spotLightCount2++;



	//se crean mas luces puntuales y spotlight 



	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0); //PARA EL CHASIS
	glm::mat4 modelaux2(1.0);



	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	alaIzq = true;
	alaDer = true;
	giraAlaIzq = 0.0f;
	giraAlaDer = 0.0f;
	anguloAlaIzq = 90.0f;
	anguloAlaDer = 90.0f;
	giraAlaOffset = 1.0f;
	movAlaOffset = 1.0f;

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
	//

	
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Aquí irán las funciones de las animaciones
		//ala izquierda
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


		//if (alaDer)
		//{
		//	if (anguloAlaDer >= 0.0f)
		//	{
		//		anguloAlaDer -= movAlaOffset * deltaTime;
		//		giraAlaDer -= giraAlaOffset * deltaTime;
		//	}
		//	else
		//	{
		//		alaDer = false;
		//	}
		//}

		//else
		//{
		//	if (anguloAlaDer <= 90.0f)
		//	{
		//		anguloAlaDer += movAlaOffset * deltaTime;
		//		giraAlaDer += giraAlaOffset * deltaTime;
		//	}
		//	else
		//	{
		//		alaDer = true;
		//	}
		//}


		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
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
		glm::mat4 modelaux2(1.0);
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




		//INSTANCIAMIENTO DE LOS MODELOS
		//X para ancho del mapa y Z para largo del mapa




		//Modelos Generales del mundo

		//Diana cazadora
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 175.0));
		model = glm::scale(model, glm::vec3(4.0f, 5.0f, 4.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		diana_cazadora.RenderModel();


		model = modelaux;


		//Angel de la independencia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -1.0f, -530.0));
		model = glm::scale(model, glm::vec3(7.0f, 8.0f, 7.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux2 = modelaux = model;
		angel_independencia.RenderModel();

		model = glm::translate(model, glm::vec3(0.0f, 28.5f, -0.5f));
		model = glm::rotate(model, giraAlaIzq * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		//Ala del angel 1
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		angel_independencia_ala.RenderModel();


		model = modelaux2;

		model = glm::translate(model, glm::vec3(0.0f, 28.5f, -0.5f));
		model = glm::rotate(model, giraAlaDer * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	
		//Ala del angel 2
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		angel_independencia_ala.RenderModel();


		


		//Edificio BBVA/Pixies

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(350.0f, -1.0f, 350.0));
		model = glm::scale(model, glm::vec3(220.0f, 220.0f, 220.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bbva.RenderModel();




		//Estela de Luz


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(200.0f, -1.0f, 620.0));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		estela_de_luz.RenderModel();





		//Modelos Mucha Lucha


		//ASTRODOMO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-335.0f, -2.0f, -320.0)); 
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, -270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Astrodomo.RenderModel();
		

		model = modelaux;


		//Slammin Donuts

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.0f, -6.0f, -10.0));
		model = glm::scale(model, glm::vec3(1.6f, 1.6f, 1.6f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tienda_donas.RenderModel();


		model = modelaux;
		
	

		//Modelos - Padrinos Mágicos

		//Big Wand
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-180.0f, -2.0f, 245.0));
		model = glm::scale(model, glm::vec3(17.0f, 17.0f, 17.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		big_wand.RenderModel();
		model = modelaux;



		//Bus
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, -2.0f, -380.0));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bus_padrinos.RenderModel();
		model = modelaux;








		//Modelos - Ratatouille




		//Modelos - Laboratorio de Dexter


		//Casa de dexter

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(370.0f, -2.0f, -40.0));
		model = glm::scale(model, glm::vec3(52.0f, 52.0f, 52.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casa_dexter.RenderModel();
		model = modelaux;
		






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


		model = modelaux;


		//MODELO DE LUMINARIA PARA REPORTE 08

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, -0.95f, -100.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		luminaria.RenderModel();

		model = modelaux;




		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
