#include <iostream>

#include "GLEW_Common.h"
#include "GLFW_Common.h"


using namespace std;

GLFWwindow* window;

int main() {

	cout << "Textures" << endl;
	InitGLFW();
	window = CreateGLFWwindow();
	InitGLEW();

	cin.get();

	glfwTerminate();
	return 0;
}