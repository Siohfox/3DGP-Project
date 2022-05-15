#include "Camera.h"

Camera::Camera()
{
	m_camera = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 100.f);
	m_position = glm::vec3{ 0.0f };
	m_orientation = glm::vec3{ 0.0f };
	m_identity = glm::mat4{ 1.0f };
}

Camera::Camera(glm::vec3 position, glm::vec3 orientation, float angle, glm::vec3 rotAxis)
{
	m_camera = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 100.f);
	m_position = position;
	m_orientation = orientation;
	m_identity = glm::mat4{ 1.0f };

	m_identity = glm::translate(m_identity, position);
	m_identity = glm::rotate(m_identity, angle, rotAxis);
}


Camera::~Camera()
{
}
