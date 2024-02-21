//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* vShaderRojo = "shaders/shader_rojo.vert";
static const char* vShaderAzul = "shaders/shader_azul.vert";
static const char* vShaderVerde = "shaders/shader_verde.vert";
static const char* vShaderCafe = "shaders/shader_cafe.vert";
static const char* vShaderVerdeF = "shaders/shader_verde_fuerte.vert";


float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
	   -0.53f,	  0.0f,		 0.0f,    //0
		0.53f,	  0.0f,		 0.0f,    //1
		0.0f,	  0.75f,    -0.57f,   //2
		0.0f,     0.0f,     -1.15f,   //3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.9f,  0.0f,   1.15f,
		 0.0f,  0.0f,   1.15f,
		 0.0f,  1.15f,  1.15f,
		-0.9f,  1.15f,  1.15f,
		// back
		-0.9f,  0.0f,  -1.15f,
		 0.0f,  0.0f,  -1.15f,
		 0.0f,  1.15f, -1.15f,
		-0.9f,  1.15f, -1.15f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);

}

void CrearCuboVerde()
{
	unsigned int CuboVerde_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3		
	};

	GLfloat CuboVerde_vertices[] = {
		// front
		0.1f,	0.0f,	 0.3f,
		0.4f,	0.0f,    0.3f,
		0.4f,   0.35f,   0.3f,
		0.1f,   0.35f,	 0.3f,

		//back
		0.1f,	0.0f,	-0.3f,
		0.4f,	0.0f,   -0.3f,
		0.4f,   0.35f,  -0.3f,
		0.1f,   0.35f,	-0.3f

	};

	Mesh* CuboVerde = new Mesh();
	CuboVerde->CreateMesh(CuboVerde_vertices, CuboVerde_indices, 24, 36);
	meshList.push_back(CuboVerde);
}

void CrearCuboCafe()
{
	unsigned int CuboCafe_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat CuboCafe_vertices[] = {
		// front
		0.1f,	0.0f,	 0.15f,
		0.25f,	0.0f,	 0.15f,
		0.25f,  0.2f,    0.15f,
		0.1f,   0.2f,	 0.15f,

		//back
		0.1f,	0.0f,	-0.15f,
		0.25f,	0.0f,	-0.15f,
		0.25f,  0.2f,   -0.15f,
		0.1f,   0.2f,	-0.15f,

	};

	Mesh* CuboCafe = new Mesh();
	CuboCafe->CreateMesh(CuboCafe_vertices, CuboCafe_indices, 24, 36);
	meshList.push_back(CuboCafe);
}

