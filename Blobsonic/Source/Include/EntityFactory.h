#pragma once

#include "stdafx.h"
#include "ResourceManager.h"

class EntityFactory {
private:
	ResourceManager* m_ptrResources;
public:
	EntityFactory(ResourceManager* res);

	std::shared_ptr<Entity> create(std::string entity);

	std::shared_ptr<Entity> createPlayer(glm::vec3 position);	//Entity with transformable,movable,player and model components

	std::shared_ptr<Entity> createCamera(glm::vec3 position);

	std::shared_ptr<Entity> createActor();


	//Phsyics
	void attachAABB(std::shared_ptr<Entity> entity, glm::vec3 position, glm::vec3 Dimensions, glm::vec3 Scale);//Use for "early out" collision testing
	
	void attachOBB(std::shared_ptr<Entity> entity, glm::vec3 position, glm::vec3 Dimensions, glm::vec3 Scale, glm::vec3 Rot);// Use for precicse box collision testing

	void attachSphere(std::shared_ptr<Entity> entity, glm::vec3 position, float radius); // becarefull when resizing entity

	void attachCapsule(std::shared_ptr<Entity> entity, glm::vec3 position, glm::vec3 dimensions, glm::vec3 scale, glm::vec3 Rot);

	void attachPhysical(std::shared_ptr<Entity> entity);


};