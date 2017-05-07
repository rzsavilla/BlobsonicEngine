/*
*	@class LuaEntity
*	@brief Handle for a C++ Entity
*	@author Rozen Savilla
*	An interface that handles an engine entity
*/

#pragma once
#include <unordered_map>
#include "MessageHandler.h"
#include "CollisionReporter.h"
#include "CollisionReceiver.h"

#include "Entity.h"
#include "sol.hpp"
#include "Sound.h"

class LuaEntity : public CollisionReceiver {
private:
	std::shared_ptr<Entity> m_entity;		//!< Pointer to entity being handled/Created upon construction
	bool m_bDebug = true;					//!< Enables couts to console
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
	~LuaEntity();
	/*!
		Creates new entity and attaches components to it this LuaEntity
		Attaches components to entity by reading from lua table
	*/
	void setComponents(sol::table t);

	/*!
		Find entity in the active scene and handle that entity
	*/
	void handleEntity(const std::string& name);			//!< This becomes handler to an already existing entity within the scene
	bool hasEntity();	//!< Has a handle to an entity
	bool hasComponent(const std::string& sComponent);	//!< Returns true if entity has component
	unsigned int getID();	//!< Return entities unique ID
	std::string getName();	//!< Return entity name
	void destroy();			//!< Destroy this entity
	bool isDestroyed();		//!< Returns true if entityhandler is destroyed
	void log();				//!< Prints entity variables in console

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
	void pCollisionListen();							//!< Messages physics system to report collisions that occur for this entity
	bool pHasCollidedByID(int entityID);		//!< Returns true if a collision report between this entity has occured
	int pHasCollidedByName(std::string entityName);	//!< Returns ID of entity collided with returns -1 if no collision has 
	void pApplyImpulse(float nx, float ny, float nz, float force);
	void pMove(float forwardX, float forwardY, float forwardZ, float speed);
	//----------------Sound Component Functions-------------------------
	void sPlay();


	/*! Register this C++ class as a lua class
		Allows lua access to member functions
	*/
	static void register_lua(lua_State* L);

	void registerCollision(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2);
};