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

	if (!InitGLFW())
		return -1;

	if (!CreateGLFWwindow())
		return -1;

	RenderLoop();

	//Wait until the user hits enter at the console
	cin.get();

	//Terminate the GLFW library
	glfwTerminate();

	//Program returns successfully
	return 0;
}

int InitGLFW() {
	//Perform initialization checks to ensure hardware & software features are available on the machine
	if (!glfwInit()) {
		//Handle initialization failure
		cout << "Error initializing GLFW library" << endl;
		return 0;
	}

	return 1;
}

int CreateGLFWwindow(){
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