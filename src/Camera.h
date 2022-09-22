#pragma once
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>



class Camera
{
public:
	glm::vec3 position = glm::vec3(0);
	glm::vec3 direction = glm::vec3(0, 0, -1);
	glm::vec3 up = glm::vec3(0, 1, 0);
	float pitch = 0.0f, yaw = 0.0f, roll = 0.0f;
	float fovy = 70.0f, zNear = 0.01, zFar = 1000, aspect = 1.0f;
	float left = -1.0, right = 1.0, top = 1.0, bottom = -1.0;
	float _speed, _sensitivity;
	float DEFAULT_CAM_SPEED = 0.03f;
	float SHIFT_CAM_SPEED = 0.2f;
	Camera() ;

	Camera(const int SCREENWIDTH, const int SCREENHEIGHT);

	glm::mat4 getViewMatrix(bool useEularAngle = true);
	glm::mat4 getProjectionMatrix(bool usePerspective = true);

	glm::vec3 getViewDirection() const;
};
