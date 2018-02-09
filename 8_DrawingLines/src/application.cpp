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

using namespace std;

int width = 640, height = 480;
GLFWwindow* window;
unsigned int line1VAO;
unsigned int line2VAO;

struct LineModel {
	unsigned int ModelID;
	glm::mat4 ModelMatrix;
};

vector<LineModel> lines;

LineModel CreateLine(float x1, float y1, float x2, float y2, float thickness);

VertexBuffer vertexBufferObject;
IndexBuffer indexBufferObject;
unsigned int shaderProgram;


float vertexBufferData[] = {
	//X		 Y		Z	  R		G	 B
	0.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Top-left
	1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Top-right
	1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
	0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f  // Bottom-left
};

unsigned int elementBufferData[] = {
	0, 1, 2,
	2, 3, 0
};



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

	lines.push_back(CreateLine(40.0f, 40.0f, 100.0f, 40.0f, 4.0f));
	lines.push_back(CreateLine(100.0f, 40.0f, 100.0f, 100.0f, 4.0f));
	lines.push_back(CreateLine(100.0f, 100.0f, 40.0f, 100.0f, 4.0f));
	lines.push_back(CreateLine(40.0f, 100.0f, 40.0f, 40.0f, 4.0f));

	RenderLoop();

	glfwTerminate();
	return 0;
}

float angle = 0.0f;
void RenderLoop() {
	//Set glfw to capture key's pressed
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Render frames until the escape key is pressed
	do {
		glClear(GL_COLOR_BUFFER_BIT);

		for (std::vector<LineModel>::iterator it = lines.begin(); it != lines.end(); it++)
		{
			glBindVertexArray((*it).ModelID);
			unsigned int model = glGetUniformLocation(shaderProgram, "Model");
			glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr((*it).ModelMatrix));

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}

LineModel CreateLine(float x1, float y1, float x2, float y2, float thickness) {
	unsigned int vertexArrayObject;

	//Generate the vertex array object and make it the active array buffer
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	vertexBufferObject = VertexBuffer(vertexBufferData, sizeof(vertexBufferData));
	indexBufferObject = IndexBuffer(elementBufferData, 6);

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

	float dx = x2 - x1;
	float dy = y2 - y1;
	float length = sqrt(dx * dx + dy * dy);
	float angle = atan2(dy, dx);

	glm::mat4 Model = glm::mat4(1.0f);

	Model = glm::translate(Model, glm::vec3(x1 , y1 , 0.0f));
	Model = glm::rotate(Model, angle, glm::vec3(0.0, 0.0, 1.0));
	Model = glm::scale(Model, glm::vec3(length, thickness, 1.0f));

	LineModel lineModel;
	lineModel.ModelID = vertexArrayObject;
	lineModel.ModelMatrix = Model;

	glBindVertexArray(0);

	return lineModel;
}






