/*
Práctica 7: Iluminación 1 
*/
//para cargar imagen
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
#include "Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture logofiTexture;
Texture Dado10Texture;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;
Model Coche;
Model Cofre;
Model Llanta1;
Model Llanta2;
Model Llanta3;
Model Llanta4;
Model Lampara;
Model Puerta;
Model Banca;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

//Arreglo de luces delanteras del coche
SpotLight spotLights2[MAX_SPOT_LIGHTS];

//Arreglo de luces traseras del coche
SpotLight spotLights3[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
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
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		-1.0f, -1.0f, -1.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		-1.0f, -1.0f, -1.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		-1.0f, -1.0f, -1.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		-1.0f, -1.0f, -1.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		-1.0f, -1.0f, -1.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		-1.0f, -1.0f, -1.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		-1.0f, -1.0f, -1.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		-1.0f, -1.0f, -1.0f,


	};
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CrearDado10()
{
	unsigned int Dado10_indices[] = {
		//top
		0,  1,  2,
		3,  4,  5,
		6,  7,  8,
		9, 10, 11,
	   12, 13, 14,

	   //bottom
	   15, 16, 17,
	   18, 19, 20,
	   21, 22, 23,
	   24, 25, 26,
	   27, 28, 29,

	};

	GLfloat Dado10_vertices[] = {
		// Parte de arriba
		//Cara 1
		//x		y		z		S		 T			 NX		  NY	   NZ
		-0.5f, -0.5f,  0.5f,	0.0f,    0.55f,	    0.0f,   -1.0f,   -1.0f,
		 0.5f, -0.5f,  0.5f,	0.2f,	 0.55f,	    0.0f,   -1.0f,   -1.0f,
		 0.0f,  0.5f, -0.35f,   0.1f,    1.0f,      0.0f,   -1.0f,   -1.0f,

		 //Cara 2
		 0.5f, -0.5f,  0.5f,	0.38f,	 0.55f,	   -1.0f,   -1.0f,   -1.0f,
		 1.0f, -0.5f, -0.5f,	0.6f,	 0.55f,	   -1.0f,   -1.0f,   -1.0f,
		 0.0f,  0.5f, -0.35f,   0.50f,   1.0f,     -1.0f,   -1.0f,   -1.0f,

		 //Cara 3
		 1.0f, -0.5f, -0.5f,	0.6f,	 0.0f,	   -1.0f,   -1.0f,    1.0f,
		 0.0f, -0.5f, -1.2f,	0.8f,	 0.0f,	   -1.0f,   -1.0f,    1.0f,
		 0.0f,  0.5f, -0.35f,   0.7f,    0.5f,     -1.0f,   -1.0f,    1.0f,

		 //Cara 4
		 0.0f, -0.5f, -1.2f,	0.8f,	 0.55f,	    1.0f,   -1.0f,    1.0f,
		-1.0f, -0.5f, -0.5f,	1.00f,   0.55f,     1.0f,   -1.0f,    1.0f,
		 0.0f,  0.5f, -0.35f,   0.9f,    1.00f,     1.0f,   -1.0f,    1.0f,

		 //Cara 5
		-1.0f, -0.5f, -0.5f,	0.2f,    0.00f,     1.0f,   -1.0f,   -1.0f,
		-0.5f, -0.5f,  0.5f,	0.4f,    0.00f,		1.0f,   -1.0f,   -1.0f,
	     0.0f,  0.5f, -0.35f,   0.3f,    0.50f,     1.0f,   -1.0f,   -1.0f,


	     //Parte de Abajo
	     //Cara 1
		 //x	 y		z		 S		   T		 NX		  NY	   NZ
		-0.5f, -0.5f,  0.5f,	0.4f,    0.55f,		0.0f,    1.0f,   -1.0f,
		 0.5f, -0.5f,  0.5f,	0.2f,	 0.55f,		0.0f,    1.0f,   -1.0f,
		 0.0f, -1.5f, -0.35f,   0.3f,    1.0f,      0.0f,    1.0f,   -1.0f,

		 //Cara 2
		 0.5f, -0.5f,  0.5f,	0.38f,	 0.0f,	   -1.0f,    1.0f,   -1.0f,
		 1.0f, -0.5f, -0.5f,	0.6f,	 0.0f,	   -1.0f,    1.0f,   -1.0f,
		 0.0f, -1.5f, -0.35f,   0.5f,    0.5f,     -1.0f,    1.0f,   -1.0f,

		 //Cara 3
		 1.0f, -0.5f, -0.5f,	1.0f,	 0.0f,	   -1.0f,    1.0f,    1.0f,
		 0.0f, -0.5f, -1.2f,	0.8f,	 0.0f,	   -1.0f,    1.0f,    1.0f,
		 0.0f, -1.5f, -0.35f,   0.9f,    0.6f,     -1.0f,    1.0f,    1.0f,

		 //Cara 4
		 0.0f, -0.5f, -1.2f,	0.80f,	0.55f,		1.0f,    1.0f,    1.0f,
	    -1.0f, -0.5f, -0.5f,	0.60f,  0.55f,      1.0f,    1.0f,    1.0f,
		 0.0f, -1.5f, -0.35f,   0.70f,  1.00f,      1.0f,    1.0f,    1.0f,

		 //Cara 5
	    -1.0f, -0.5f, -0.5f,	0.20f,  0.00f,      1.0f,    1.0f,   -1.0f,
	    -0.5f, -0.5f,  0.5f,	0.00f,  0.00f,		1.0f,    1.0f,   -1.0f,
		 0.0f, -1.5f, -0.35f,   0.10f,  0.55f,      1.0f,    1.0f,   -1.0f,

	};
	Mesh* Dado10 = new Mesh();
	Dado10->CreateMesh(Dado10_vertices, Dado10_indices, 320, 48);
	meshList.push_back(Dado10);

}


