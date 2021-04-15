#pragma once
#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include <glm.hpp>
#include "gtc/matrix_transform.hpp"
#include "Camera.h"

class Renderer 
{
public:
	Renderer();
	Renderer(float width, float height);
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

	Camera camera;

	float width;
	float height;

	glm::vec3 ambientLightColor = glm::vec3(1, 1, 0.75f);
	float ambientStrength = 0.5f;
};