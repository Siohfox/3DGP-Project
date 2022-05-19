#pragma once
#include "GameObject.h"
class Camera :	public GameObject
{
public:
	/** Camera default constructor
   */
	Camera();

	/** A method for making a game object in the scene
   * @param glm::vec3 pos the position of the camera
   * @param glm::vec3 orientation the orientation of the camera
   * @param float angle the angle of the camera
   * @param glm::vec3 rotAxis the rotation axis of the camera
   * @param bool perspective whether the camera is perspective or orthographic
   */
	Camera(glm::vec3 position, glm::vec3 orientation, float angle, glm::vec3 rotAxis, bool perspective);

	/** Camera deconstructor
   */
	~Camera();

	/** Set projection of the camera
   * @param glm::mat4 projection an input matrix for the projection of the camera
   */
	void SetProjection(glm::mat4 projection) { m_identity = projection; }

	/** Get projection of the camera
   * @return the camera's identity matrix
   */
	glm::mat4 GetProjection() { return m_identity; }
};

