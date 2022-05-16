#pragma once
#include "GameObject.h"
#include <iostream>
#include <glm/glm.hpp>

class SceneObject :	public GameObject
{
public:
	SceneObject(const char* filePath);
	SceneObject(glm::vec3 position, glm::vec3 orientation, float angle, glm::vec3 rotAxis, const char* filePath);
	~SceneObject();

	WfModel GetModel() { return m_model; }
	GLuint GetModelTextureID() { return m_model.textureId; }
	GLuint GetModelVaoID() { return m_model.vaoId; }
	GLuint GetModelPositionVboId() { return m_model.positionVboId; }
	GLuint GetModelNormalVboId() { return m_model.normalVboId; }
	GLuint GetModelVertexCount() { return m_model.vertexCount; }
protected:
	WfModel m_model;
};

