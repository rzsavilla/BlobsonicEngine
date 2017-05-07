#include "stdafx.h"
#include "Physics.h"
#include "AABB.h"
#include "OBB.h"
#include "Sphere.h"
#include "Capsule.h"
#include "Physical.h"
#include "Transformable.h"

#include "SceneMessages.h"
#include "CollisionReporter.h"

System::Physics::Physics()
{

}

void System::Physics::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	//m_vAABBS.clear();
	//m_vOBBS.clear();
	//m_vSpheres.clear();
	//m_vCapsules.clear();
	//m_vPhysicals.clear();

	for (auto it = entities->begin(); it != entities->end(); ++it)
	{
		if ((*it)->has<Capsule>() && (*it)->has<Component::Transformable>()) {
			//m_vCapsules.push_back((*it));
			addEntity((*it), &m_vCapsules);	// Will add entity if it has not yet been added
		}
		if ((*it)->has<AABB>() && (*it)->has<Component::Transformable>()) {
			//m_vAABBS.push_back((*it));
			addEntity((*it), &m_vAABBS);

		}
		if ((*it)->has<OBB>() && !(*it)->has<Capsule>() && (*it)->has<Component::Transformable>()) {
			//m_vOBBS.push_back((*it));
			addEntity((*it), &m_vOBBS);

		}
		if ((*it)->has<Sphere>() && !(*it)->has<Capsule>() && (*it)->has<Component::Transformable>()) {
			//m_vSpheres.push_back((*it));
			addEntity((*it), &m_vSpheres);

		}
		if ((*it)->has<Physical>() && (*it)->has<Component::Transformable>()) {
			//m_vPhysicals.push_back((*it));
			addEntity((*it), &m_vPhysicals);
		}
	}

	

}

void System::Physics::removeDestroyed(std::vector<std::shared_ptr<Entity>>* entities)
{
	for (int i = 0; i < entities->size(); i++) {
		if (entities->at(i)->isDestroyed()) {
			entities->erase(entities->begin() + i);
		}
	}
}

void System::Physics::update(float dt)
{

	dt = 1 / 60.0f;


	//update physicals positions
	for (int i = 0; i < m_vPhysicals.size(); i++)
	{
		updatePhysicals(m_vPhysicals.at(i),dt);
	}


	//update all collidables positions
	for (int i = 0; i < m_vAABBS.size(); i++)
	{
		updateAABB(m_vAABBS.at(i));
	}
	for (int i = 0; i < m_vOBBS.size(); i++)
	{
		updateOBB(m_vOBBS.at(i));
	}
	for (int i = 0; i < m_vSpheres.size(); i++)
	{
		updateSphere(m_vSpheres.at(i));
	}

	broadPhase(dt);
	narrowPhase(dt);


	removeDestroyed(&m_vAABBS);
	removeDestroyed(&m_vCapsules);
	removeDestroyed(&m_vOBBS);
	removeDestroyed(&m_vSpheres);
	removeDestroyed(&m_vPhysicals);
}

void System::Physics::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	for (auto it = msgs->begin(); it != msgs->end(); ++it) {
		if ((*it)->sID == "ListenCollision") {
			auto data = static_cast<SceneMessage::ListenToCollision*>((*it).get());
			m_vListenToCollision.push_back(data->entityID);	//Record entity ID, will report collision events that occur with this entity
		}
	}
}

void System::Physics::addEntity(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>>* entities)
{
	for (auto it = entities->begin(); it != entities->end(); ++it) {
		if ((*it)->getUID() == entity->getUID()) {
			return;	//Entity already stored
		}
	}
	if (!entity->isDestroyed()) {
		if (entity->has<Component::Transformable>()) {
			auto t = entity->get<Component::Transformable>();

			//if (entity->has<OBB>()) {
			//	auto b = entity->get<OBB>();
			//	//Get component Properties
			//	auto t = entity->get<Component::Transformable>();
			//	auto o = entity->get<OBB>();

			//	o->m_vScale = o->m_vScale * t->getScale();

			//	o->m_Rotation = glm::rotate(o->m_Rotation, t->getRotation().x, glm::vec3(1.0f, 0.0, 0.0f));
			//	o->m_Rotation = glm::rotate(o->m_Rotation, t->getRotation().y, glm::vec3(0.0f, 1.0, 0.0f));
			//	o->m_Rotation = glm::rotate(o->m_Rotation, t->getRotation().z, glm::vec3(0.0f, 0.0, 1.0f));

			//	o->m_vCenter = glm::mat3(o->m_Rotation) * (t->getPosition() + (o->m_vScale * t->getScale()) / 2.0f);
			//}
			//if (entity->has<AABB>()) {
			//	auto b = entity->get<AABB>();

			//	//Set component Properties
			//	auto t = entity->get<Component::Transformable>();
			//	auto a = entity->get<AABB>();

			//	//find the longest side of the whole object , so as the bounding box ebcases all orientation
			//	float fSize = std::max(a->m_vScale.x * t->getScale().x, a->m_vScale.y * t->getScale().y);
			//	fSize = std::max(fSize, a->m_vScale.z * t->getScale().z);

			//	a->m_vCenter = t->m_vPosition + (a->m_vScale * a->m_vScale) / 2.0f;
			//}
			if (entity->has<Physical>()) {
				auto p = entity->get<Physical>();
				if (p->m_fMass == 0) {
					p->setfINVMass(0);
				}
				else {
					p->setfINVMass(1 / p->getMass());
				}
			}
		}
		entities->push_back(entity);	//Store entity
	}
}

