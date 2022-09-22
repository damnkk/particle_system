#pragma once
#include"Shader.h"
#include"Camera.h"
#include"Particle.h"
#include<GLFW\glfw3.h>
#include<glm.hpp>
#include<vector>

class Display
{
private:
	const float SCREEN_HEIGHT = 720.f;
	const float SCREEN_WIDTH = 1280.0f;
	GLFWwindow* window;
	Color backgroundcColor;
public:
	Display();
	~Display();
	GLFWwindow* getWindow() const;
	void update(Shader shader, Camera& camera, double elapsedTime, std::vector<Particle>& particles,Mesh& mesh);
	void render();
	void setBackgroundColour(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
};
