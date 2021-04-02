#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


Shader::Shader(const std::string& path)
	:filePath(path), rendererID(0)
{
	ShaderProgramSource source = ParseShader("resources/shaders/Basic.shader");
	rendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::Shader()
	:rendererID(0)
{

}

Shader::~Shader()
{
	glDeleteProgram(rendererID);
}

void Shader::Bind() const
{
	glUseProgram(rendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}



unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		std::cout << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	//TODO: error handling

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (uniformLocationCashe.find(name) != uniformLocationCashe.end()) 
	{
		return uniformLocationCashe[name];
	}
	int location = glGetUniformLocation(rendererID, name.c_str());
	if(location == -1)
	{
		std::cout << "Warning: uniform " <<name << "doesn't exist" << std::endl;
	}
	else 
	{
		uniformLocationCashe[name] = location;
	}
	return location;
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}