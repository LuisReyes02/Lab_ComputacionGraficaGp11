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
	GLfloat getmuevex() { return muevex; }
	GLfloat getmuevex2() { return muevex2; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	// Función para obtener el estado de apagar (si es true o false)
	bool GetApagarLuz() { return apagar; }
	// Función para establecer el estado de apagar (true o false)
	void ApagarLuz(bool state) { apagar = state; }

	//Funciones para que prendan las luces delanteras del coche
	bool GetPrenderLuz() { return prender; }
	void PrenderLuz(bool state) { prender = state; }

	//Funciones para que prendan las luces traseras del coche
	bool GetPrenderLuz2() { return prender2; }
	void PrenderLuz2(bool state) { prender2 = state; }

	//Funciones para que vuelvan las spotLights normales
	bool GetLucesSpothLights() { return luces; }
	void LucesSpothLights(bool state) { luces = state; }


	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLfloat muevex2;
	bool apagar = false;
	bool prender = false;
	bool prender2 = false;
	bool luces = false;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

