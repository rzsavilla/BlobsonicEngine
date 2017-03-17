/**
* @class	Scene
* @brief	Abstract class for scenes
* Abstract class for creating different types of scenes and storing them all as a single scene type (Polymorphism)
*/

#pragma once

#include <stdafx.h>
#include "ResourceManager.h"
#include "EntityManager.h"

#include "Drawable.h"
#include "Message.h"

#include "ModelOLD.h"
#include "Light.h"
#include "Text.h"

#include "EntityFactory.h"

/* Abstract Scene class*/

class Scene
{
protected:
	//std::map<GLchar, Character>* m_ptrCharacters;			//!< Pointer to character used for create Text

	EntityManager m_entities;	//!< Store entities

	/*! Pointer to resource manager
		Allows scenes to access loaded resources
	*/
	ResourceManager* m_ptrResources;

	EntityFactory m_factory;
public:
	Scene(ResourceManager* res)
		:m_factory(res), m_ptrResources(res)
	{  }
	~Scene() {};	//!< Destructor
	/**
		Load textures, initialize shaders, etc.
	*/
	virtual void initScene() = 0;

	//! Update scene
	virtual void update(float dt) = 0;

	/*!	
		Allows scene to create Text by passing pointer to characters texture
	*/
	//void setCharacters(std::map<GLchar, Character>* characters);

	//Pointer to resources/gives scene access to resources
	void setResources(ResourceManager* res);

	std::vector<std::shared_ptr<Entity>>* getEntities() { return &m_entities.m_entities; }
};