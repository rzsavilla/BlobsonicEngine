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
	/*! Entity storage and management
	* Stores entities and used to set entity destruction
	*/
	EntityManager m_entities;	

	/*! Pointer to resource manager
		Allows scenes to access loaded resources
	*/
	ResourceManager* m_ptrResources;

	/*!	Factory pattern entity generation
	*	Used to generate premade entities or attach new components to entities
	*/
	EntityFactory m_factory;
public:
	Scene(ResourceManager* res);
	~Scene();	//!< Destructor
	/**
		Scene loader replaces majority of what this function would do.
		SceneLoader is simply called to initialize the scene
	*/
	virtual void initScene() = 0;

	//! Update scene
	virtual void update(float dt) = 0;

	//Pointer to resources/gives scene access to resources
	void setResources(ResourceManager* res);

	EntityManager* getEntityManager() { return &m_entities; }
	std::vector<std::shared_ptr<Entity>>* getEntities() { return &m_entities.m_entities; }

	void clearScene();	//!< Empties the scene destroying all entities
};