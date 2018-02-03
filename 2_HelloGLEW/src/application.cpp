/*

GLEW is a cross platform open-source c/c++ extension loading library which provides run time mechanisims
for determining which OpenGL extensions are supported on the target platform.

This application demonstrates how to setup GLEW with GLFW and some basic usage

Introduction http://glew.sourceforge.net/index.html
Basic usage http://glew.sourceforge.net/basic.html

Bellow are the Visual studio Configuration properties needed to link GLFW and GLEW into our project
All Configurations All Platforms:
*Set the output & intermediate directories to a path relative to the solution directory as to not clutter the project directories*
	General
		Output Directory						$(SolutionDir)bin\$(Platform)\$(Configuration)
		Intermediate Directory					$(SolutionDir)bin\intermediates\$(Platform)\$(Configuration)

*Include GLFW & GLEW header files*
	C++->General
		Additional Include Directories			$(SolutionDir)dependencies\GLFW\include;
												$(SolutionDir)dependencies\GLEW\include

*Tell the linker where GLFW & GLEW object files are located*
	Linker->General
		Additional Using Directories			$(SolutionDir)dependencies\GLFW\lib\$(Configuration)\$(PlatformTarget);
												$(SolutionDir)dependencies\GLEW\lib\$(Configuration)\$(PlatformTarget)
												
*Tell the linker which additional object files are being used*
	Linker->Input
		Additional Dependencies					opengl32.lib
												glfw3.lib

*A command to copy GLEW's DLL into the output directory*
	Build Events
		Post-Build Event						xcopy /y /d "$(SolutionDir)dependencies\GLEW\bin\$(Configuration)\$(PlatformTarget)\*.dll" "$(OutDir)"

*GLEW has different object files for debug and release*
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