bool System::Physics::CheckAABBAABBCollision(std::shared_ptr<Entity> aabb1, std::shared_ptr<Entity> aabb2)
{
	auto aabox1 = aabb1->get<AABB>();
	auto aabox2 = aabb2->get<AABB>();

	//aabox1->m_vCenter = aabox1->m_vPosition + aabox1->m_vScale / 2.0f;
	//aabox2->m_vCenter = aabox2->m_vPosition + aabox2->m_vScale / 2.0f;

	//create positions of all vertecies
	aabox1->obbLocalPoints[0] = glm::vec3(aabox1->m_vCenter.x - aabox1->m_vScale.x / 2, aabox1->m_vCenter.y + aabox1->m_vScale.y / 2, aabox1->m_vCenter.z + aabox1->m_vScale.z / 2);	//Front - Top left
	aabox1->obbLocalPoints[1] = glm::vec3(aabox1->m_vCenter.x + aabox1->m_vScale.x / 2, aabox1->m_vCenter.y + aabox1->m_vScale.y / 2, aabox1->m_vCenter.z + aabox1->m_vScale.z / 2);	//Front - Top Right
	aabox1->obbLocalPoints[2] = glm::vec3(aabox1->m_vCenter.x + aabox1->m_vScale.x / 2, aabox1->m_vCenter.y - aabox1->m_vScale.y / 2, aabox1->m_vCenter.z + aabox1->m_vScale.z / 2);	//Front - Bottom Right
	aabox1->obbLocalPoints[3] = glm::vec3(aabox1->m_vCenter.x - aabox1->m_vScale.x / 2, aabox1->m_vCenter.y - aabox1->m_vScale.y / 2, aabox1->m_vCenter.z + aabox1->m_vScale.z / 2);	//Front - Bottom left
	aabox1->obbLocalPoints[4] = glm::vec3(aabox1->m_vCenter.x - aabox1->m_vScale.x / 2, aabox1->m_vCenter.y + aabox1->m_vScale.y / 2, aabox1->m_vCenter.z - aabox1->m_vScale.z / 2);	//Back - Top left
	aabox1->obbLocalPoints[5] = glm::vec3(aabox1->m_vCenter.x + aabox1->m_vScale.x / 2, aabox1->m_vCenter.y + aabox1->m_vScale.y / 2, aabox1->m_vCenter.z - aabox1->m_vScale.z / 2);	//Back - Top Right
	aabox1->obbLocalPoints[6] = glm::vec3(aabox1->m_vCenter.x + aabox1->m_vScale.x / 2, aabox1->m_vCenter.y - aabox1->m_vScale.y / 2, aabox1->m_vCenter.z - aabox1->m_vScale.z / 2);	//Back - Bottom Right
	aabox1->obbLocalPoints[7] = glm::vec3(aabox1->m_vCenter.x - aabox1->m_vScale.x / 2, aabox1->m_vCenter.y - aabox1->m_vScale.y / 2, aabox1->m_vCenter.z - aabox1->m_vScale.z / 2);	//Back - Bottom left


	aabox2->obbLocalPoints[0] = glm::vec3(aabox2->m_vCenter.x - aabox2->m_vScale.x / 2, aabox2->m_vCenter.y + aabox2->m_vScale.y / 2, aabox2->m_vCenter.z + aabox2->m_vScale.z / 2);	//Front - Top left
	aabox2->obbLocalPoints[1] = glm::vec3(aabox2->m_vCenter.x + aabox2->m_vScale.x / 2, aabox2->m_vCenter.y + aabox2->m_vScale.y / 2, aabox2->m_vCenter.z + aabox2->m_vScale.z / 2);	//Front - Top Right
	aabox2->obbLocalPoints[2] = glm::vec3(aabox2->m_vCenter.x + aabox2->m_vScale.x / 2, aabox2->m_vCenter.y - aabox2->m_vScale.y / 2, aabox2->m_vCenter.z + aabox2->m_vScale.z / 2);	//Front - Bottom Right
	aabox2->obbLocalPoints[3] = glm::vec3(aabox2->m_vCenter.x - aabox2->m_vScale.x / 2, aabox2->m_vCenter.y - aabox2->m_vScale.y / 2, aabox2->m_vCenter.z + aabox2->m_vScale.z / 2);	//Front - Bottom left
	aabox2->obbLocalPoints[4] = glm::vec3(aabox2->m_vCenter.x - aabox2->m_vScale.x / 2, aabox2->m_vCenter.y + aabox2->m_vScale.y / 2, aabox2->m_vCenter.z - aabox2->m_vScale.z / 2);	//Back - Top left
	aabox2->obbLocalPoints[5] = glm::vec3(aabox2->m_vCenter.x + aabox2->m_vScale.x / 2, aabox2->m_vCenter.y + aabox2->m_vScale.y / 2, aabox2->m_vCenter.z - aabox2->m_vScale.z / 2);	//Back - Top Right
	aabox2->obbLocalPoints[6] = glm::vec3(aabox2->m_vCenter.x + aabox2->m_vScale.x / 2, aabox2->m_vCenter.y - aabox2->m_vScale.y / 2, aabox2->m_vCenter.z - aabox2->m_vScale.z / 2);	//Back - Bottom Right
	aabox2->obbLocalPoints[7] = glm::vec3(aabox2->m_vCenter.x - aabox2->m_vScale.x / 2, aabox2->m_vCenter.y - aabox2->m_vScale.y / 2, aabox2->m_vCenter.z - aabox2->m_vScale.z / 2);	//Back - Bottom left


																																																	//set up the mins and maxs
	aabox1->m_fMinX = 9999999999999999999.0f;
	aabox1->m_fMinY = 9999999999999999999.0f;
	aabox1->m_fMinZ = 9999999999999999999.0f;

	aabox1->m_fMaxX = -9999999999999999999.0f;
	aabox1->m_fMaxY = -9999999999999999999.0f;
	aabox1->m_fMaxZ = -9999999999999999999.0f;

	aabox2->m_fMinX = 9999999999999999999.0f;
	aabox2->m_fMinY = 9999999999999999999.0f;
	aabox2->m_fMinZ = 9999999999999999999.0f;

	aabox2->m_fMaxX = -9999999999999999999.0f;
	aabox2->m_fMaxY = -9999999999999999999.0f;
	aabox2->m_fMaxZ = -9999999999999999999.0f;

	//loop all the axis's for box 1

	for (int i = 0; i < 8; i++)
	{
		if (aabox1->obbLocalPoints[i].x < aabox1->m_fMinX)
		{
			aabox1->m_fMinX = aabox1->obbLocalPoints[i].x;
		}
		if (aabox1->obbLocalPoints[i].y < aabox1->m_fMinY)
		{
			aabox1->m_fMinY = aabox1->obbLocalPoints[i].y;
		}
		if (aabox1->obbLocalPoints[i].z < aabox1->m_fMinZ)
		{
			aabox1->m_fMinZ = aabox1->obbLocalPoints[i].z;
		}
		//max
		if (aabox1->obbLocalPoints[i].x > aabox1->m_fMaxX)
		{
			aabox1->m_fMaxX = aabox1->obbLocalPoints[i].x;
		}
		if (aabox1->obbLocalPoints[i].y > aabox1->m_fMaxY)
		{
			aabox1->m_fMaxY = aabox1->obbLocalPoints[i].y;
		}
		if (aabox1->obbLocalPoints[i].z > aabox1->m_fMaxZ)
		{
			aabox1->m_fMaxZ = aabox1->obbLocalPoints[i].z;
		}
	}
	//loop all the axis's for box 2

	for (int i = 0; i < 8; i++)
	{
		if (aabox2->obbLocalPoints[i].x < aabox2->m_fMinX)
		{
			aabox2->m_fMinX = aabox2->obbLocalPoints[i].x;
		}
		if (aabox2->obbLocalPoints[i].y < aabox2->m_fMinY)
		{
			aabox2->m_fMinY = aabox2->obbLocalPoints[i].y;
		}
		if (aabox2->obbLocalPoints[i].z < aabox2->m_fMinZ)
		{
			aabox2->m_fMinZ = aabox2->obbLocalPoints[i].z;
		}

		//max
		if (aabox2->obbLocalPoints[i].x > aabox2->m_fMaxX)
		{
			aabox2->m_fMaxX = aabox2->obbLocalPoints[i].x;
		}
		if (aabox2->obbLocalPoints[i].y > aabox2->m_fMaxY)
		{
			aabox2->m_fMaxY = aabox2->obbLocalPoints[i].y;
		}
		if (aabox2->obbLocalPoints[i].z > aabox2->m_fMaxZ)
		{
			aabox2->m_fMaxZ = aabox2->obbLocalPoints[i].z;
		}
	}

	//test for an overlap x
	if (aabox1->m_fMinX <= aabox2->m_fMaxX && aabox1->m_fMinX >= aabox2->m_fMinX)
	{
		aabox1->testAxis[0] = true;
	}
	else if (aabox1->m_fMaxX >= aabox2->m_fMinX && aabox1->m_fMaxX <= aabox2->m_fMaxX)
	{
		aabox1->testAxis[0] = true;
	}
	else
	{
		aabox1->testAxis[0] = false;

	}
	//test for an overlap y
	if (aabox1->m_fMinY <= aabox2->m_fMaxY && aabox1->m_fMinY >= aabox2->m_fMinY)
	{
		aabox1->testAxis[1] = true;
	}
	else if (aabox1->m_fMaxY >= aabox2->m_fMinY && aabox1->m_fMaxY <= aabox2->m_fMaxY)
	{
		aabox1->testAxis[1] = true;
	}
	else
	{
		aabox1->testAxis[1] = false;
	}

	//test for an overlap z
	if (aabox1->m_fMinZ <= aabox2->m_fMaxZ && aabox1->m_fMinZ >= aabox2->m_fMinZ)
	{
		aabox1->testAxis[2] = true;
	}
	else if (aabox1->m_fMaxZ >= aabox2->m_fMinZ && aabox1->m_fMaxZ <= aabox2->m_fMaxZ)
	{
		aabox1->testAxis[2] = true;
	}
	else
	{
		aabox1->testAxis[2] = false;

	}

	if (aabox1->testAxis[0] && aabox1->testAxis[1] && aabox1->testAxis[2])
	{
		return true;
	}
	else
	{
		return false;
	}


}

