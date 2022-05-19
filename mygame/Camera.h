#pragma once
#include "GameObject.h"
class Camera :	public GameObject
{
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 orientation, float angle, glm::vec3 rotAxis, bool perspective);
	~Camera();

	void SetProjection(glm::mat4 projection) { m_identity = projection; }

	glm::mat4 GetProjection() { return m_identity; }
private:

};

