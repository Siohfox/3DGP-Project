#include "GameObject.h"

void GameObject::TranslateObject(glm::vec3 translation)
{
	m_identity = glm::translate(m_identity, translation);
	m_position += translation;
}

void GameObject::RotateObject(float angle, glm::vec3 rotAxis)
{
	m_identity = glm::rotate(m_identity, glm::radians(angle), rotAxis);
	m_orientation += angle;
}

void GameObject::ScaleObject(glm::vec3 scale)
{
	m_identity = glm::scale(m_identity, scale);
	m_scale += scale;
}