bool System::Physics::CheckOBBOBBCollision(std::shared_ptr<Entity> obb1, std::shared_ptr<Entity> obb2)
{

	//setup data for the OBB's
	auto obox1 = obb1->get<OBB>();
	auto obox2 = obb2->get<OBB>();

	auto box1 = obb1->get<Component::Transformable>();
	auto box2 = obb2->get<Component::Transformable>();

	bool testAxis[6];


	// begin collison check!!!!

	//create local versions

	//create positions of all vertecies
	obox1->m_obbLocalPoints[0] = glm::vec3(obox1->m_vCenter.x - obox1->m_vScale.x / 2, obox1->m_vCenter.y + obox1->m_vScale.y / 2, obox1->m_vCenter.z + obox1->m_vScale.z / 2);	//Front - Top left
	obox1->m_obbLocalPoints[1] = glm::vec3(obox1->m_vCenter.x + obox1->m_vScale.x / 2, obox1->m_vCenter.y + obox1->m_vScale.y / 2, obox1->m_vCenter.z + obox1->m_vScale.z / 2);	//Front - Top Right
	obox1->m_obbLocalPoints[2] = glm::vec3(obox1->m_vCenter.x + obox1->m_vScale.x / 2, obox1->m_vCenter.y - obox1->m_vScale.y / 2, obox1->m_vCenter.z + obox1->m_vScale.z / 2);	//Front - Bottom Right
	obox1->m_obbLocalPoints[3] = glm::vec3(obox1->m_vCenter.x - obox1->m_vScale.x / 2, obox1->m_vCenter.y - obox1->m_vScale.y / 2, obox1->m_vCenter.z + obox1->m_vScale.z / 2);	//Front - Bottom left
	obox1->m_obbLocalPoints[4] = glm::vec3(obox1->m_vCenter.x - obox1->m_vScale.x / 2, obox1->m_vCenter.y + obox1->m_vScale.y / 2, obox1->m_vCenter.z - obox1->m_vScale.z / 2);	//Back - Top left
	obox1->m_obbLocalPoints[5] = glm::vec3(obox1->m_vCenter.x + obox1->m_vScale.x / 2, obox1->m_vCenter.y + obox1->m_vScale.y / 2, obox1->m_vCenter.z - obox1->m_vScale.z / 2);	//Back - Top Right
	obox1->m_obbLocalPoints[6] = glm::vec3(obox1->m_vCenter.x + obox1->m_vScale.x / 2, obox1->m_vCenter.y - obox1->m_vScale.y / 2, obox1->m_vCenter.z - obox1->m_vScale.z / 2);	//Back - Bottom Right
	obox1->m_obbLocalPoints[7] = glm::vec3(obox1->m_vCenter.x - obox1->m_vScale.x / 2, obox1->m_vCenter.y - obox1->m_vScale.y / 2, obox1->m_vCenter.z - obox1->m_vScale.z / 2);	//Back - Bottom left


	obox2->m_obbLocalPoints[0] = glm::vec3(obox2->m_vCenter.x - obox2->m_vScale.x / 2, obox2->m_vCenter.y + obox2->m_vScale.y / 2, obox2->m_vCenter.z + obox2->m_vScale.z / 2);	//Front - Top left
	obox2->m_obbLocalPoints[1] = glm::vec3(obox2->m_vCenter.x + obox2->m_vScale.x / 2, obox2->m_vCenter.y + obox2->m_vScale.y / 2, obox2->m_vCenter.z + obox2->m_vScale.z / 2);	//Front - Top Right
	obox2->m_obbLocalPoints[2] = glm::vec3(obox2->m_vCenter.x + obox2->m_vScale.x / 2, obox2->m_vCenter.y - obox2->m_vScale.y / 2, obox2->m_vCenter.z + obox2->m_vScale.z / 2);	//Front - Bottom Right
	obox2->m_obbLocalPoints[3] = glm::vec3(obox2->m_vCenter.x - obox2->m_vScale.x / 2, obox2->m_vCenter.y - obox2->m_vScale.y / 2, obox2->m_vCenter.z + obox2->m_vScale.z / 2);	//Front - Bottom left
	obox2->m_obbLocalPoints[4] = glm::vec3(obox2->m_vCenter.x - obox2->m_vScale.x / 2, obox2->m_vCenter.y + obox2->m_vScale.y / 2, obox2->m_vCenter.z - obox2->m_vScale.z / 2);	//Back - Top left
	obox2->m_obbLocalPoints[5] = glm::vec3(obox2->m_vCenter.x + obox2->m_vScale.x / 2, obox2->m_vCenter.y + obox2->m_vScale.y / 2, obox2->m_vCenter.z - obox2->m_vScale.z / 2);	//Back - Top Right
	obox2->m_obbLocalPoints[6] = glm::vec3(obox2->m_vCenter.x + obox2->m_vScale.x / 2, obox2->m_vCenter.y - obox2->m_vScale.y / 2, obox2->m_vCenter.z - obox2->m_vScale.z / 2);	//Back - Bottom Right
	obox2->m_obbLocalPoints[7] = glm::vec3(obox2->m_vCenter.x - obox2->m_vScale.x / 2, obox2->m_vCenter.y - obox2->m_vScale.y / 2, obox2->m_vCenter.z - obox2->m_vScale.z / 2);	//Back - Bottom left

																																																//multiply points by rotation matrix			


	obox1->m_Rotation = glm::rotate(obox1->m_Rotation, box1->getRotation().x, glm::vec3(1.0f, 0.0, 0.0f));
	obox1->m_Rotation = glm::rotate(obox1->m_Rotation, box1->getRotation().y, glm::vec3(0.0f, 1.0, 0.0f));
	obox1->m_Rotation = glm::rotate(obox1->m_Rotation, box1->getRotation().z, glm::vec3(0.0f, 0.0, 1.0f));

	obox1->m_obbLocalPoints[0] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[0];
	obox1->m_obbLocalPoints[1] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[1];
	obox1->m_obbLocalPoints[2] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[2];
	obox1->m_obbLocalPoints[3] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[3];
	obox1->m_obbLocalPoints[4] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[4];
	obox1->m_obbLocalPoints[5] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[5];
	obox1->m_obbLocalPoints[6] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[6];
	obox1->m_obbLocalPoints[7] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[7];


	obox2->m_Rotation = glm::rotate(obox2->m_Rotation, box2->getRotation().x, glm::vec3(1.0f, 0.0, 0.0f));
	obox2->m_Rotation = glm::rotate(obox2->m_Rotation, box2->getRotation().y, glm::vec3(0.0f, 1.0, 0.0f));
	obox2->m_Rotation = glm::rotate(obox2->m_Rotation, box2->getRotation().z, glm::vec3(0.0f, 0.0, 1.0f));

	obox2->m_obbLocalPoints[0] = obox2->m_obbLocalPoints[0] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[1] = obox2->m_obbLocalPoints[1] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[2] = obox2->m_obbLocalPoints[2] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[3] = obox2->m_obbLocalPoints[3] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[4] = obox2->m_obbLocalPoints[4] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[5] = obox2->m_obbLocalPoints[5] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[6] = obox2->m_obbLocalPoints[6] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[7] = obox2->m_obbLocalPoints[7] * glm::mat3(obox2->m_Rotation);

	//create normals for each face
	obox1->m_obbNormals[0] = glm::mat3(obox1->m_Rotation) * glm::vec3(0, 0, 1);  // front face
	obox1->m_obbNormals[1] = glm::mat3(obox1->m_Rotation) * glm::vec3(0, 0, -1); // back face
	obox1->m_obbNormals[2] = glm::mat3(obox1->m_Rotation) * glm::vec3(-1, 0, 0); // left face
	obox1->m_obbNormals[3] = glm::mat3(obox1->m_Rotation) * glm::vec3(1, 0, 0); // right face
	obox1->m_obbNormals[4] = glm::mat3(obox1->m_Rotation) * glm::vec3(0, 1, 0); // Top face
	obox1->m_obbNormals[5] = glm::mat3(obox1->m_Rotation) * glm::vec3(0, -1, 0); // bottom face

	obox2->m_obbNormals[0] = glm::mat3(obox2->m_Rotation) * glm::vec3(0, 0, 1);  // front face
	obox2->m_obbNormals[1] = glm::mat3(obox2->m_Rotation) * glm::vec3(0, 0, -1); // back face
	obox2->m_obbNormals[2] = glm::mat3(obox2->m_Rotation) * glm::vec3(-1, 0, 0); // left face
	obox2->m_obbNormals[3] = glm::mat3(obox2->m_Rotation) * glm::vec3(1, 0, 0); // right face
	obox2->m_obbNormals[4] = glm::mat3(obox2->m_Rotation) * glm::vec3(0, 1, 0); // Top face
	obox2->m_obbNormals[5] = glm::mat3(obox2->m_Rotation) * glm::vec3(0, -1, 0); // bottom face

	 

	//project 6 axis 
	for (int axisTest = 0; axisTest < 6; axisTest++)
	{
		//values for min box2->and max
		float obb1Min = 999999999999999999999.0f;
		float obb1Max = -999999999999999999999.0f;
		float obb2Min = 999999999999999999999.0f;
		float obb2Max = -999999999999999999999.0f;


		// check all vertecies on box 1
		for (int box1Vertex = 0; box1Vertex < 8; box1Vertex++)
		{
			float fDotProduct = glm::dot(obox1->m_obbNormals[axisTest], obox1->m_obbLocalPoints[box1Vertex]);
			if (fDotProduct < obb1Min)
			{
				obb1Min = fDotProduct;
			}
			if (fDotProduct > obb1Max)
			{
				obb1Max = fDotProduct;
			}

		}

		// check all vertecies on box 2
		for (int box2Vertex = 0; box2Vertex < 8; box2Vertex++)
		{
			float fDotProduct = glm::dot(obox1->m_obbNormals[axisTest], obox2->m_obbLocalPoints[box2Vertex]);
			if (fDotProduct < obb2Min)
			{
				obb2Min = fDotProduct;
			}
			if (fDotProduct > obb2Max)
			{
				obb2Max = fDotProduct;
			}

		}

		//check each box min and max for over lap
		if (obb2Min <= obb1Max && obb2Min >= obb1Min)
		{
			testAxis[axisTest] = true; // There is a collision along this axis
		}
		else if (obb2Max >= obb1Min && obb2Max <= obb1Max)
		{
			testAxis[axisTest] = true; // There is a collision along this axis
			
		
		}
		else
		{
			testAxis[axisTest] = false; // There is no collision along this axis
			return false;

		}

	}

	if (testAxis[0] == true && testAxis[1] == true && testAxis[2] == true && testAxis[3] == true && testAxis[4] == true && testAxis[5] == true)
	{

		// find normal
		glm::vec3 normal = obox2->m_vCenter - obox1->m_vCenter;
		

		//find overlap amount
		glm::vec3 pen;
		float fPen = abs(sqrt((pen.x * pen.x) + (pen.y * pen.y) + (pen.z * pen.z)));

		normal = glm::normalize(normal);
		//resolve
		resolveCollision(obb1, obb2, normal);

		//position
		PositionalCorrection(obb1, obb2, fPen, normal);

		return true;
	}
	

}

