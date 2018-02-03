/*

GLEW is a cross platform open-source c/c++ extension loading library which provides run time mechanisims
for determining which OpenGL extensions are supported on the target platform.

This application demonstrates how to setup GLEW with GLFW and some basic usage

Introduction http://glew.sourceforge.net/index.html
Basic usage http://glew.sourceforge.net/basic.html

Bellow are the Visual studio Configuration properties needed to link GLFW and GLEW into our project
All Configurations All Platforms:

General
	Output Directory						$(SolutionDir)bin\$(Platform)\$(Configuration)
	Intermediate Directory					$(SolutionDir)bin\intermediates\$(Platform)\$(Configuration)

C++->General
	Additional Include Directories			$(SolutionDir)dependencies\GLFW\include;
											$(SolutionDir)dependencies\GLEW\include

Linker->General
	Additional Using Directories			$(SolutionDir)dependencies\GLFW\lib\$(Configuration)\$(PlatformTarget);
											$(SolutionDir)dependencies\GLEW\lib\$(Configuration)\$(PlatformTarget)

Linker->Input
	Additional Dependencies					opengl32.lib
											glfw3.lib

Build Events
	Post-Build Event						xcopy /y /d "$(SolutionDir)dependencies\GLEW\bin\$(Configuration)\$(PlatformTarget)\*.dll" "$(OutDir)"


Debug All Platforms
Linker->Input
	Additional Dependencies					glew32d.lib

Release All Platforms
Linker->Input
	Additional Dependencies					glew32.lib
*/

#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

int initGLFW();
int initGLEW();
void terminate();
GLFWwindow* window;

int main() {

	cout << "Hello Triangles" << endl;

	if (!initGLFW()) {
		return -1;
	}

	if (!initGLEW()) {
		terminate();
		return -1;
	}


	terminate();
	return 0;
}

int initGLFW() {
	cout << "Initializing GLFW" << endl;
	if (!glfwInit()) {
		cout << "Failed to init GLFW" << endl;
		return 0;
	}

	window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
	if (!window) {
		cout << "Failed to create GLFW context" << endl;
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);

	return 1;
}

int initGLEW() {

	cout << "Initializing GLEW" << endl;

	if (glewInit() != GLEW_OK) {
		cout << "Glew init failed" << endl;
		return 0;
	}

	cout << "Usign glew version: " << glewGetString(GLEW_VERSION) << endl;
	return 1;
}

void terminate() {
	cout << "Terminating press enter to exit" << endl;
	cin.get();
	glfwTerminate();
}