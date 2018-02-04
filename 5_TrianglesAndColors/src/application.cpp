#include <iostream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "GLEW_Common.h"
#include "GLFW_Common.h"

using namespace std;

int main() {

	cout << "Triangles and Colors" << endl;

	InitGLFW();
	InitGLEW();
	CreateGLFWwindow();

	cin.get();

	glfwTerminate();
	return 0;
}