bool System::Physics::CheckShereSphereCollision(std::shared_ptr<Entity> sphere1, std::shared_ptr<Entity> sphere2)
{

	//setup data for the Sphere's
	auto sph1 = sphere1->get<Sphere>();
	auto sph2 = sphere2->get<Sphere>();

	auto t1 = sphere1->get<Component::Transformable>();
	auto t2 = sphere2->get<Component::Transformable>();

	//find the dist between the centre of each sphere
	glm::vec3 Dist = sph1->m_vCenter - sph2->m_vCenter;

	//find the magnitude of this distance
	float magDist = sqrt((Dist.x * Dist.x) + (Dist.y * Dist.y) + (Dist.z * Dist.z));

	//subtract the radius 
	magDist = magDist - sph1->m_fRadius;
	if (magDist <= sph2->m_fRadius)
	{
		if (sphere1->has<Physical>() && sphere2->has<Physical>())
		{
			// find penetration

			glm::vec3 Normal = sph1->m_vCenter - sph2->m_vCenter;
			glm::vec3 newVector = Normal;
			newVector = glm::normalize(newVector);
			newVector *= sph1->m_fRadius;
			newVector *= sph2->m_fRadius;
			Normal = Normal - newVector;


			float d = abs(sqrt((Normal.x * Normal.x) + (Normal.y * Normal.y) + (Normal.z * Normal.z)));
			//find collison normal
			Normal = glm::normalize(Normal);
			Normal = -Normal;

			//find the penetration depth
			float PenetrationDepth = (sph1->m_fRadius + sph2->m_fRadius) - d;
			resolveCollision(sphere1, sphere2, Normal);
			PositionalCorrection(sphere1, sphere2, PenetrationDepth, Normal);

		}

		return true;

	}
	else
	{
		return false;
	}
}

