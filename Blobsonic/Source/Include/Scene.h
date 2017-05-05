/**
*	@class	Scene
*	@brief	Storage for scene
*	Abstract class for creating different types of scenes and storing them all as a single scene type (Polymorphism)
*/

#pragma once

#include "stdafx.h"
#include "ResourceManager.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "UniqueID.h"

/* Abstract Scene class*/

class Scene: public Destroyable, public UniqueID, public Name
{
protected:
	/*! Entity storage and management
	* Stores entities and used to set entity destruction
	*/
	EntityManager m_entities;	

public:
	Scene();	//!< Default constructor
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