void CreaPiramideVerde()
{
	unsigned int PiramideVerde_indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat PiramideVerde_vertices[] = {
	   -0.2f,	  0.0f,		 0.0f,   //0
		0.2f,	  0.0f,      0.0f,   //1
		0.0f,	  0.6f,		 0.3f,   //2
		0.0f,     0.0f,     -0.15f,  //3

	};
	Mesh* PiramideVerde = new Mesh();
	PiramideVerde->CreateMesh(PiramideVerde_vertices, PiramideVerde_indices, 12, 12);
	meshList.push_back(PiramideVerde);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {	
			//X			Y			Z			R		G		B
			-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			/*1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,*/
			
	};
	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,18);
	meshColorList.push_back(letras);

	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
	   -0.2f,	  0.0f,		 0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	  0.6f,		 0.5f,			0.0f,	0.5f,	0.0f,
		0.2f,	  0.0f,      0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);

	GLfloat vertices_LetraRamarilla[] = {
		//X			Y			Z			R		G		B
	    -0.95f,	 -0.6f,       0.0f,        1.0f,   1.0f,   0.0f,
		-0.85f,	 -0.6f,       0.6f,        1.0f,   1.0f,   0.0f,
		-0.95f,   0.6f,       0.0f,        1.0f,   1.0f,   0.0f,

		-0.95f,   0.6f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.85f,  -0.6f,       0.0f,        1.0f,   1.0f,   0.0f,
		-0.85f,   0.6f,      -0.0f,        1.0f,   1.0f,   0.0f,

		-0.85f,   0.6f,       0.0f,        1.0f,   1.0f,   0.0f,
		-0.60f,   0.6f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.85f,   0.4f,       0.0f,        1.0f,   1.0f,   0.0f,

		-0.60f,   0.6f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.75f,   0.48f,     -0.0f,        1.0f,   1.0f,   0.0f,
		-0.75f,   0.0f,       0.0f,        1.0f,   1.0f,   0.0f,

		-0.60f,   0.6f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.75f,   0.0f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.60f,   0.0f,       0.0f,        1.0f,   1.0f,   0.0f,

		-0.85f,   0.0f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.70f,  -0.6f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.58f,  -0.6f,       0.0f,        1.0f,   1.0f,   0.0f,

		-0.85f,   0.0f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.75f,  -0.0f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.58f,  -0.6f,       0.0f,        1.0f,   1.0f,   0.0f,

		-0.85f,   0.0f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.85f,   0.1f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.75f,   0.1f,       0.0f,        1.0f,   1.0f,   0.0f,

		-0.75f,   0.1f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.85f,   0.0f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.75f,   0.0f,       0.0f,        1.0f,   1.0f,   0.0f,

		-0.75f,   0.48f,     -0.0f,        1.0f,   1.0f,   0.0f,
		-0.85f,   0.4f,      -0.0f,        1.0f,   1.0f,   0.0f,
		-0.75f,   0.4f,       0.0f,        1.0f,   1.0f,   0.0f,

	};

	MeshColor* LetraRamarilla = new MeshColor();
	LetraRamarilla->CreateMeshColor(vertices_LetraRamarilla, 187);
	meshColorList.push_back(LetraRamarilla);

	GLfloat vertices_LetraRroja[] = {
		//X			Y			Z			R		G		B
		-0.45f,   -0.6f,      0.0f,        0.5f,  0.0f,   0.0f,
		-0.35f,   -0.6f,      0.6f,        0.5f,  0.0f,   0.0f,
		-0.45f,    0.6f,      0.0f,        0.5f,  0.0f,   0.0f,

		-0.45f,    0.6f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.35f,   -0.6f,      0.0f,        0.5f,  0.0f,   0.0f,
		-0.35f,    0.6f,     -0.0f,        0.5f,  0.0f,   0.0f,

		-0.35f,    0.6f,      0.0f,        0.5f,  0.0f,   0.0f,
		-0.10f,    0.6f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.35f,    0.4f,      0.0f,        0.5f,  0.0f,   0.0f,

		-0.10f,    0.6f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.25f,    0.48f,    -0.0f,        0.5f,  0.0f,   0.0f,
		-0.25f,    0.0f,      0.0f,        0.5f,  0.0f,   0.0f,

		-0.10f,    0.6f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.25f,    0.0f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.10f,    0.0f,      0.0f,        0.5f,  0.0f,   0.0f,

		-0.35f,    0.0f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.20f,   -0.6f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.08f,   -0.6f,      0.0f,        0.5f,  0.0f,   0.0f,

		-0.35f,    0.0f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.25f,   -0.0f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.08f,   -0.6f,      0.0f,        0.5f,  0.0f,   0.0f,

		-0.35f,    0.0f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.35f,    0.1f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.25f,    0.1f,      0.0f,        0.5f,  0.0f,   0.0f,

		-0.25f,    0.1f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.35f,    0.0f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.25f,    0.0f,      0.0f,        0.5f,  0.0f,   0.0f,

		-0.25f,    0.48f,    -0.0f,        0.5f,  0.0f,   0.0f,
		-0.35f,    0.4f,     -0.0f,        0.5f,  0.0f,   0.0f,
		-0.25f,    0.4f,      0.0f,        0.5f,  0.0f,   0.0f,


	};

	MeshColor* LetraRroja = new MeshColor();
	LetraRroja->CreateMeshColor(vertices_LetraRroja, 187);
	meshColorList.push_back(LetraRroja);

	GLfloat vertices_LetraLazul[] = {
		//X			Y			Z			R		G		B
	    0.05f,    -0.6f,      0.0f,        0.0f,   1.0f,  1.0f,
		0.15f,    -0.6f,      0.6f,        0.0f,   1.0f,  1.0f,
		0.05f,     0.6f,      0.0f,        0.0f,   1.0f,  1.0f,

		0.05f,     0.6f,     -0.0f,        0.0f,   1.0f,  1.0f,
		0.15f,    -0.6f,      0.0f,        0.0f,   1.0f,  1.0f,
		0.15f,     0.6f,     -0.0f,        0.0f,   1.0f,  1.0f,

		0.15f,    -0.45f,     0.0f,        0.0f,   1.0f,  1.0f,
		0.35f,    -0.45f,     0.0f,        0.0f,   1.0f,  1.0f,
		0.15f,    -0.60f,     0.0f,        0.0f,   1.0f,  1.0f,

		0.15f,     -0.6f,     0.0f,        0.0f,   1.0f,  1.0f,
		0.35f,     -0.45f,    0.0f,        0.0f,   1.0f,  1.0f,
		0.35f,     -0.6f,     0.0f,        0.0f,   1.0f,  1.0f,
	};

	MeshColor* LetraLazul = new MeshColor();
	LetraLazul->CreateMeshColor(vertices_LetraLazul, 72);
	meshColorList.push_back(LetraLazul);

	GLfloat vertices_LetraFverde[] = {
		//X			Y			Z			R		G		B
		0.50f,    -0.6f,       0.0f,       0.0f,   0.5f,   0.0f,
		0.60f,    -0.6f,       0.6f,       0.0f,   0.5f,   0.0f,
		0.50f,     0.6f,       0.0f,       0.0f,   0.5f,   0.0f,

		0.50f,     0.6f,      -0.0f,       0.0f,   0.5f,   0.0f,
		0.60f,    -0.6f,       0.0f,       0.0f,   0.5f,   0.0f,
		0.60f,     0.6f,      -0.0f,       0.0f,   0.5f,   0.0f,

		0.60f,     0.6f,       0.0f,       0.0f,   0.5f,   0.0f,
		0.60f,     0.45,       0.0f,       0.0f,   0.5f,   0.0f,
		0.95f,     0.6f,       0.0f,       0.0f,   0.5f,   0.0f,

		0.95f,     0.6f,       0.0f,       0.0f,   0.5f,   0.0f,
		0.60f,     0.45f,      0.0f,       0.0f,   0.5f,   0.0f,
		0.95f,     0.45f,      0.0f,       0.0f,   0.5f,   0.0f,

		0.60f,     0.0f,       0.0f,       0.0f,   0.5f,   0.0f,
		0.60f,     0.15f,      0.0f,       0.0f,   0.5f,   0.0f,
		0.80f,     0.15f,      0.0f,       0.0f,   0.5f,   0.0f,

		0.80f,     0.15f,      0.0f,       0.0f,   0.5f,   0.0f,
		0.60f,     0.0f,       0.0f,       0.0f,   0.5f,   0.0f,
		0.80f,     0.0f,       0.0f,       0.0f,   0.5f,   0.0f,
	};

	MeshColor* LetraFverde = new MeshColor();
	LetraFverde->CreateMeshColor(vertices_LetraFverde, 108);
	meshColorList.push_back(LetraFverde);

}