bool System::Physics::CheckOBBSphereCollision(std::shared_ptr<Entity> eBox, std::shared_ptr<Entity> eSphere)
{
	//setup data for sphere and box
	auto sphere = eSphere->get<Sphere>();
	auto box = eBox->get<OBB>();

	//local version
	Sphere localSphere = *sphere;

	bool bExtremeClamp = true;

	//translate sphere by inverse box position
	localSphere.m_vCenter = localSphere.m_vCenter - box->m_vCenter;

	//rotate sphere by inverse box rotation
	localSphere.m_mRotation = glm::rotate(localSphere.m_mRotation, -box->m_vRotation.x, glm::vec3(1.0f, 0.0, 0.0f));
	localSphere.m_mRotation = glm::rotate(localSphere.m_mRotation, -box->m_vRotation.y, glm::vec3(0.0f, 1.0, 0.0f));
	localSphere.m_mRotation = glm::rotate(localSphere.m_mRotation, -box->m_vRotation.z, glm::vec3(0.0f, 0.0, 1.0f));

	localSphere.m_vCenter = localSphere.m_vCenter * mat3(localSphere.m_mRotation);

	//find the distance from center to center
	glm::vec3 overAllDistance = glm::vec3(0, 0, 0) + localSphere.m_vCenter;
 	glm::vec3 clamp;


	//find which portion of space around the cube the sphere exists in

	if (overAllDistance.x < 0) // to the left of cube
	{
		if ((localSphere.m_vCenter.y < box->m_vScale.y / 2.0f && localSphere.m_vCenter.y > -box->m_vScale.y / 2.0f) && (localSphere.m_vCenter.z < box->m_vScale.z / 2.0f && localSphere.m_vCenter.z > -box->m_vScale.z / 2.0f))
		{
			clamp.x = -box->m_vScale.x / 2.0f;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = localSphere.m_vCenter.z;
			bExtremeClamp = false;
		}

	}

	if (overAllDistance.x > 0) // to the right of cube
	{
		if ((localSphere.m_vCenter.y < box->m_vScale.y / 2.0f && localSphere.m_vCenter.y > -box->m_vScale.y / 2.0f) && (localSphere.m_vCenter.z < box->m_vScale.z / 2.0f && localSphere.m_vCenter.z > -box->m_vScale.z / 2.0f))
		{
			clamp.x = box->m_vScale.x / 2.0f;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = localSphere.m_vCenter.z;
			bExtremeClamp = false;
		}

	}

	if (overAllDistance.y > 0) // above the cube
	{
		if ((localSphere.m_vCenter.x < box->m_vScale.x / 2.0f && localSphere.m_vCenter.x > -box->m_vScale.x / 2.0f) && (localSphere.m_vCenter.z < box->m_vScale.z / 2.0f && localSphere.m_vCenter.z > -box->m_vScale.z / 2.0f))
		{
			clamp.x = localSphere.m_vCenter.x;
			clamp.y = box->m_vScale.y / 2.0f;
			clamp.z = localSphere.m_vCenter.z;
			bExtremeClamp = false;
		}

	}
	if (overAllDistance.y < 0) // below the cube
	{
		if ((localSphere.m_vCenter.x < box->m_vScale.x / 2.0f && localSphere.m_vCenter.x > -box->m_vScale.x / 2.0f) && (localSphere.m_vCenter.z < box->m_vScale.z / 2.0f && localSphere.m_vCenter.z > -box->m_vScale.z / 2.0f))
		{
			clamp.x = localSphere.m_vCenter.x;
			clamp.y = -box->m_vScale.y / 2.0f;
			clamp.z = localSphere.m_vCenter.z;
			bExtremeClamp = false;
		}

	}
	if (overAllDistance.z > 0) // infront of the cube
	{
		if ((localSphere.m_vCenter.x < box->m_vScale.x / 2.0f && localSphere.m_vCenter.x > -box->m_vScale.x / 2.0f) && (localSphere.m_vCenter.y < box->m_vScale.y / 2.0f && localSphere.m_vCenter.y > -box->m_vScale.y / 2.0f))
		{
			clamp.x = localSphere.m_vCenter.x;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = box->m_vScale.z / 2.0f;
			bExtremeClamp = false;
		}

	}
	if (overAllDistance.z < 0) // behind the cube
	{
		if ((localSphere.m_vCenter.x < box->m_vScale.x / 2.0f && localSphere.m_vCenter.x > -box->m_vScale.x / 2.0f) && (localSphere.m_vCenter.y < box->m_vScale.y / 2.0f && localSphere.m_vCenter.y > -box->m_vScale.y / 2.0f))
		{
			clamp.x = localSphere.m_vCenter.x;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = -box->m_vScale.z / 2.0f;
			bExtremeClamp = false;
		}

	}

	if (overAllDistance.z < 0 && overAllDistance.x < 0) // behind and left 
	{

		if (localSphere.m_vCenter.y < box->m_vScale.y / 2.0f && localSphere.m_vCenter.y > -box->m_vScale.y / 2.0)
		{
			clamp.x = -box->m_vScale.x / 2.0f;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = -box->m_vScale.z / 2.0f;
			bExtremeClamp = false;
		}

	}
	if (overAllDistance.z < 0 && overAllDistance.x > 0) // behind and right 
	{
		if (localSphere.m_vCenter.y < box->m_vScale.y / 2.0f && localSphere.m_vCenter.y > -box->m_vScale.y / 2.0f)
		{
			clamp.x = box->m_vScale.x / 2.0f;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = -box->m_vScale.z / 2.0f;
			bExtremeClamp = false;
		}

	}
	if (overAllDistance.z > 0 && overAllDistance.x > 0) // infront and right 
	{
		if (localSphere.m_vCenter.y < box->m_vScale.y / 2.0f && localSphere.m_vCenter.y > -box->m_vScale.y / 2.0f)
		{
			clamp.x = box->m_vScale.x / 2.0f;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = box->m_vScale.z / 2.0f;
			bExtremeClamp = false;
		}

	}
	if (overAllDistance.z > 0 && overAllDistance.x < 0) // infront and left 
	{
		if (localSphere.m_vCenter.y < box->m_vScale.y / 2.0f && localSphere.m_vCenter.y > -box->m_vScale.y / 2.0f)
		{
			clamp.x = -box->m_vScale.x / 2.0f;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = box->m_vScale.z / 2.0f;
			bExtremeClamp = false;
		}

	}

	//extreme clamps
	if (bExtremeClamp)
	{
		if (overAllDistance.x < 0) clamp.x = 0 - (box->m_vScale.x / 2.0f);
		if (overAllDistance.x >= 0) clamp.x = 0 + (box->m_vScale.x / 2.0f);
		if (overAllDistance.y < 0) clamp.y = 0 - (box->m_vScale.y / 2.0f);
		if (overAllDistance.y >= 0) clamp.y = 0 + (box->m_vScale.y / 2.0f);
		if (overAllDistance.z < 0) clamp.z = 0 - (box->m_vScale.z / 2.0f);
		if (overAllDistance.z >= 0) clamp.z = 0 + (box->m_vScale.z / 2.0f);
	}


	//find dist from clamp to center of circle
	glm::vec3 dist = clamp - localSphere.m_vCenter;
	float fDist = abs(sqrt((dist.x * dist.x) + (dist.y * dist.y) + (dist.z * dist.z)));
	//subract the radius
	fDist = fDist - localSphere.m_fRadius;

	overAllDistance = box->m_vScale + localSphere.m_vCenter;

	if ((fDist <= 0 + EPSILON ) || (abs(overAllDistance.x) < abs(box->m_vScale.x / 2) && abs(overAllDistance.y) < abs(box->m_vScale.y / 2) && abs(overAllDistance.z) < abs(box->m_vScale.z / 2)))
	{
		//check for physical component on sphere
		if (eSphere->has<Physical>() && eBox->has<Physical>())
		{
			//find collison normal
			glm::vec3 Normal = localSphere.m_vCenter - clamp;
			glm::vec3 newVector = Normal;
			newVector = glm::normalize(newVector);
			newVector *= localSphere.m_fRadius;
			Normal = Normal - newVector;

			float d = abs(sqrt((Normal.x * Normal.x) + (Normal.y * Normal.y) + (Normal.z * Normal.z)));

			Normal = glm::normalize(Normal);
			Normal = -Normal;

			//find the penetration depth
			float PenetrationDepth = localSphere.m_fRadius - d;

			resolveCollision(eBox, eSphere, Normal);
			PositionalCorrection(eBox, eSphere, PenetrationDepth, Normal);
		}

		return true;
	}
	else
	{
		return false;
	}

}

