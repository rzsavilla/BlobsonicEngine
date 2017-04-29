/**
* @class	Scene
* @brief	Class stores scene objects
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
	/*! Entity storage and management
	* Stores entities and used to set entity destruction
	*/
	EntityManager m_entities;	

	/*! Pointer to instance of the resource manager
		Allows scenes to access loaded resources
	*/
	std::shared_ptr<ResourceManager> m_ptrResources;

	/*!	Factory pattern entity generation
	*	Used to generate premade entities or attach new components to entities
	*/
	EntityFactory m_factory;
public:
	Scene();
	~Scene();	//!< Destructor
	/**
		Scene loader replaces majority of what this function would do.
		SceneLoader is simply called to initialize the scene
	*/
	virtual void initScene() { };

	//! Update scene
	virtual void update(float dt) { };

	EntityManager* getEntityManager() { return &m_entities; }
	std::vector<std::shared_ptr<Entity>>* getEntities() { return &m_entities.m_entities; }

	void clearScene();	//!< Empties the scene destroying all entities
};