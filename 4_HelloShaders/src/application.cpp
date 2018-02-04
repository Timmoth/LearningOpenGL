#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "GLEW_Common.h"
#include "GLFW_Common.h"

using namespace std;

//Structure to hold the source code for a Vertex & Fragment shader source
struct ShaderProgramSource {
	string VertexSource;
	string FragmentSource;
};

GLFWwindow* window;
unsigned int shaderProgram;

static ShaderProgramSource ParseShader(const string& filepath);
static int createProgram(string vertexSource, string fragmentSource);
static int compileShader(const string sourceCode, unsigned int type);
void RenderLoop();

int main() {

	cout << "Hello Shaders" << endl;

	InitGLFW();

	window = CreateGLFWwindow();

	InitGLEW();

	ShaderProgramSource shaderSource = ParseShader("Basic.shader");
	shaderProgram = createProgram(shaderSource.VertexSource, shaderSource.FragmentSource);

	RenderLoop();

	cin.get();

	return 0;
}

void RenderLoop() {
	//Set glfw to capture key's pressed
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Render frames until the escape key is pressed
	do {

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}

//Take the filepath of the shader sourcecode file and parse it into a ShaderProgramSource
static ShaderProgramSource ParseShader(const string& filepath) {
	ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;

	string line;
	stringstream ss[2];
	while (getline(stream, line)) {
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment")) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

static int createProgram(string vertexSource, string fragmentSource) {
	//Create a new program and get its ID
	unsigned int program = glCreateProgram();
	//Compile the VertexShader source and get the ID of the shader
	unsigned int vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
	//Compile the Fragment source and get the ID of the shader
	unsigned int fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

	//Attatch the shaders to the program ID
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	//Link the program
	glLinkProgram(program);

	//Check for errors in the program
	glValidateProgram(program);
	//Free shader resources
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//Return compiled program's ID
	return program;
}

static int compileShader(const string sourceCode, unsigned int type) {
	//Create a shader object and get its ID
	unsigned int id = glCreateShader(type);
	//Convert the sourcecode String to a char array
	const char* source = sourceCode.c_str();

	//Set the shader source code data
	glShaderSource(id, 1, &source, nullptr);
	//Compile the shader
	glCompileShader(id);

	//Check for compilation errors
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char *)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << message << endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}