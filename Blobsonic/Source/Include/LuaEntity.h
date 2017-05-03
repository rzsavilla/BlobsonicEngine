/*
*	@class LuaEntity
*	@brief Handle for a C++ Entity
*	@author Rozen Savilla
*	Stores variables and functions
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
	void setTransformable(sol::table t);	//Attaches and sets Transformable component
	void setModel(sol::table t);			//Attaches and sets Model component
	void setPhysical(sol::table t);			//Attaches and sets Physical component
public:
	LuaEntity();	//!< Default Constructor
	/*!
		Attaches components to entity by reading from lua table
	*/
	void setComponents(sol::table t);
	bool hasComponent(const std::string& sComponent);	//!< Returns true if entity has component
	unsigned int getID();	//!< Return entities unique ID
	void destroy();			//!< Destroy this entity

	//----------------Transformable component Functions-----------------------
	void tSetPosition(float x, float y, float z);	//!< Set transformable components position
	void tSetRotation(float x, float y, float z);	//!< Set transformable components rotation
	void tSetScale(float x, float y, float z);		//!< Set transformable components scale
	void tSetOrigin(float x, float y, float z);		//!< Set transformable components origin
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