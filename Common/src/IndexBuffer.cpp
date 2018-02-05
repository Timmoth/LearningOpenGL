#pragma once
#include "../Headers/IndexBuffer.h"

IndexBuffer::IndexBuffer() {}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count) {
	//Generate the id for this VertexBuffer object
	glGenBuffers(1, &m_RendererID);

	//Select the newly generated buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

	//Set the layout of the buffer data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

}

IndexBuffer::~IndexBuffer() {
	//glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}