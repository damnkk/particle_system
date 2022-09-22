#include"Camera.h"

Camera::Camera(const int SCREENWIDTH, const int SCREENHEIGHT)
{
	aspect = SCREENWIDTH / SCREENHEIGHT;
}
Camera::Camera()
{
	position = { 0.0f, 0.0f, 50.0f };
	up = { 0.0f, 1.0f, 0.0f };
	direction = { 0.0f, 0.0f, -1.0f };
	_speed = 0.03f;
	pitch = 0.0f;
	yaw = 0.0f;
	fovy = 45.0f;
	_sensitivity = 0.025f;
}

glm::mat4 Camera::getViewMatrix(bool useEulerAngle)
{
	if (useEulerAngle)
	{
		direction.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		direction.y = sin(glm::radians(pitch));
		direction.z = -cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	}
	return glm::lookAt(position, position + direction, up);
}
glm::mat4 Camera::getProjectionMatrix(bool usePerspective)
{
	if (usePerspective)
	{
		return glm::perspective(glm::radians(fovy), aspect, zNear, zFar);
	}
	return glm::ortho(left, right, bottom, top, zNear, zFar);
}