#include "../Headers/GLFW_Common.h"

using namespace std;

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

GLFWwindow* CreateGLFWwindow() {

	cout << "Creating the OpenGL Context" << endl;

	//Attempt to create a handle to a OpenGL context
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello GLFW!", NULL, NULL);

	if (!window) {
		cout << "Could not create OpenGL Window" << endl;
		//free any allocated resources
		glfwTerminate();
		return NULL;
	}

	//Make the window's context the current one for this thread
	glfwMakeContextCurrent(window);

	return window;
}