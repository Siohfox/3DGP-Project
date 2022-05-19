#pragma once
// Main libraries
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stb_image.h>

// System libraries
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>  

// Necessary header for GameObject::ObjectType
#include "GameObject.h"

// Forward declare to save space
class Shader;
class Camera;
class RenderTexture;
class Mesh;
class Movement;
class SceneObject;
class Camera;

/*! \brief Brief description.
*  This game class sets up all the game logic necessary for the program to render and run 
*/

class Game
{
public:
	/** A constructor for the Game
	*/
	Game();

	/** A destructor for the Game
	*/
	~Game();

	/** A method for updating every object in the scene
    */
	void Update();

	/** A method for initialising the SDL window
	* @return a SDL_Window*
    */
	SDL_Window* SDLWindowInit();

	/** A method for making a game object in the scene
   * @param glm::vec3 pos the position of the object
   * @param glm::vec3 scale the scale of the object
   * @param glm::vec3 orient the orientation of the object
   * @param float angle the angle of the object
   * @param glm::vec3 rotAxis the rotation axis of the object
   * @param const char* filePath the filepath of the object's model
   * @param GameObject::ObjectType type the gameobject type of the object
   */
	void CreateSceneObject(glm::vec3 pos, glm::vec3 scale, glm::vec3 orient, float angle, glm::vec3 rotAxis, const char* filePath, GameObject::ObjectType type);

	/** A method for making a game object in the scene
   * @param i the for integer
   */
	void Render(int i);

private:
	/** SDL window holder
	*/
	SDL_Window* m_window;

	/** A vector of scene objects
	*/
	std::vector<SceneObject*> m_sceneObjects;

	/** A camera
	*/
	Camera* m_cam;

	/** An orthographic camera
	*/
	Camera* m_orthoCam;

	/** A movement holder
	*/
	Movement* m_movement;

	/** A mesh defined as a quad
	*/
	Mesh* m_quad;

	/** The light shader
	*/
	Shader* m_lightShader;

	/** A basic shader
	*/
	Shader* m_basicShader;

	/** The rendertexture
	*/
	RenderTexture* m_renderTexture;

	/** The model location
	*/
	GLint m_modelLocation;

	/** The projection location
	*/
	GLint m_projectionLocation;

	/** A bool for checking when to quit the main loop
	*/
	bool m_quit;

	/** A movement checker - interacts with Movement()
	*/
	int m_moveCheck;

	/** A random number generator
	*/
	bool m_randGen;
};


