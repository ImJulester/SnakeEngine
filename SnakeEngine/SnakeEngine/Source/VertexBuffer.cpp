#include "VertexBuffer.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &renderID);
	glBindBuffer(GL_ARRAY_BUFFER, renderID);
	glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer()
{
	renderID = 0;
	
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &renderID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, renderID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
