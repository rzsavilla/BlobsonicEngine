/*
*	@class LuaEntity
*	@brief Handle for a C++ Entity
*	@author Rozen Savilla
*	Stores variables and functions that
*/

#pragma once

#include "MessageHandler.h"

#include "Entity.h"

#include "sol.hpp"

#include <unordered_map>

static lua_State* m_activeScript = NULL;

class LuaEntity {
private:
	std::shared_ptr<Entity> m_entity;		//!< Pointer to entity being handled/Created upon construction
	bool m_bDebug = false;					//!< Enables couts to console
private:	//Component functions
	void setTransformable(sol::table t);	//!< Attaches and sets Transformable component
	void setModel(sol::table t);			//!< Attaches and sets Model component
	void setPhysical(sol::table t);			//!< Attaches and sets Physical component
	void setAABB(sol::table t);				//!< Attaches and sets AABB Component
	void setSphere(sol::table t);			//!< Attaches and sets Sphere collider component
	void setOBB(sol::table t);				//!< Attaches and sets OBB (Oriented Bounding Box) component
	bool m_bDestroyed;						//!< Check to see if this handler is destroyed
public:
	LuaEntity();	//!< Default Constructor
	/*!
		Creates new entity and attaches components to it this LuaEntity
		Attaches components to entity by reading from lua table
	*/
	void setComponents(sol::table t);

	/*!
		Find entity in the active scene and handle that entity
	*/
	void handleEntity(const std::string& name);			//!< This becomes handler to an already existing entity within the scene

	bool hasComponent(const std::string& sComponent);	//!< Returns true if entity has component
	unsigned int getID();	//!< Return entities unique ID
	void destroy();			//!< Destroy this entity
	bool isDestroyed();		//!< Returns true if entityhandler is destroyed

	//----------------Transformable component Functions-----------------------
	void tSetPosition(float x, float y, float z);	//!< Set transformable components position
	void tSetRotation(float x, float y, float z);	//!< Set transformable components rotation
	void tSetScale(float x, float y, float z);		//!< Set transformable components scale
	void tSetOrigin(float x, float y, float z);		//!< Set transformable components origin
	float tGetPosX();		//!< Return transformable position x
	float tGetPosY();		//!< Return transformable position y
	float tGetPosZ();		//!< Return transformable position z
	//----------------Physical component Functions-----------------------
	void pSetMass(float newMass);
	void pSetInvMass(float newInvMass);
	void pSetRestitution(float newRestituion);
	void pSetVelocity(float x, float y, float z);

	/*! Register this C++ class as a lua class
		Allows lua access to member functions
	*/
	static void register_lua(lua_State* L);
};