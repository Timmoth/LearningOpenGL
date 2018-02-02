/*
GLFW is a free open source multiplatform library for OpenGL which provides a platform independent
API for creating Windows, Contexts, Surfaces and handling input and events.

This project demonstrates the initialization and basic usage of the library 
Introduction http://www.glfw.org/docs/latest/index.html
Documentation http://www.glfw.org/documentation.html
*/


//Include iostream which contains the code needed to use cout
#include <iostream>
//Include the GLFW library
#include <GLFW\glfw3.h>

using namespace std;

//A handle to the OpenGL context
GLFWwindow* window;

//Forward decleration of the functions
int InitGLFW();
int CreateGLFWwindow();
void RenderLoop();

//Program entry point
int main() {

	//Output application title to the console
	cout << "HelloGLFW" << endl;

	//Initilize the GLFW Library
	if (!InitGLFW())
		return -1; //Exit if returns an error

	//Create the OpenGL Context 
	if (!CreateGLFWwindow())//Exit if an error has been returned
		return -1;

	//All the drawing is done here
	RenderLoop();

	//Wait until the user hits enter at the console
	cin.get();

	//Terminate the GLFW library
	glfwTerminate();

	//Program returns successfully
	return 0;
}

int InitGLFW() {

	cout << "Initializing GLFW library" << endl;

	//Perform initialization checks to ensure hardware & software features are available on the machine
	if (!glfwInit()) {

		//Handle initialization failure
		cout << "Error initializing GLFW library" << endl;
		return 0;

	}

	return 1;
}

int CreateGLFWwindow(){

	cout << "Creating the OpenGL Context" << endl;

	//Attempt to create a handle to a OpenGL context
	window = glfwCreateWindow(640, 480, "Hello GLFW!", NULL, NULL);

	if (!window) {
		cout << "Could not create OpenGL Window" << endl;
		//free any allocated resources
		glfwTerminate();
		return 0;
	}

	//Make the window's context the current one for this thread
	glfwMakeContextCurrent(window);

	return 1;
}

void RenderLoop() {

	cout << "Entering render loop" << endl;

	//Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}
}