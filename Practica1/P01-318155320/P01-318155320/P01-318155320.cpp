#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include<random>

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;
float rojo, verde, azul;
float rango_rojo_min = 0.0f;
float rango_rojo_max = 1.0f;
float rango_verde_min = 0.0f; 
float rango_verde_max = 1.0f;
float rango_azul_min = 0.0f;
float rango_azul_max = 1.0f;

//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(0.0f,0.0f,0.0f,1.0f);	 			\n\
}";

void CrearTriangulo()
{
	GLfloat vertices[] = {
		//Letra R
		-0.95f, -0.6f, 0.0f,
		-0.85f,-0.6f, 0.6f,
		-0.95f,0.6f,0.0f,

		-0.95f, 0.6f, -0.0f,
		-0.85f,-0.6f, 0.0f,
		-0.85f,0.6f,-0.0f,

		-0.85f, 0.6f, 0.0f,
		-0.60f, 0.6f, -0.0f,
		-0.85f, 0.4f,0.0f,

		-0.60f, 0.6f, -0.0f,
		-0.75f, 0.48f, -0.0f,
		-0.75f, 0.0f,0.0f,

		-0.60f, 0.6f, -0.0f,
		-0.75f, 0.0f, -0.0f,
		-0.60f, 0.0f, 0.0f,

		-0.85f, 0.0f, -0.0f,
		-0.70f,-0.6f, -0.0f,
		-0.58f,-0.6f,0.0f,

		-0.85f, 0.0f, -0.0f,
		-0.75f,-0.0f, -0.0f,
		-0.58f,-0.6f,0.0f,

		-0.85f, 0.0f, -0.0f,
		-0.85f, 0.1f, -0.0f,
		-0.75f, 0.1f,0.0f,

		-0.75f, 0.1f, -0.0f,
		-0.85f, 0.0f, -0.0f,
		-0.75f, 0.0f,0.0f,

		-0.75f, 0.48f, -0.0f,
		-0.85f, 0.4f, -0.0f,
		-0.75f, 0.4f,0.0f,

		//Segunda R
		-0.45f, -0.6f, 0.0f,
		-0.35f,-0.6f, 0.6f,
		-0.45f,0.6f,0.0f,

		-0.45f, 0.6f, -0.0f,
		-0.35f,-0.6f, 0.0f,
		-0.35f,0.6f,-0.0f,

		-0.35f, 0.6f, 0.0f,
		-0.10f, 0.6f, -0.0f,
		-0.35f, 0.4f,0.0f,

		-0.10f, 0.6f, -0.0f,
		-0.25f, 0.48f, -0.0f,
		-0.25f, 0.0f,0.0f,

		-0.10f, 0.6f, -0.0f,
		-0.25f, 0.0f, -0.0f,
		-0.10f, 0.0f, 0.0f,

		-0.35f, 0.0f, -0.0f,
		-0.20f,-0.6f, -0.0f,
		-0.08f,-0.6f,0.0f,

		-0.35f, 0.0f, -0.0f,
		-0.25f,-0.0f, -0.0f,
		-0.08f,-0.6f,0.0f,

		-0.35f, 0.0f, -0.0f,
		-0.35f, 0.1f, -0.0f,
		-0.25f, 0.1f,0.0f,

		-0.25f, 0.1f, -0.0f,
		-0.35f, 0.0f, -0.0f,
		-0.25f, 0.0f,0.0f,

		-0.25f, 0.48f, -0.0f,
		-0.35f, 0.4f, -0.0f,
		-0.25f, 0.4f,0.0f,

		//Letra L
		0.05f, -0.6f, 0.0f,
		0.15f,-0.6f, 0.6f,
		0.05f,0.6f,0.0f,

		0.05f, 0.6f, -0.0f,
		0.15f,-0.6f, 0.0f,
		0.15f,0.6f,-0.0f,

		0.15f, -0.45f, 0.0f,
		0.35f, -0.45f, 0.0f,
		0.15f, -0.60f, 0.0f,

		0.15f, -0.6f, 0.0f,
		0.35f, -0.45f, 0.0f,
		0.35f, -0.6f, 0.0f,

		//Letra F
		0.50f, -0.6f, 0.0f,
		0.60f, -0.6f, 0.6f,
		0.50f, 0.6f, 0.0f,

		0.50f, 0.6f, -0.0f,
		0.60f, -0.6f, 0.0f,
		0.60f, 0.6f, -0.0f,

		0.60f, 0.6f, 0.0f,
		0.60f, 0.45, 0.0f,
		0.95f, 0.6f, 0.0f,

		0.95f, 0.6f, 0.0f,
		0.60f, 0.45f, 0.0f,
		0.95f, 0.45f, 0.0f,

		0.60f, 0.0f, 0.0f,
		0.60f, 0.15f, 0.0f,
		0.80f, 0.15f, 0.0f,

		0.80f, 0.15f, 0.0f,
		0.60f, 0.0f, 0.0f,
		0.80f, 0.0f, 0.0f


	};
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
		glEnableVertexAttribArray(0);
		//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader


{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	 //verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}

}
float numeroAleatorio(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

int main()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
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
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Segundo ejercicio practica 1", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

 //Crear tríangulo
	CrearTriangulo();
	CompileShaders();

	float tiempo_anterior = 0.0f;
	float tiempo_color = 2.0f;

	rojo = numeroAleatorio(rango_rojo_min, rango_rojo_max);
	verde = numeroAleatorio(rango_verde_min, rango_verde_max);
	azul = numeroAleatorio(rango_azul_min, rango_azul_max);

	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		
		// Obtener el tiempo actual
		float tiempo_actual = glfwGetTime();
		
		if (tiempo_actual - tiempo_anterior > tiempo_color)
		{
			// Generacion de colores de forma aleatoria
			rojo = numeroAleatorio(rango_rojo_min, rango_rojo_max);
			verde = numeroAleatorio(rango_verde_min, rango_verde_max);
			azul = numeroAleatorio(rango_azul_min, rango_azul_max);

			// Actualizacion el tiempo
			tiempo_anterior = tiempo_actual;	
		}

		// Limpiar la ventana con el color actual de la ventana
		glClearColor(rojo, verde, azul, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,90);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);

	}
	return 0;
}