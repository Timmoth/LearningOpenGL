#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

//Structure to hold the source code for a Vertex & Fragment shader source
struct ShaderProgramSource {
	string VertexSource;
	string FragmentSource;
};

ShaderProgramSource ParseShader(const string& filepath);
int createProgram(string vertexSource, string fragmentSource);
int compileShader(const string sourceCode, unsigned int type);