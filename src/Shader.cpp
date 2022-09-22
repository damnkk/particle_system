#include"Shader.h"
#include<fstream>
#include<iostream>
#include<gtc\type_ptr.hpp>


std::string readFile(std::string shaderPath)
{
	std::string res, line;
	std::fstream fin(shaderPath);
	if (!fin.is_open())
	{
		std::cerr << "ERROR:: open shader file fail" << std::endl;
		exit(-1);
	}
	while (std::getline(fin, line))
	{
		res += line + '\n';
	}
	fin.close();
	return res;
}

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
{
	const std::string vshader = readFile(vertexShader);
	const std::string fshader = readFile(fragmentShader);
	const char* vPointer = vshader.c_str();
	const char* fPointer = fshader.c_str();

	GLint success;

	GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObject, 1, (const GLchar**)(&vPointer), NULL);
	glCompileShader(vertexShaderObject);
	glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cerr << "ERROR: vertex shader compile fail" << std::endl;
		exit(-1);
	}
	GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderObject, 1, (const GLchar**)(&fPointer), NULL);
	glCompileShader(fragmentShaderObject);
	glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cerr << "ERROR: fragment shader compile fail" << std::endl;
		exit(-1);
	}

	std::cout << "Vertex Shader:\n" << vshader << "\n\n";
	std::cout << "Fragment Shader:\n" << fshader << "\n\n";

	program = glCreateProgram();
	glAttachShader(program, vertexShaderObject);
	glAttachShader(program, fragmentShaderObject);
	glLinkProgram(program);
	glDeleteShader(vertexShaderObject);
	glDeleteShader(fragmentShaderObject);
}

Shader::~Shader()
{
	glDeleteProgram(program);
}
void Shader::useShader()
{
	glUseProgram(program);
}

GLuint Shader::getProgram() const
{
	return program;
}

void Shader::setMatrix4fv(const char* name, glm::mat4 value)
{
	int location = glGetUniformLocation(program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set4fv(const char* name, glm::vec4 value)
{
	int location = glGetUniformLocation(program, name);
	//glUniform4f(location, value[0], value[1], value[2], value[3]);
	glUniform4fv(location, 1, glm::value_ptr(value));
}
