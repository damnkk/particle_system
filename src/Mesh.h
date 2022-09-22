#pragma once
#include<GL\glew.h>
#include"Shader.h"
#include<vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh
{
private:
	GLuint vbo, ebo;
	void setup();
public:
	GLuint vao;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	Mesh();
	Mesh(std::vector<float> v, std::vector<unsigned int> i);
	~Mesh();
	void draw();
};
