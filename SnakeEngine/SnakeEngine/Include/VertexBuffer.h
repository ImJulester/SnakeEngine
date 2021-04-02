#pragma once

class VertexBuffer 
{
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;



private:
	unsigned int renderID;

};