void CreateShaders()
{
	Shader* shader0 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader0->CreateFromFiles(vShaderAzul, fShader);
	shaderList.push_back(*shader0);

	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShaderRojo, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();
	shader2->CreateFromFiles(vShaderVerde, fShader);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader();
	shader3->CreateFromFiles(vShaderCafe, fShader);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader();
	shader4->CreateFromFiles(vShaderVerdeF, fShader);
	shaderList.push_back(*shader4);

	Shader *shader5 = new Shader();//shader para usar color como parte del VAO: letras 
	shader5->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader5);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearCuboVerde(); //indice 2 en MeshList
	CrearCuboCafe(); //indice 3 en MeshList
	CreaPiramideVerde(); //indice 4 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
													
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		/*Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();
		*/
	
		

		//Ejercicio 2
		
		//Cubo rojo (casa)
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.45f, -0.95f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		
		//Piramide azul (Techo)
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Cubo verde (puerta)
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, -0.95f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[2]->RenderMesh();

		//Cubo verde (ventana izquierda)
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.45f, -0.25f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[2]->RenderMesh();

		//Cubo verde (ventana derecha)
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.05f, -0.25f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[2]->RenderMesh();

		//Cubo cafe (tronco izquierdo)
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.90f, -0.95f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[3]->RenderMesh();

		//Cubo cafe (tronco derecho)
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.55f, -0.95f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[3]->RenderMesh();

		//Piramide verde (arbol izquierdo)
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.73f, -0.75f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[4]->RenderMesh();

		//Piramide verde (arbol derecho)
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.72f, -0.75f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[4]->RenderMesh();
		
		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/