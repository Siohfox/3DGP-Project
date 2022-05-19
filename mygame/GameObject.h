#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <wavefront/wavefront.h>

class GameObject abstract
{
public:
	/** an Enum object type to define independent object behaviours
    * @enums Enemy, Player, Floor, Other
    */
	enum class ObjectType { Enemy, Player, Floor, Other };

	/** A method of translating the object
    * @param glm::vec3 translation a translation amount
    */
	virtual void TranslateObject(glm::vec3 translation);

	/** A method of rotating the object
    * @param float angle angle of rotation
    * @param glm::vec3 rotAxis a rotation axis to rotate around
    */
	virtual void RotateObject(float angle, glm::vec3 rotAxis);

	/** A method of scaling the object
    * @param glm::vec3 scale a scale amount
    */
	virtual void ScaleObject(glm::vec3 scale);

	/** Set position for the object
    * @param glm::vec3 position a 3D vector for the position of the object
    */
	virtual void SetPos(glm::vec3 position) { m_position = position; };

	/** Set scale for the object
    * @param glm::vec3 scale a 3D vector for the scale of the object
    */
	virtual void SetScale(glm::vec3 scale) { m_scale = scale; }

	/** Set orientation for the object
    * @param glm::vec3 orientation a 3D vector for the orientation of the object
    */
	virtual void SetOrientation(glm::vec3 orientation) { m_orientation = orientation; }

	/** Set identity for the object
    * @param glm::mat4 identity a 4x4 matrix for the identity of the object
    */
	virtual void SetIdentity(glm::mat4 identity) { m_identity = identity; };

	/** Set type for the object
   * @param ObjectType type a ObjectType for the type of the object
   */
	virtual void SetObjectType(ObjectType type) { m_objectType = type; }


	/** Get the position of the object
	* @return a 3D vector
	*/
	virtual glm::vec3 GetPos() { return m_position; }

	/** Get the scale of the object
	* @return a 3D vector
	*/
	virtual glm::vec3 GetScale() { return m_scale; }

	/** Get the orientation of the object
	* @return a 3D vector
	*/
	virtual glm::vec3 GetOrientation() { return m_orientation; }

	/** Get the idnetity of the object
	* @return a 4x4 matrix
	*/
	virtual glm::mat4 GetIdentity() { return m_identity; }

	/** Get the type of the object
	* @return an ObjectType
	*/
	virtual ObjectType GetObjectType() { return m_objectType; }

protected:
	/** Position of the object
	*/
	glm::vec3 m_position;

	/** Orientation of the object
	*/
	glm::vec3 m_orientation;

	/** Scale of the object
	*/
	glm::vec3 m_scale;

	/** Identity matrix of the object
	*/
	glm::mat4 m_identity;

	/** Type of the object
	*/
	ObjectType m_objectType;
};