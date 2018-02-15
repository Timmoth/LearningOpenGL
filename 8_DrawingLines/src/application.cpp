#include <iostream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "GLEW_Common.h"
#include "GLFW_Common.h"
#include "ShaderLoader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "../headers/Rectangle.h"

using namespace std;

int width = 640, height = 480;
GLFWwindow* window;

vector<Rectangle> Rectangles;
unsigned int shaderProgram;


void RenderLoop();

int main() {

	cout << "Drawing Lines" << endl;

	InitGLFW();
	window = CreateGLFWwindow("Drawing Lines", width, height);
	InitGLEW();

	//Compile and link shaders into a program
	ShaderProgramSource shaderSource = ParseShader("./res/8_DrawingLines.shader");
	shaderProgram = createProgram(shaderSource.VertexSource, shaderSource.FragmentSource);
	//use the shader
	glUseProgram(shaderProgram);

	//Create the model view and projection matrices and initialise them to the identity matrix
	glm::mat4 View = glm::mat4(1.0f), Projection = glm::mat4(1.0f);

	Projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);

	unsigned int view = glGetUniformLocation(shaderProgram, "View");
	glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(View));

	unsigned int projection = glGetUniformLocation(shaderProgram, "Projection");
	glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(Projection));

	Rectangles.push_back(Rectangle(100.0f, 100.0f, 20.0f, 20.0f, 5.0f, shaderProgram));
	Rectangles.push_back(Rectangle(width /2, height /2, 20.0f, 60.0f, 2.0f, shaderProgram));

	Rectangles.push_back(Rectangle(100.0f, 100.0f, 40.0f, 40.0f, 4.0f, shaderProgram));
	Rectangles.push_back(Rectangle(200.0f, 100.0f, 20.0f, 20.0f, 4.0f, shaderProgram));

	RenderLoop();

	glfwTerminate();
	return 0;
}

float angle1 = 0.0f;
void RenderLoop() {
	//Set glfw to capture key's pressed
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Render frames until the escape key is pressed
	do {

		glClear(GL_COLOR_BUFFER_BIT);

		for (std::vector<Rectangle>::iterator it = Rectangles.begin(); it != Rectangles.end(); it++)
		{
			
			(*it).Render();
		
		}


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}



