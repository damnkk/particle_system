#pragma once

#include<GL\glew.h>
#include<string>
#include<glm.hpp>
#include<fstream>

class Shader
{
private:
	GLuint program;

public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();
	void useShader();
	GLuint getProgram() const;

	void setMatrix4fv(const char* name, glm::mat4 value);
	void set4fv(const char* name, glm::vec4 value);
};
