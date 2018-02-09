#include "../headers/Line.h"

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

Line::Line(float x1, float y1, float x2, float y2, float thickness, unsigned int shaderProgram) {
	ShaderProgramID = shaderProgram;

	//Generate the vertex array object and make it the active array buffer
	glGenVertexArrays(1, &RenderID);
	glBindVertexArray(RenderID);

	VertexBuffer vertexBufferObject = VertexBuffer(vertexBufferData, sizeof(vertexBufferData));
	IndexBuffer indexBufferObject = IndexBuffer(elementBufferData, 6);

	//Get the index of the position attribute
	unsigned int positionAttribute = glGetAttribLocation(ShaderProgramID, "position");
	//Specify how the data for the position attribute is retrieved from the array
	glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//Enable the vertex attribute
	glEnableVertexAttribArray(positionAttribute);

	//Get the index of the color attribute
	unsigned int colorAttribute = glGetAttribLocation(ShaderProgramID, "color");
	//Specify how the data for the position attribute is retrieved from the array
	glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//Enable the vertex attribute
	glEnableVertexAttribArray(colorAttribute);

	float dx = x2 - x1;
	float dy = y2 - y1;
	float length = sqrt(dx * dx + dy * dy);
	float angle = atan2(dy, dx);

	ModelMatrx = mat4(1.0f);

	ModelMatrx = translate(ModelMatrx, vec3(x1, y1 , 0.0f));
	ModelMatrx = rotate(ModelMatrx, angle, vec3(0.0, 0.0, 1.0));
	ModelMatrx = scale(ModelMatrx, vec3(length, thickness, 1.0f));

	glBindVertexArray(0);
}

void Line::Render() {
	glBindVertexArray(RenderID);
	unsigned int model = glGetUniformLocation(ShaderProgramID, "Model");
	glUniformMatrix4fv(model, 1, GL_FALSE, value_ptr(ModelMatrx));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}