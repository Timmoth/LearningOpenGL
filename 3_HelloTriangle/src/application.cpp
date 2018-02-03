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
void CreateTriangleVertexArrayObject();
void CreateTriangleVertexBuffer();
void RenderLoop();
void terminate();

GLFWwindow* window;

//Id of the vertex array object
unsigned int triangleVertexArrayID;

//ID of the vertex buffer object;
unsigned int triangleVertexBufferID;

//Vertex buffer data - the coordinates of the points of the triangle
//Coordinates are in screen coordinates: floats from -1.0f to 1.0f in the X,Y and Z plane
const float triangleVertexBuffer[] = {
	//Coordinates	  X		 Y	  Z
				   -1.0f, -1.0f, 0.0f,	//Vertex 0
					1.0f, -1.0f, 0.0f,	//Vertex 1
					0.0f,  1.0f, 0.0f	//Vertex 2
};

int main() {

	cout << "Hello Triangles" << endl;

	if (!initGLFW()) {
		return -1;
	}

	if (!initGLEW()) {
		terminate();
		return -1;
	}

	CreateTriangleVertexArrayObject();
	CreateTriangleVertexBuffer();

	RenderLoop();

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

	cout << "Using glew version: " << glewGetString(GLEW_VERSION) << endl;
	return 1;
}

void terminate() {
	cout << "Terminating press enter to exit" << endl;
	cin.get();
	glfwTerminate();
}

void CreateTriangleVertexArrayObject() {
	//Generate a vertex array object and get it's ID in triangleVertexArrayID
	glGenVertexArrays(1, &triangleVertexArrayID);
	//Bind the newly created vertex array object
	glBindVertexArray(triangleVertexArrayID);
}

void CreateTriangleVertexBuffer() {
	//Generate a vertex buffer object and get a reference to it
	glGenBuffers(1, &triangleVertexBufferID);
	//Bind the Vertex Buffer object
	glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBufferID);
	//Load the vertex buffer data into the bound vertex buffer object
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(triangleVertexBuffer), 
		triangleVertexBuffer,
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

}

void RenderLoop() {
	//Set glfw to capture key's pressed
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Render frames until the escape key is pressed
	do {
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}