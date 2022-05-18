#include "SceneObject.h"

SceneObject::SceneObject()
{
	m_position = glm::vec3(0.0f, 0.0f, -20.0f);
	m_orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_identity = glm::mat4(1.0f);

	m_model = { 0 };

	m_objectType = ObjectType::Floor;
}

SceneObject::SceneObject(const char* filePath)
{
	m_model = { 0 };

	if (WfModelLoad("models/curuthers/curuthers.obj", &m_model) != 0)
	{
		throw std::runtime_error("failed to load model thingy");
	}

	m_objectType = ObjectType::Floor;

}

SceneObject::SceneObject(glm::vec3 position, glm::vec3 scale, glm::vec3 orientation, float angle, glm::vec3 rotAxis, const char* filePath, ObjectType type)
{
	m_position = position;
	m_orientation = orientation;
	m_identity = glm::mat4(1.0f);
	m_objectType = type;
	m_scale = scale;

	m_model = { 0 };

	if (WfModelLoad(filePath, &m_model) != 0)
	{
		throw std::runtime_error("failed to load model thingy");
	}

	
	m_identity = glm::translate(m_identity, position);
	m_identity = glm::rotate(m_identity, glm::radians(angle), rotAxis);
	m_identity = glm::scale(m_identity, scale);
}


SceneObject::~SceneObject()
{
	WfModelDestroy(&m_model);
}