bool System::Physics::CheckOBBCapsuleCollision(std::shared_ptr<Entity> eCap, std::shared_ptr<Entity> eBox)
{
	// check the OBB against the capsules OBB
	if (CheckOBBOBBCollision(eCap, eBox)) return true;


	//move the sphere to capsule spher pos one
	auto sphere = eCap->get<Sphere>();
	auto cap = eCap->get<Capsule>();
	sphere->m_vCenter = cap->m_vSphereCenter1;

	// check the OBB against the capsules Sphere
	if (CheckOBBOBBCollision(eBox, eCap)) return true;

	//move sphere to cap pos 2
	sphere->m_vCenter = cap->m_vSphereCenter2;

	// check the OBB against the capsules Sphere
	if (CheckOBBOBBCollision(eBox, eCap)) return true;


	return false;
}

bool System::Physics::CheckSphereCapsuleCollision(std::shared_ptr<Entity> eCap, std::shared_ptr<Entity> eSphere)
{
	// check the Sphere against the capsules OBB
	if (CheckOBBSphereCollision(eCap, eSphere)) return true;

	//move the sphere to capsule spher pos one
	auto sphere = eCap->get<Sphere>();
	auto cap = eCap->get<Capsule>();
	sphere->m_vCenter = cap->m_vSphereCenter1;

	// check the OBB against the capsules Sphere
	if (CheckShereSphereCollision(eSphere, eCap)) return true;

	//move sphere to cap pos 2
	sphere->m_vCenter = cap->m_vSphereCenter2;

	// check the OBB against the capsules Sphere
	if (CheckShereSphereCollision(eSphere, eCap)) return true;


	return false;
}

bool System::Physics::CheckCapsuleCapsuleCollision(std::shared_ptr<Entity> eCap1, std::shared_ptr<Entity> eCap2)
{
	//check  capsule 1 obb against capsule 2
	if (CheckOBBCapsuleCollision(eCap2, eCap1))return true;

	//move the sphere to capsule spher pos one
	auto sphere = eCap1->get<Sphere>();
	auto cap = eCap1->get<Capsule>();
	sphere->m_vCenter = cap->m_vSphereCenter1;

	//check capsule 1 sphere aginst capsule 2
	if (CheckSphereCapsuleCollision(eCap2, eCap1))return true;


	//move sphere to cap pos 2
	sphere->m_vCenter = cap->m_vSphereCenter2;

	//check capsule 1 sphere aginst
	if (CheckSphereCapsuleCollision(eCap2, eCap1))return true;

	return false;

}

void System::Physics::updateOBB(std::shared_ptr<Entity> eBox)
{
	auto box = eBox->get<OBB>();
	auto tBox = eBox->get<Component::Transformable>();

	box->m_Rotation = glm::rotate(box->m_Rotation, tBox->m_vRotation.x, glm::vec3(1.0f, 0.0, 0.0f));
	box->m_Rotation = glm::rotate(box->m_Rotation, tBox->m_vRotation.y, glm::vec3(0.0f, 1.0, 0.0f));
	box->m_Rotation = glm::rotate(box->m_Rotation, tBox->m_vRotation.z, glm::vec3(0.0f, 0.0, 1.0f));

	box->m_vCenter = tBox->getPosition() - box->m_vLocalPos;
	box->m_vPosition = glm::mat3(box->m_Rotation) * (box->m_vCenter - (box->m_vScale / 2.0f));

}

