#include <iostream>

#include <GLEW_Common.h>
#include <GLFW_Common.h>

#include "VertexBuffer.h"
#include <IndexBuffer.h>
#include <Shader.h>
#include <time.h> 
using namespace std;


GLFWwindow *window;
unsigned int VertexArrayObject;

Shader shader;
unsigned int TextureObject1;
unsigned int TextureObject2;

void RenderLoop();
void InitRender();
void generateTexture(int index);

int main() {

	cout << "Multiple Textures" << endl;

	InitGLFW();
	window = CreateGLFWwindow("Multiple Textures", 640, 480);
	InitGLEW();
	srand(time(NULL));
	InitRender();



	RenderLoop();

	glfwTerminate();

	return 0;
}

float vertexBufferData[] = {
	//X		 Y		Z	  R		G	 B
	-0.5f,  0.5f, 0.0f,	0.0f, 0.0f, // Top-left
	0.5f,  0.5f, 0.0f,	1.0f, 0.0f, // Top-right
	0.5f, -0.5f, 0.0f,	1.0f, 1.0f, // Bottom-right
	-0.5f, -0.5f, 0.0f,	0.0f, 1.0f  // Bottom-left
};

unsigned int elementBufferData[] = {
	0, 1, 2,
	2, 3, 0
};



void generateTexture(int index) {
	glBindTexture(GL_TEXTURE_2D, index);
	//Set the texture parameter to determine how the texture should be sampled outside of the coordinate range of 0 to 1
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width = 300;
	int height = 300;
	char* image = new char[3 * width * height];

	char r = (char)rand() % 255/(index+1);
	char g = (char)rand() % 255 / (index + 1);
	char b = (char)rand() % 255 / (index + 1);

	for (int i = 0; i < 3 * width * height; i += 3) {
		image[i] = r;
		image[i + 1] = g;
		image[i + 2] = b;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
}

unsigned int textures[2];

void InitRender() {
	shader = Shader("./res/9_MultipleTextures.shader");
	glUseProgram(shader.getID());

	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);

	VertexBuffer vertexBuffer = VertexBuffer(vertexBufferData, sizeof(vertexBufferData));
	IndexBuffer indexBuffer = IndexBuffer(elementBufferData, sizeof(elementBufferData));

	//Get the index of the position attribute
	unsigned int positionAttribute = glGetAttribLocation(shader.getID(), "position");
	//Specify how the data for the position attribute is retrieved from the array
	glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	//Enable the vertex attribute
	glEnableVertexAttribArray(positionAttribute);

	GLint texAttrib = glGetAttribLocation(shader.getID(), "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));



	glGenTextures(2, textures);
	glActiveTexture(GL_TEXTURE0);
	generateTexture(textures[0]);
	generateTexture(textures[1]);

}

void RenderLoop() {
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(255, 255, 255, 1);

	int i = 0;
	int di = 1;
	//Render frames until the escape key is pressed
	do {

		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		if (i > 100) {
			di = -1;
		}
		if (i <=0) {
			di = 1;
		}
		i += di;

		if (i > 50)
		{
			//glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textures[0]);
		}
		else
		{
			//glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
		}

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}