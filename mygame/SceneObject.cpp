#include "SceneObject.h"

SceneObject::SceneObject(const char* filePath)
{
	m_model = { 0 };

	if (WfModelLoad("models/curuthers/curuthers.obj", &m_model) != 0)
	{
		throw std::runtime_error("failed to load model thingy");
	}

}

SceneObject::SceneObject(glm::vec3 position, glm::vec3 orientation, float angle, glm::vec3 rotAxis, const char* filePath)
{
	m_position = position;
	m_orientation = orientation;
	m_identity = glm::mat4(1.0f);

	m_model = { 0 };

	if (WfModelLoad("models/curuthers/curuthers.obj", &m_model) != 0)
	{
		throw std::runtime_error("failed to load model thingy");
	}

	
	m_identity = glm::translate(m_identity, position);
	m_identity = glm::rotate(m_identity, glm::radians(angle), rotAxis);
}


SceneObject::~SceneObject()
{
	WfModelDestroy(&m_model);
}


