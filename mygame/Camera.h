#pragma once
#include "GameObject.h"
class Camera :	public GameObject
{
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 orientation, float angle, glm::vec3 rotAxis);
	~Camera();

	void SetProjection(glm::mat4 projection) { m_camera = projection; }
	void LookAtModel(glm::vec3 model);

	glm::mat4 GetProjection() { return m_camera; }
private:
	glm::mat4 m_camera;
};

