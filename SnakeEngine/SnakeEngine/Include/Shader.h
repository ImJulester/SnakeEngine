#pragma once
#include <string>
#include "GL/glew.h"
#include <unordered_map>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader 
{
public:

	Shader(const std::string& filepath);
	Shader();
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform4x4f(const std::string& name, glm::mat4);
	void SetUniformFloat(const std::string& name, float);
	void SetUniformVec3(const std::string& name, glm::vec3);
private: 

	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource ParseShader(const std::string& filepath);

	int GetUniformLocation(const std::string& name);

	unsigned int rendererID = 0;
	std::string filePath;

	std::unordered_map<std::string, int> uniformLocationCashe;
};