int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	CrearDado10();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

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
	Dado10Texture = Texture("Textures/dado_colores.tga");
	Dado10Texture.LoadTextureA();

	/*Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");*/
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Coche = Model();
	Coche.LoadModel("Models/coche.obj");

	Cofre = Model();
	Cofre.LoadModel("Models/cofre_tex.obj");

	Llanta1 = Model();
	Llanta1.LoadModel("Models/llanta1_tex.obj");

	Llanta2 = Model();
	Llanta2.LoadModel("Models/llanta2_tex.obj");

	Llanta3 = Model();
	Llanta3.LoadModel("Models/llanta3_tex.obj");

	Llanta4 = Model();
	Llanta4.LoadModel("Models/llanta4_tex.obj");

	Lampara = Model();
	Lampara.LoadModel("Models/lampara1.obj");

	Puerta = Model();
	Puerta.LoadModel("Models/Puerta.obj");

	Banca = Model();
	Banca.LoadModel("Models/Banca.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		-6.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	//luz de la lampara
	pointLights[1] = PointLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
	   -1.0f, 0.0f, 12.0f,
	    0.3f, 0.2f, 0.1f);
	pointLightCount++;
	
	//luz de la banca
	pointLights[2] = PointLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
	    5.5f, 0.0f, 11.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;
	
	//se crean mas luces puntuales y spotlight 

	//Luz del helicoptero
	spotLights[1] = SpotLight(1.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	//Luz de la puerta
	spotLights[2] = SpotLight(1.0f, 0.2706f, 0.0f,
		1.0f,  2.0f,
	   -0.5f,  11.0f, 29.3f,
		0.0f, -11.0f, 0.0f,
		0.3f,  0.0f,  0.0f,
		20.0f);
	spotLightCount++;


	unsigned int spotLightCount2 = 0;
	//Arreglo de luces para la parte delantera del coche
	spotLights2[0] = SpotLight(0.0f, 0.0f, 1.0f,
		7.0f, 2.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.09f, 0.09f,
		10.0f);
	spotLightCount2++;

	spotLights2[1] = SpotLight(0.0f, 0.0f, 1.0f,
		7.0f, 2.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.09f, 0.09f,
		10.0f);
	spotLightCount2++;

	//Arreglo de luces para la parte trasera del coche
	unsigned int spotLightCount3 = 0;
	spotLights3[0] = SpotLight(1.0f, 0.0f, 0.0f,
		20.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.09f, 0.09f,
		10.0f);
	spotLightCount3++;

	spotLights3[1] = SpotLight(1.0f, 0.0f, 0.0f,
		20.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.09f, 0.09f,
		10.0f);
	spotLightCount3++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

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
		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
			glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		//shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);
		
		//Condición para apagar la luz de nuestra lámpara y de la banca
		if (mainWindow.GetApagarLuz()) {
			shaderList[0].SetPointLights(pointLights, pointLightCount-2);
		}
		else {
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		}
		//Condicion para que se prenda la luz delantera
		if (mainWindow.GetPrenderLuz()) {
			shaderList[0].SetSpotLights(spotLights2, spotLightCount2);
		}
		//Condicion para que se prenda la luz trasera
		else if(mainWindow.GetPrenderLuz2()) {
			shaderList[0].SetSpotLights(spotLights3, spotLightCount3);
		}
		//Condicion para que vuelvan las primeras luces SpotLight
		else if (mainWindow.GetLucesSpothLights()) {
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
		}

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();
		
		float muevex = mainWindow.getmuevex();

		//Luces delanteras de color azul del coche
		glm::vec3 carPosition = glm::vec3(-3.2f + muevex, -1.08f, 2.7f);
		glm::vec3 carDirection = glm::vec3(-1.0f, 0.0f, 0.0f);

		glm::vec3 spotLightPosition= carPosition;
		glm::vec3 spotLightDirection = carDirection;
		spotLights2[0].SetFlash(spotLightPosition, spotLightDirection);

		glm::vec3 carPosition3 = glm::vec3(-3.2f + muevex, -1.08f, -0.0f);
		glm::vec3 carDirection3 = glm::vec3(-1.0f, 0.0f, 0.0f);

		glm::vec3 spotLightPosition4 = carPosition3;
		glm::vec3 spotLightDirection4 = carDirection3;
		spotLights2[1].SetFlash(spotLightPosition4, spotLightDirection4);
		

		//Luces traseras de color rojo del coche
		glm::vec3 carPosition2 = glm::vec3(4.0f + muevex, -1.08f, 0.0f);
		glm::vec3 carDirection2 = glm::vec3(1.0f, 0.0f, 0.0f);
		
		glm::vec3 spotLightPosition3 = carPosition2;
		glm::vec3 spotLightDirection3 = carDirection2;
		spotLights3[0].SetFlash(spotLightPosition3, spotLightDirection3);

		glm::vec3 carPosition4 = glm::vec3(4.0f + muevex, -1.08f, 2.7f);
		glm::vec3 carDirection4 = glm::vec3(1.0f, 0.0f, 0.0f);

		glm::vec3 spotLightPosition5 = carPosition4;
		glm::vec3 spotLightDirection5 = carDirection4;
		spotLights3[1].SetFlash(spotLightPosition5, spotLightDirection5);


		//Instancia del coche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex(), -1.08f, 1.5f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coche.RenderModel();

		//Cofre
		modelaux = model;
		model = glm::translate(model, glm::vec3(-3.0f, 1.5f, 40.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cofre.RenderModel();

		// Llanta1
		modelaux = model;
		model = glm::translate(model, glm::vec3(-25.0f, 0.0f, 5.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta1.RenderModel();
		
		// Llanta2
		modelaux = model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -102.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta2.RenderModel();
		
		//Llanta 3
		modelaux = model;
		model = glm::translate(model, glm::vec3(50.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta3.RenderModel();
		
		//Llanta 4
		modelaux = model;
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -102.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta4.RenderModel();	

		//Luz ligada al helicoptero
		glm::vec3 helPosition = glm::vec3(0.0f + mainWindow.getmuevex2(), 1.2f, 6.0f);
		glm::vec3 helDirection = glm::vec3(0.0f, -1.2f, 0.0f);

		glm::vec3 spotLightPosition2 = helPosition;
		glm::vec3 spotLightDirection2 = helDirection;
		spotLights[1].SetFlash(spotLightPosition2, spotLightDirection2);
		
		//Helicoptero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex2(), 5.0f, 6.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 11.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara.RenderModel();

		//Dado de 10 caras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, 1.0f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado10Texture.UseTexture();
		meshList[4]->RenderMesh();

		//Puerta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.05f, 30.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puerta.RenderModel();

		//Banca
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -1.0f, 11.5f));
		model = glm::scale(model, glm::vec3(0.02f,0.02f,0.02f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();

		//Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
