#pragma once

#include <GL\glew.h>

class VertexBuffer
{
private:
	unsigned int m_RendererID;

public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();
	~VertexBuffer();

	void bind() const;
	void unbind() const;
};