#pragma once
#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class Renderer 
{
public:
	Renderer();
	~Renderer();

	void Render();
	void Start();
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Clear();
private:


	Shader* shader;
	VertexBuffer* vb;
	IndexBuffer* ib;

	VertexArray va;
};