void System::Physics::updateAABB(std::shared_ptr<Entity> eBox)
{

	auto box = eBox->get<AABB>();
	auto tBox = eBox->get<Component::Transformable>();

	box->m_vCenter = tBox->getPosition() - box->m_vLocalTransform;
	box->m_vPosition = box->m_vCenter - (box->m_vScale / 2.0f);

	

}

void System::Physics::updatePhysicals(std::shared_ptr<Entity> e, float dt)
{
	//get transformable and physical
	auto trans = e->get<Component::Transformable>();
	auto phys = e->get<Physical>();
	

	if (phys->m_fINVMass != 0) // infinit mass , do not apply forces to it
	{
		//update velocity//apply drag //apply gravity
		phys->m_vVelocity.y += -0.5;
		//calculate drag
		glm::vec3 drag(phys->m_vVelocity.x * DRAG * -GRAVITYCOEFFICENT, phys->m_vVelocity.y * DRAG * -GRAVITYCOEFFICENT, phys->m_vVelocity.z * DRAG * -GRAVITYCOEFFICENT);

		phys->m_vVelocity += (phys->getAcceleration() - drag) * dt;
		trans->m_vPosition += phys->m_vVelocity;
	

		if (abs(phys->m_vAcceleration.x) < EPSILON) phys->m_vAcceleration.x = 0;
		if (abs(phys->m_vAcceleration.y) < EPSILON) phys->m_vAcceleration.y = 0;
		if (abs(phys->m_vAcceleration.z) < EPSILON) phys->m_vAcceleration.z = 0;


	}
	else
	{
		phys->m_vVelocity = glm::vec3(0, 0, 0);
		phys->m_vAcceleration = glm::vec3(0, 0, 0);
	}
}

void System::Physics::updateSphere(std::shared_ptr<Entity> eSphere)
{
	auto trans1 = eSphere->get<Component::Transformable>();
	auto sphere = eSphere->get<Sphere>();

	sphere->m_vCenter = trans1->getPosition() - sphere->m_localCenter;

}

void System::Physics::resolveCollision(std::shared_ptr<Entity> object1, std::shared_ptr<Entity> object2, glm::vec3 CollisionNormal)
{
	//get physicals and transformables
	auto trans1 = object1->get<Component::Transformable>();
	auto phys1 = object1->get<Physical>();

	auto trans2 = object2->get<Component::Transformable>();
	auto phys2 = object2->get<Physical>();

	//calculate relative velocity
	glm::vec3 vRelVel = phys2->m_vVelocity - phys1->m_vVelocity;

	//calculate velocity along normal
	float fRelVelocity = glm::dot(vRelVel, CollisionNormal);

	//do not resolve if traverling away from
	if (fRelVelocity > 0)return;
	
	//calculate restitution
	//float e = std::min(phys1->m_fRestitution, phys2->m_fRestitution);
	float e = (phys1->m_fRestitution + phys2->m_fRestitution) / 2.0f;

	//calculate impulse scalar
	float j = -(1 + e) * fRelVelocity;
	j /= phys1->m_fINVMass + phys2->m_fINVMass;

	//Apply the impluse
	glm::vec3 impulse = j * CollisionNormal;
	phys1->m_vVelocity -= phys1->m_fINVMass * impulse ;
	phys2->m_vVelocity += phys2->m_fINVMass * impulse ;


}

void System::Physics::PositionalCorrection(std::shared_ptr<Entity> object1, std::shared_ptr<Entity> object2, float Depth, glm::vec3 CollisionNormal)
{
	
	//get physicals and transformables
	auto trans1 = object1->get<Component::Transformable>();
	auto phys1 = object1->get<Physical>();

	auto trans2 = object2->get<Component::Transformable>();
	auto phys2 = object2->get<Physical>();

	//find the smallest scale
	float scale1 = min(trans1->m_vScale.x, trans1->m_vScale.y);
	scale1 = min(scale1, trans1->m_vScale.z);

	float scale2 = min(trans2->m_vScale.x, trans2->m_vScale.y);
	scale2 = min(scale2, trans2->m_vScale.z);

	float scale = 1/min(scale1, scale2) ;
	if (scale > 0.8f) scale = 0.8f;
	if (scale < 0.01) scale = 0.01f;

	//reduces rounding errors in the hardware
	
	glm::vec3 correction = Depth / (phys1->m_fINVMass + phys2->m_fINVMass) * 0.025f * CollisionNormal;
	trans1->m_vPosition -= phys1->m_fINVMass * correction;
	trans2->m_vPosition += phys2->m_fINVMass * correction;

}

void System::Physics::broadPhase(float dt)
{
	m_vCheckSpheres.clear();
	m_vCheckOBBS.clear();
	m_vCheckCapsule.clear();

	//Reset recorded collision - previous entities this has collided with
	for (int i = 0; i < m_vAABBS.size(); i++) {
		m_vAABBS.at(i)->m_vCollidedWith.clear();
	}
	
	//process AABB
	for (int i = 0; i < m_vAABBS.size(); i++)
	{
		for (int x = 0; x < m_vAABBS.size(); x++)
		{
			if (i != x)
			{
				if (CheckAABBAABBCollision(m_vAABBS.at(i), m_vAABBS.at(x)))
				{

					CollisionReporter::getInstance()->notify(m_vAABBS.at(i), m_vAABBS.at(x));

					// these 2 entities need to be checked
					if (m_vAABBS.at(i)->has<Sphere>())
					{

						if ((find(m_vCheckSpheres.begin(), m_vCheckSpheres.end(), m_vAABBS.at(i))) != m_vCheckSpheres.end())
						{
							//dont add
						}
						else
						{
							m_vCheckSpheres.push_back(m_vAABBS.at(i));
							auto sphere = m_vAABBS.at(i)->get<Physical>();

						}
					}

					if (m_vAABBS.at(x)->has<Sphere>())
					{

						if ((find(m_vCheckSpheres.begin(), m_vCheckSpheres.end(), m_vAABBS.at(x))) != m_vCheckSpheres.end())
						{
							//dont add
						}
						else
						{
							m_vCheckSpheres.push_back(m_vAABBS.at(x));
						}
					}

					if (m_vAABBS.at(i)->has<OBB>())
					{

						if ((find(m_vCheckOBBS.begin(), m_vCheckOBBS.end(), m_vAABBS.at(i))) != m_vCheckOBBS.end())
						{
							//dont add
						}
						else
						{
							m_vCheckOBBS.push_back(m_vAABBS.at(i));
						}
					}
					if (m_vAABBS.at(x)->has<OBB>())
					{

						if ((find(m_vCheckOBBS.begin(), m_vCheckOBBS.end(), m_vAABBS.at(x))) != m_vCheckOBBS.end())
						{
							//dont add
						}
						else
						{
							m_vCheckOBBS.push_back(m_vAABBS.at(x));
						}
					}

					if (m_vAABBS.at(i)->has<Capsule>())
					{


						if ((find(m_vCheckCapsule.begin(), m_vCheckCapsule.end(), m_vAABBS.at(i))) != m_vCheckCapsule.end())
						{
							//dont add
						}
						else
						{
							m_vCheckCapsule.push_back(m_vAABBS.at(i));
						}
					}

					if (m_vAABBS.at(x)->has<Capsule>())
					{


						if ((find(m_vCheckCapsule.begin(), m_vCheckCapsule.end(), m_vAABBS.at(x))) != m_vCheckCapsule.end())
						{
							//dont add
						}
						else
						{
							m_vCheckCapsule.push_back(m_vAABBS.at(x));
						}
					}

				}
			}
		}
	}
}

