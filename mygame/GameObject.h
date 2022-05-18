#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <wavefront/wavefront.h>

class GameObject abstract
{
public:
	enum class ObjectType { Enemy, Player, Floor, Other };

	virtual void TranslateObject(glm::vec3 translation);
	virtual void RotateObject(float angle, glm::vec3 rotAxis);
	virtual void ScaleObject(glm::vec3 scale);

	virtual void SetPos(glm::vec3 position) { m_position = position; };
	virtual void SetScale(glm::vec3 scale) { m_scale = scale; }
	virtual void SetOrientation(glm::vec3 orientation) { m_orientation = orientation; }
	virtual void SetIdentity(glm::mat4 identity) { m_identity = identity; };
	virtual void SetObjectType(ObjectType type) { m_objectType = type; }

	virtual glm::vec3 GetPos() { return m_position; }
	virtual glm::vec3 GetScale() { return m_scale; }
	virtual glm::vec3 GetOrientation() { return m_orientation; }
	virtual glm::mat4 GetIdentity() { return m_identity; }
	virtual ObjectType GetObjectType() { return m_objectType; }

protected:
	glm::vec3 m_position;
	glm::vec3 m_orientation;
	glm::vec3 m_scale;
	glm::mat4 m_identity;
	ObjectType m_objectType;
};