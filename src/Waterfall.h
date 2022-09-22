#pragma once
#include<glm.hpp>

class Camera
{
private:
	glm::vec3 _position;
	glm::vec3 _up;					
	glm::vec3 _direction;			//朝向指针
	glm::mat4 _view;				//视图矩阵
	float _pitch;						//仰角
	float  _speed;						//(可能是移动速度)
	float _fov;							//视场角
	float _sensitivity;					//视角灵敏度

public:
	float DEFAULT_CAM_SPEED = 0.03f;
	float SHIFT_CAM_SPEED = 0.2f;
	Camera();
	~Camera() = default;
	void updateCameraView();
	void setViewDirection(glm::vec3 d);
	glm::vec3 getViewDirection() const;

	glm::vec3& position();
	glm::vec3& up();
	glm::vec3& direction();
	glm::mat4& view();
	float& pitch();
	float& yaw();
	float& speed();
	float& fov();
	float& sensitivity();
};