/*

GLEW is a cross platform open-source c/c++ extension loading library which provides run time mechanisims
for determining which OpenGL extensions are supported on the target platform.

This application demonstrates how to setup GLEW with GLFW and some basic usage

Introduction http://glew.sourceforge.net/index.html
Basic usage http://glew.sourceforge.net/basic.html

*/

#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

void CreateOpenGLRenderingContext();
int InitGLEW();
int main() {
	cout << "Hello GLEW" << endl;

	//To initialize GLEW you first must create a valid OpenGL rendering context (using GLFW) and then call glewInit();
	CreateOpenGLRenderingContext();

	if (!InitGLEW()) {
		return -1;
	}

	//Program returns successfully
	return 0;
}

void CreateOpenGLRenderingContext() {
	//Initilize OpenGL 
	glfwInit();
	//Create a glfw window handle
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello GLFW!", NULL, NULL);
	//Make the window's context the current one for this thread
	glfwMakeContextCurrent(window);
}

int InitGLEW() {
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << "glewInit failed" << glewGetErrorString(err) << endl;
		return 0;
	}
	cout << "Usign glew version: " << glewGetString(GLEW_VERSION)) << endl;

	return 1;
}