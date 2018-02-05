#pragma once
#include "../Headers/VertexBuffer.h"

VertexBuffer::VertexBuffer() {}
VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	//Generate the id for this VertexBuffer object
	glGenBuffers(1, &m_RendererID);

	//Select the newly generated buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

	//Set the layout of the buffer data
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	//glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}