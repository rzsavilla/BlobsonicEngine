/**
* @class	Scene
* @brief	Abstract class for scenes
* Abstract class for creating different types of scenes and storing them all as a single scene type (Polymorphism)
*/

#pragma once

#include <stdafx.h>
#include "ResourceManager.h"
#include "Drawable.h"
#include "Message.h"

#include "Model.h"
#include "Light.h"
#include "Text.h"

/* Abstract Scene class*/


//class Scene {
//private:
//
//public:
//	Scene();
//
//};

class Scene: public Drawable
{
protected:
	unsigned int m_uiCameraActive;	//!< index of camera being used

	int m_iKey_W;		//!< Key press
	int m_iKey_S;		//!< Key press
	int m_iKey_A;		//!< Key press
	int m_iKey_D;		//!< Key press
	int m_iKey_Up;		//!< Key press
	int m_iKey_Down;		//!< Key press
	int m_iKey_Left;		//!< Key press
	int m_iKey_Right;		//!< Key press
	int m_iKey_Escape;	//!< Key press
	int m_iKey_Space;	//!< Key press
	int m_iKey_Q;		//!< Key press
	int m_iKey_E;		//!< Key press
	int m_iKey_R;		//!< Key press

	double m_dMouseX;		//!< Mouse position x
	double m_dMouseY;		//!< Mouse position y
	double m_dPrevMouseX;	//!< Mouse x position in previous frame
	double m_dPrevMouseY;	//!< Mouse y position in previous frame

	/*!  /brief Pointer to vector of messages.
		Allows the scenes/derived classes to create and pass messages to other components.
	*/
	std::vector<std::shared_ptr<Message>>* m_ptrMessages;	
	std::map<GLchar, Character>* m_ptrCharacters;			//!< Pointer to character used for create Text
	/*! Pointer to resource manager
		Allows scenes to access loaded resources
	*/
	ResourceManager* m_ptrResources;	
public:
	~Scene() {};	//!< Destructor
	/**
		Load textures, initialize shaders, etc.
	*/
	virtual void initScene() = 0;

	/*! 
		Process GLFW inputs for scene
	*/
	virtual void handleInput(GLFWwindow* window) = 0;

	//! Update scene
	virtual void update(float dt) = 0;

	//! Draw Scene
	virtual void draw() = 0;

	/*! 
		Set pointer to vector of messages.
		Allow seen to create messages/ Communicate to other components
	*/
	void setMessages(std::vector<std::shared_ptr<Message>>* messages) {
		m_ptrMessages = messages;
	}

	/*!	
		Allows scene to create Text by passing pointer to characters texture
	*/
	void setCharacters(std::map<GLchar, Character>* characters);

	//Pointer to resources/gives scene access to resources
	void setResources(ResourceManager* res);
};