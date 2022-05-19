#include "Camera.h"

Camera::Camera()
{
	m_identity = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 100.f);
	m_position = glm::vec3{ 0.0f };
	m_orientation = glm::vec3{ 0.0f };
}

Camera::Camera(glm::vec3 position, glm::vec3 orientation, float angle, glm::vec3 rotAxis, bool perspective)
{

	// Switch camera creation depending on whether perspective or orthographic
	if (perspective)
	{
		m_identity = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 100.f);
	}
	if (!perspective)
	{
		m_identity = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.0f, 1.0f);
	}

	// Set position and rotation
	m_position = position;
	m_orientation = orientation;

	// Update identity matrix with position and rotation
	m_identity = glm::translate(m_identity, m_position);
	m_identity = glm::rotate(m_identity, glm::radians(angle), rotAxis);
}


Camera::~Camera()
{

}