#include"Display.h"
#include"Particle.h"
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include<GL\glew.h>
#include<iostream>
#include<algorithm>


Display::Display()
{
	if (!glfwInit())
	{
		std::cerr << "cannot initialize glfw" << std::endl;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "particle_test", NULL, NULL);

	
	if (!window)
	{
		std::cerr << "ERROR:: connot open glfw window" << std::endl;
		glfwTerminate();
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	// Depth buffer enable
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Colour blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Interpolate

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	backgroundcColor = Color(0.0f, 0.0f, 0.0f, 1.0f);
}

Display::~Display()
{
	glfwTerminate();
}

GLFWwindow* Display::getWindow() const
{
	return window;
}

void Display::update(Shader shader, Camera& camera, double elapsedTime, std::vector<Particle>& particles,Mesh& mesh)
{
	glClearColor(backgroundcColor.r, backgroundcColor.g, backgroundcColor.b, backgroundcColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.useShader();

	camera._speed = 20 * static_cast<float> (elapsedTime);
	camera.aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	
	glm::mat4 view = camera.getViewMatrix(true);
	glm::mat4 projection = camera.getProjectionMatrix(true);

	std::sort(particles.begin(), particles.end(),
		[&camera](const Particle& lhs, const Particle& rhs)
		{
			return glm::length(camera.position - lhs.position) > glm::length(camera.position - rhs.position);
		});
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		shader.set4fv("newColour", glm::vec4(particles[i].color.r, particles[i].color.g, particles[i].color.b, particles[i].color.a));
		glm::mat4 mvp = projection* view*particles[i].model;

		shader.setMatrix4fv("mvp", mvp);

		Particle::draw(mesh);

		particles[i].update(elapsedTime);
	}
}

void Display::render()
{
	glfwPollEvents();
	glfwSwapBuffers(window);
}

void Display::setBackgroundColour(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
{
	backgroundcColor = { r, g, b, a };
}