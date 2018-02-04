#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GLFW\glfw3.h>
#include <GL\glew.h>

using namespace std;

//Structure to hold the source code for a Vertex & Fragment shader source
struct ShaderProgramSource {
	string VertexSource;
	string FragmentSource;
};

static ShaderProgramSource ParseShader(const string& filepath);
static int createProgram(string vertexSource, string fragmentSource);
static int compileShader(const string sourceCode, unsigned int type);