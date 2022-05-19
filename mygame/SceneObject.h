#pragma once
#include "GameObject.h"
#include <iostream>
#include <glm/glm.hpp>

class SceneObject :	public GameObject
{
public:
	/** A default constructor of the SceneObject 
	*/
	SceneObject();

	/** A constructor of the SceneObject
	* @param const char* filePath a file path to the model's location
	*/
	SceneObject(const char* filePath);

	/** A constructor of the SceneObject
   * @param glm::vec3 position the position of the object
   * @param glm::vec3 scale the scale of the object
   * @param glm::vec3 orientation the orientation of the object
   * @param float angle the angle of the object
   * @param glm::vec3 rotAxis the rotation axis of the object
   * @param const char* filePath the filepath of the object's model
   * @param GameObject::ObjectType type the gameobject type of the object
   */
	SceneObject(glm::vec3 position, glm::vec3 scale, glm::vec3 orientation, float angle, glm::vec3 rotAxis, const char* filePath, ObjectType type);

	/** A destructor of the SceneObject
	*/
	~SceneObject();


	/** Get the object model
	* @return an object model
	*/
	WfModel GetModel() { return m_model; }

	/** Get the object model texture ID
	* @return an object model texture ID
	*/
	GLuint GetModelTextureID() { return m_model.textureId; }

	/** Get the object model vao ID
	* @return an object model vao ID
	*/
	GLuint GetModelVaoID() { return m_model.vaoId; }

	/** Get the object model positionVbo ID
	* @return an object model positionVbo ID
	*/
	GLuint GetModelPositionVboId() { return m_model.positionVboId; }

	/** Get the object model normalVboId ID
	* @return an object model normalVboId ID
	*/
	GLuint GetModelNormalVboId() { return m_model.normalVboId; }

	/** Get the object model vertexCount
	* @return an object model vertexCount
	*/
	GLuint GetModelVertexCount() { return m_model.vertexCount; }

protected:
	/** The object's model
	*/
	WfModel m_model;
};

