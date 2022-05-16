#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <wavefront/wavefront.h>

class GameObject abstract
{
public:
	virtual void TranslateObject(glm::vec3 translation);
	virtual void RotateObject(float angle, glm::vec3 rotAxis);

	virtual void SetPos(glm::vec3 position) { m_position = position; };
	virtual void SetOrientation(glm::vec3 orientation) { m_orientation = orientation; }
	virtual void SetIdentity(glm::mat4 identity) { m_identity = identity; };

	virtual glm::vec3 GetPos() { return m_position; }
	virtual glm::vec3 GetOrientation() { return m_orientation; }
	virtual glm::mat4 GetIdentity() { return m_identity; }

protected:
	glm::vec3 m_position;
	glm::vec3 m_orientation;
	glm::mat4 m_identity;
};