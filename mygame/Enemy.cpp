#include "Enemy.h"
#include "Enemy.h"

Enemy::Enemy()
{
	m_position = glm::vec3(0.0f, 0.0f, -20.0f);
	m_orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_identity = glm::mat4(1.0f);

	m_model = { 0 };
}

Enemy::Enemy(glm::vec3 position, glm::vec3 orientation, float angle, glm::vec3 rotAxis, const char* filePath)

{
	m_position = position;
	m_orientation = orientation;
	m_identity = glm::mat4(1.0f);

	m_model = { 0 };

	if (WfModelLoad(filePath, &m_model) != 0)
	{
		throw std::runtime_error("failed to load model thingy");
	}


	m_identity = glm::translate(m_identity, position);
	m_identity = glm::rotate(m_identity, glm::radians(angle), rotAxis);
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	TranslateObject(glm::vec3(0.0f, 0.0f, -1.0f));
}
