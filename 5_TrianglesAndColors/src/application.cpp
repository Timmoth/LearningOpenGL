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
	//X		 Y		Z	  R		G	 B
	-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Top-left
	 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Top-right
	 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-right
	-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f  // Bottom-left
};

unsigned int vertexElementData[] = {
	0, 1, 2,
	2, 3, 0
};

void RenderLoop();

int main() {

	cout << "Triangles and Colors" << endl;

	InitGLFW();
	window = CreateGLFWwindow();
	InitGLEW();

	//Generate the vertex array object and make it the active array buffer
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//Generate Vertex Buffer object and make it the active vertex buffer
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	//Copy the vertex data to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	//Generate vertex element buffer and make it the active element buffer
	glGenBuffers(1, &vertexElementObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexElementObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexElementData), vertexElementData, GL_STATIC_DRAW);


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


		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}