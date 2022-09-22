#pragma once
#include"Display.h"
#include<iostream>

namespace InputManager
{
	void processKeyPress(GLFWwindow* window, Camera& camera)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			camera._speed = camera.SHIFT_CAM_SPEED;
		}
		else
		{
			camera._speed = camera.DEFAULT_CAM_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.position += camera._speed * camera.direction;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.position -= camera._speed * camera.direction;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.position -= glm::cross(camera.direction, camera.up) * camera._speed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.position += glm::cross(camera.direction, camera.up) * camera._speed;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			camera.pitch = 0.0f;
			camera.yaw = 0.0f;
			camera.position = glm::vec3(0);
			camera.direction = glm::vec3(0, 0, -1);
		}

	}
	void processMouseMove(GLFWwindow* window, double x, double y, double oldX, double oldY, Camera& camera)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			glm::vec2 offset = glm::vec2(x, y) - glm::vec2(oldX, oldY);
			offset *= camera._sensitivity;
			camera.yaw += offset.x;
			camera.pitch -= offset.y;
			camera.yaw = glm::mod(camera.yaw + 180.0f, 360.0f) - 180.0f;
			camera.pitch = glm::clamp(camera.pitch, -89.0f, 89.0f);
		}
	}

}
