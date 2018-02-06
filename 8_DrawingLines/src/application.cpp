#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <GLEW_Common.h>
#include <GLFW_Common.h>
#include <ShaderLoader.h>

using namespace std;

GLFWwindow* window;

int main() {

	cout << "DrawingLines" << endl;

	InitGLFW();
	window = CreateGLFWwindow();
	InitGLEW();

	cin.get();
	glfwTerminate();
	return 0;
}