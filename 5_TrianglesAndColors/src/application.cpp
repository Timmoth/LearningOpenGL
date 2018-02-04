#include <iostream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "GLEW_Common.h"
#include "GLFW_Common.h"
#include "ShaderLoader.h"

using namespace std;

GLFWwindow* window;
unsigned int vertexArrayObject;
unsigned int vertexBufferObject;
unsigned int vertexElementObject;
unsigned int shaderProgram;

float vertexBufferData[] = {
			//	  X		   Y		 Z			 R		  G		  B
				0.0f,	 0.5f,		0.0f,		1.0f,	0.0f,	0.0f,
				0.5f,	-0.5f,		0.0f,		0.0f,	1.0f,	0.0f,
				-0.5f,	-0.5f,		0.0f,		0.0f,	0.0f,	1.0f
};

unsigned int vertexElementData[] = {
	0
};

void RenderLoop();

int main() {

	cout << "Triangles and Colors" << endl;

	InitGLFW();
	window = CreateGLFWwindow();
	InitGLEW();

	//Generate the vertex array object and make it the active vertex array
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//Generate Vertex Buffer object and make it the active array buffer
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	//Copy the vertex data to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	//Compile and link shaders into a program
	ShaderProgramSource shaderSource = ParseShader("./5_TrianglesAndColors.shader");
	shaderProgram = createProgram(shaderSource.VertexSource, shaderSource.FragmentSource);
	//use the shader
	glUseProgram(shaderProgram);

	//Get the index of the position attribute
	unsigned int positionAttribute = glGetAttribLocation(shaderProgram, "position");
	//Specify how the data for the position attribute is retrieved from the array
	glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//Enable the vertex attribute
	glEnableVertexAttribArray(positionAttribute);

	//Get the index of the color attribute
	unsigned int colorAttribute = glGetAttribLocation(shaderProgram, "color");
	//Specify how the data for the position attribute is retrieved from the array
	glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//Enable the vertex attribute
	glEnableVertexAttribArray(colorAttribute);

	RenderLoop();

	glfwTerminate();
	return 0;
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