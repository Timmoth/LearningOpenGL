#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

using namespace glm;

class Line {
private:
	unsigned int RenderID;
	unsigned int ShaderProgramID;
	mat4 ModelMatrx;
public:
	Line(float x1, float y1, float x2, float y2, float thickness, unsigned int shaderProgram);
	void Render();
};