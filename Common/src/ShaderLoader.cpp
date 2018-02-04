#include "../Headers/ShaderLoader.h"

//Take the filepath of the shader sourcecode file and parse it into a ShaderProgramSource
ShaderProgramSource ParseShader(const string& filepath) {
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

int createProgram(string vertexSource, string fragmentSource) {
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

int compileShader(const string sourceCode, unsigned int type) {
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