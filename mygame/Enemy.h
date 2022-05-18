#pragma once
#include "SceneObject.h"
class Enemy : public SceneObject
{
public:
	Enemy();
	Enemy(glm::vec3 position, glm::vec3 orientation, float angle, glm::vec3 rotAxis, const char* filePath);
	~Enemy();


	void Update();

private:
	
};