void System::Physics::narrowPhase(float dt)
{
	
	//process OBB
	for (int i = 0; i < m_vCheckOBBS.size(); i++)
	{
		for (int x = 0; x < m_vCheckOBBS.size(); x++)
		{
			if (i != x)
			{
				if (m_vCheckOBBS[i]->has<Physical>() && m_vCheckOBBS[x]->has<Physical>())
				{
					auto sphys1 = m_vCheckOBBS[i]->get<Physical>();
					auto sphys2 = m_vCheckOBBS[x]->get<Physical>();
					if (sphys1->m_fINVMass == 0 && sphys2->m_fINVMass == 0)
					{
						//dont process
					}
					else
					{
						CheckOBBOBBCollision(m_vCheckOBBS.at(i), m_vCheckOBBS.at(x));
					}
				}
				else
				{
					CheckOBBOBBCollision(m_vCheckOBBS.at(i), m_vCheckOBBS.at(x));
				}
			}
		}
	}

	//process Sphere
	for (int i = 0; i < m_vCheckSpheres.size(); i++)
	{
		for (int x = 0; x < m_vCheckSpheres.size(); x++)
		{
			if (i != x)
			{
				if (m_vCheckSpheres[i]->has<Physical>() && m_vCheckSpheres[x]->has<Physical>())
				{
					auto sphys1 = m_vCheckSpheres[i]->get<Physical>();
					auto sphys2 = m_vCheckSpheres[x]->get<Physical>();
					if (sphys1->m_fINVMass == 0 && sphys2->m_fINVMass == 0)
					{
						//dont process
					}
					else
					{
						CheckShereSphereCollision(m_vCheckSpheres.at(i), m_vCheckSpheres.at(x));
					}
				}
				else
				{
					CheckShereSphereCollision(m_vCheckSpheres.at(i), m_vCheckSpheres.at(x));
				}
			}
		}

	}

	//process Sphere Box Collision
	for (int i = 0; i < m_vCheckSpheres.size(); i++)
	{
		for (int x = 0; x < m_vCheckOBBS.size(); x++)
		{

			if (m_vCheckSpheres[i]->has<Physical>() && m_vCheckOBBS[x]->has<Physical>())
			{
				auto sphys1 = m_vCheckSpheres[i]->get<Physical>();
				auto sphys2 = m_vCheckOBBS[x]->get<Physical>();
				if (sphys1->m_fINVMass == 0 && sphys2->m_fINVMass == 0)
				{
					//dont process
				}
				else
				{
					CheckOBBSphereCollision(m_vCheckOBBS.at(x), m_vCheckSpheres.at(i));
				}
			}
			else
			{
				CheckOBBSphereCollision(m_vCheckOBBS.at(x), m_vCheckSpheres.at(i));
			}

		}

	}

	//process OBB Capsule collision
	for (int i = 0; i < m_vCheckOBBS.size(); i++)
	{
		for (int x = 0; x < m_vCheckCapsule.size(); x++)
		{
			if (m_vCheckOBBS[i]->has<Physical>() && m_vCheckCapsule[x]->has<Physical>())
			{
				auto sphys1 = m_vCheckOBBS[i]->get<Physical>();
				auto sphys2 = m_vCheckCapsule[x]->get<Physical>();
				if (sphys1->m_fINVMass == 0 && sphys2->m_fINVMass == 0)
				{
					//dont process
				}
				else
				{
					CheckOBBCapsuleCollision(m_vCheckCapsule.at(x), m_vCheckOBBS.at(i));
				}
			}
			else
			{
				CheckOBBCapsuleCollision(m_vCheckCapsule.at(x), m_vCheckOBBS.at(i));
			}
		

		}

	}
	//process Sphere Capsule collision
	for (int i = 0; i < m_vCheckSpheres.size(); i++)
	{
		for (int x = 0; x < m_vCheckCapsule.size(); x++)
		{
			if (m_vCheckSpheres[i]->has<Physical>() && m_vCheckCapsule[x]->has<Physical>())
			{
				auto sphys1 = m_vCheckSpheres[i]->get<Physical>();
				auto sphys2 = m_vCheckCapsule[x]->get<Physical>();
				if (sphys1->m_fINVMass == 0 && sphys2->m_fINVMass == 0)
				{
					//dont process
				}
				else
				{
					CheckSphereCapsuleCollision(m_vCheckCapsule.at(x), m_vCheckSpheres.at(i));
				}
			}
			else
			{
				CheckSphereCapsuleCollision(m_vCheckCapsule.at(x), m_vCheckSpheres.at(i));
			}
			

		}

	}
	//process Capsule Capsule collision
	for (int i = 0; i < m_vCheckCapsule.size(); i++)
	{
		for (int x = 0; x < m_vCheckCapsule.size(); x++)
		{
			if (i != x)
			{
				if (m_vCheckCapsule[i]->has<Physical>() && m_vCheckCapsule[x]->has<Physical>())
				{
					auto sphys1 = m_vCheckCapsule[i]->get<Physical>();
					auto sphys2 = m_vCheckCapsule[x]->get<Physical>();
					if (sphys1->m_fINVMass == 0 && sphys2->m_fINVMass == 0)
					{
						//dont process
					}
					else
					{
						CheckSphereCapsuleCollision(m_vCheckCapsule.at(x), m_vCheckCapsule.at(i));
					}
				}
				else
				{
					CheckSphereCapsuleCollision(m_vCheckCapsule.at(x), m_vCheckCapsule.at(i));
				}
				
			}
		}

	}
}

void System::Physics::applyImpulse(glm::vec3 Normal, float force, std::shared_ptr<Entity> object)
{
	//get physicals and transformables
	auto trans = object->get<Component::Transformable>();
	auto phys = object->get<Physical>();

	// find the acceleration
	//f = ma

	float Acceleration = force / phys->m_fMass;

	//multiply normal my accerlation
	phys->m_vVelocity +=  Normal * Acceleration;
}
