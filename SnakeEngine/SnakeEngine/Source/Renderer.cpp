#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length,
	const GLchar* msg, const void* data)
{
	const char* _source;
	const char* _type;
	const char* _severity;

	switch (source) {
	case GL_DEBUG_SOURCE_API:
		_source = "API";
		break;

	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		_source = "WINDOW SYSTEM";
		break;

	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		_source = "SHADER COMPILER";
		break;

	case GL_DEBUG_SOURCE_THIRD_PARTY:
		_source = "THIRD PARTY";
		break;

	case GL_DEBUG_SOURCE_APPLICATION:
		_source = "APPLICATION";
		break;

	case GL_DEBUG_SOURCE_OTHER:
		_source = "UNKNOWN";
		break;

	default:
		_source = "UNKNOWN";
		break;
	}

	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		_type = "ERROR";
		break;

	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		_type = "DEPRECATED BEHAVIOR";
		break;

	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		_type = "UDEFINED BEHAVIOR";
		break;

	case GL_DEBUG_TYPE_PORTABILITY:
		_type = "PORTABILITY";
		break;

	case GL_DEBUG_TYPE_PERFORMANCE:
		_type = "PERFORMANCE";
		break;

	case GL_DEBUG_TYPE_OTHER:
		_type = "OTHER";
		break;

	case GL_DEBUG_TYPE_MARKER:
		_type = "MARKER";
		break;

	default:
		_type = "UNKNOWN";
		break;
	}

	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:
		_severity = "HIGH";
		break;

	case GL_DEBUG_SEVERITY_MEDIUM:
		_severity = "MEDIUM";
		break;

	case GL_DEBUG_SEVERITY_LOW:
		_severity = "LOW";
		break;

	case GL_DEBUG_SEVERITY_NOTIFICATION:
		_severity = "NOTIFICATION";
		break;

	default:
		_severity = "UNKNOWN";
		break;
	}

	printf("Error id = %d, Error type = %s, Error severity = %s, raised from %s: %s\n",
		id, _type, _severity, _source, msg);
};


Renderer::Renderer()
{
}

Renderer::Renderer(float w, float h)
{
	width = w;
	height = h;
}

Renderer::~Renderer()
{
}

void Renderer::Start()
{

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDisable(GL_DEPTH_TEST);
	glDebugMessageCallback(GLDebugMessageCallback, 0);

	std::cout << "openGL version " << glGetString(GL_VERSION) << std::endl;

	glm::vec3 cubee[] =
	{
	glm::vec3(-1, -1, -1),
	glm::vec3(1, -1, -1),
	glm::vec3(1, 1, -1),
	glm::vec3(-1, 1, -1),
	glm::vec3(-1, -1, 1),
	glm::vec3(1, -1, 1),
	glm::vec3(1, 1, 1),
	glm::vec3(-1, 1, 1)
	};
	float cube[] =
	{
	-0.5,-0.5,-0.5,
	0.5,-0.5,-0.5,
	0.5,0.5,-0.5,
	-0.5,0.5,-0.5,
	-0.5,-0.5,0.5,
	0.5,-0.5,0.5,
	0.5,0.5,0.5,
	-0.5,0.5,0.5

	};
	
	unsigned int cubeIndices[] =
	{
	0, 1, 3, 3, 1, 2,
	1, 5, 2, 2, 5, 6,
	5, 4, 6, 6, 4, 7,
	4, 0, 7, 7, 0, 3,
	3, 2, 7, 7, 2, 6,
	4, 5, 0, 0, 5, 1
	};


	vb = new VertexBuffer(cubee, 8 * 3 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	va.AddBuffer(*vb, layout);

	ib = new IndexBuffer(cubeIndices, 36);
	
	shader = new Shader("resources/shaders/Basic.shader");
	shader->Bind();

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(1.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(5, 5, 5));

	camera = Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0),width,height,90);

	shader->SetUniform4x4f("model", trans);
	shader->SetUniform4x4f("view", camera.GetLookAt());
	shader->SetUniform4x4f("projection", camera.GetProjectionMatrix());
	shader->SetUniform4f("u_Color", 1.0f, 0.5f, 0.0f, 1.0f);
	shader->SetUniformVec3("ambientLightColor", ambientLightColor);
	shader->SetUniformFloat("ambientLightStrength", ambientStrength);

	
	va.Unbind();
	shader->Unbind();
	vb->Unbind();
	ib->Unbind();
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{

	shader.Bind();

	va.Bind();
	ib.Bind();
	//Render here
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);


}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render()
{
	Clear();
	shader->Bind();
	shader->SetUniform4x4f("view", camera.GetLookAt());
	Draw(va, *ib, *shader);
}


