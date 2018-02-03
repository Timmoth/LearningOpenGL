#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "GLEW_Common.h"
#include "GLFW_Common.h"

using namespace std;

int main() {

	cout << "Hello Shaders" << endl;

	InitGLFW();

	CreateGLFWwindow();

	InitGLEW();

	cin.get();

	return 0;
}