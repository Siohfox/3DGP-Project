#include "GameObject.h"

void GameObject::TranslateObject(glm::vec3 translation)
{
	m_identity = glm::translate(m_identity, translation);
}

void GameObject::RotateObject(float angle, glm::vec3 rotAxis)
{
	m_identity = glm::rotate(m_identity, glm::radians(angle), rotAxis);
}
