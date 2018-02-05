#include <iostream>

#include "GLEW_Common.h"
#include "GLFW_Common.h"
#include "ShaderLoader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;

GLFWwindow* window;
unsigned int shaderProgram;
unsigned int arrayBufferObject;
unsigned int textureBufferObject;
VertexBuffer vertexBufferObject;
IndexBuffer indexBufferObject;

float vertexBufferData[] = {
	//X		 Y		Z	  R		G	 B
	-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Top-left
	0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // Top-right
	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Bottom-right
	-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,	0.0f, 1.0f  // Bottom-left
};

unsigned int elementBufferData[] = {
	0, 1, 2,
	2, 3, 0
};

void RenderLoop();

int main() {

	cout << "Textures" << endl;
	InitGLFW();
	window = CreateGLFWwindow();
	InitGLEW();

	//Compile and link shaders into a program
	ShaderProgramSource shaderSource = ParseShader("./res/7_Transformations.shader");
	shaderProgram = createProgram(shaderSource.VertexSource, shaderSource.FragmentSource);
	glUseProgram(shaderProgram);

	glGenVertexArrays(1, &arrayBufferObject);
	glBindVertexArray(arrayBufferObject);

	vertexBufferObject = VertexBuffer(vertexBufferData, sizeof(vertexBufferData));
	indexBufferObject = IndexBuffer(elementBufferData, 6);

	//Generate texture buffer object and bind as active texture buffer
	glGenTextures(1, &textureBufferObject);
	glBindTexture(GL_TEXTURE_2D, textureBufferObject);
	//Set the texture parameter to determine how the texture should be sampled outside of the coordinate range of 0 to 1
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Specify what happens when a texture is stretched
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	int width = 720;
	int height = 960;
	unsigned char* image =
		SOIL_load_image("./res/dexter.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);


	//Get the index of the position attribute
	unsigned int positionAttribute = glGetAttribLocation(shaderProgram, "position");
	//Specify how the data for the position attribute is retrieved from the array
	glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	//Enable the vertex attribute
	glEnableVertexAttribArray(positionAttribute);

	//Get the index of the color attribute
	unsigned int colorAttribute = glGetAttribLocation(shaderProgram, "color");
	//Specify how the data for the position attribute is retrieved from the array
	glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//Enable the vertex attribute
	glEnableVertexAttribArray(colorAttribute);


	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));




	RenderLoop();

	glfwTerminate();

	return 0;
}

float rotation = 0.0f;

void RenderLoop() {
	//Set glfw to capture key's pressed
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Render frames until the escape key is pressed
	do {

		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, glm::radians(rotation+= 0.1f), glm::vec3(0.0, 0.0, 1.0));

		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}