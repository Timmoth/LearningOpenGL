#include <iostream>

#include <GLEW_Common.h>
#include <GLFW_Common.h>

using namespace std;

GLFWwindow *window;

void RenderLoop();

int main() {

	cout << "Multiple Textures" << endl;

	InitGLFW();
	window = CreateGLFWwindow("Multiple Textures", 640, 480);
	InitGLEW();

	RenderLoop();

	glfwTerminate();

	return 0;
}

void RenderLoop() {
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Render frames until the escape key is pressed
	do {

		glClear(GL_COLOR_BUFFER_BIT);




		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}