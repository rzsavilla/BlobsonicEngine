#include "stdafx.h"
#include "LuaEntity.h"

#include "SceneMessages.h"

//Components
#include "Player.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Transformable.h"
#include "Physical.h"
#include "AABB.h"
#include "Sphere.h"
#include "OBB.h"

#include "LuaScripting.h"

#include "Model.h"


static std::shared_ptr<EntityFactory> m_EntityFactory = EntityFactory::getInstance();

LuaEntity::LuaEntity()
{
	m_entity = NULL;
	CollisionReporter::getInstance()->attachReceiver(this);
}

LuaEntity::~LuaEntity()
{
	m_entity = NULL;
	CollisionReporter::getInstance()->dettachReceiver(this);
}

void LuaEntity::setTransformable(sol::table t)
{
	//Set Default variables
	glm::vec3 vPosition = glm::vec3(0.0f);
	glm::vec3 vRotation = glm::vec3(0.0f);
	glm::vec3 vScale = glm::vec3(1.0f);
	glm::vec3 vOrigin = glm::vec3(0.0f);

	if (!m_entity->has<Component::Transformable>()) {
		//Attach component
		m_entity->attach<Component::Transformable>();
	}
	//Get Component
	auto transform = m_entity->get<Component::Transformable>();

	//Read variables from lua table
	for (auto it = t.begin(); it != t.end(); ++it) {
		auto key = (*it).first;	//Get element key
		std::string s = key.as<std::string>();		//Get element value
		if (key.get_type() == sol::type::string) {
			//Set Component variables
			if (s == "Position")
				transform->setPosition(LuaHelper::readVec3((*it).second));
			else if (s == "Rotation")
				transform->setRotation(LuaHelper::readVec3((*it).second));
			else if (s == "Scale")
				transform->setScale(LuaHelper::readVec3((*it).second));
			else if (s == "Origin")
				transform->setOrigin(LuaHelper::readVec3((*it).second));
		}
	}
}

void LuaEntity::setModel(sol::table t)
{
	if (!m_entity->has<Component::Model>()) {
		m_entity->attach<Component::Model>();	//Attach component
	}
	auto model = m_entity->get<Component::Model>();	//Get Component

	auto res = ResourceManager::getInstance();

	//Read variables from lua table
	for (auto it = t.begin(); it != t.end(); ++it) {
		auto key = (*it).first;	//Get element key
		std::string s = key.as<std::string>();		//Get element value
		if (key.get_type() == sol::type::string) {
			auto value = (*it).second;
			if (value.get_type() == sol::type::string) {
				std::string sValue = value.as<std::string>();
				//Set Component variables
				if (s == "Mesh")
					model->addMesh(res->getAssimpMesh((sValue)));
				else if (s == "Material")
					model->addMaterial(res->getMaterial((sValue)));
				else if (s == "Texture")
					model->addTexture(res->getTexture((sValue)));
				else if (s == "Shader")
					model->setShader(res->getShader((sValue)));
			}
		}
	}
}

void LuaEntity::setPhysical(sol::table t)
{
	if (!m_entity->has<Physical>()) {
		m_entity->attach<Physical>();	//Attach component
	}
	auto physical = m_entity->get<Physical>();	//Get Component
	//Read variables from lua table
	for (auto it = t.begin(); it != t.end(); ++it) {
		auto key = (*it).first;	//Get element key
		std::string s = key.as<std::string>();		//Get element value
		if (key.get_type() == sol::type::string) {
			auto value = (*it).second;
			//Set Component variables
			if (value.get_type() == sol::type::number) {
				if (s == "Mass") {
					physical->setMass(value.as<float>());
				}
				else if (s == "INVMass") {
					physical->setfINVMass(value.as<float>());
				}
				else if (s == "Restitution") {
					physical->setRestitution(value.as<float>());
				}
			}
		}
	}
}

void LuaEntity::setAABB(sol::table t)
{
	if (!m_entity->has<AABB>()) {
		glm::vec3 vPos;
		glm::vec3 vDimenstions;
		glm::vec3 vScale = glm::vec3(1.0f);
		glm::vec3 vCenter = glm::vec3(0.0f);

		//Read variables from lua table
		for (auto it = t.begin(); it != t.end(); ++it) {
			auto key = (*it).first;	//Get element key
			std::string s = key.as<std::string>();		//Get element value
			if (key.get_type() == sol::type::string) {
				auto value = (*it).second;
				//Set Component variables
				if (value.get_type() == sol::type::table) {

				}
			}
		}

		//Attach component
		if (!m_entity->has<AABB>()) {
			m_EntityFactory->attachAABB(m_entity, vPos, vDimenstions, vScale);
		}
		else {
			//Set Component variables
			auto aabb = m_entity->get<AABB>();	//Get Component
		}
	}
}

void LuaEntity::setSphere(sol::table t)
{
	if (!m_entity->has<Sphere>()) {
		m_entity->attach<Sphere>();	//Attach component
	}
	auto sphere = m_entity->get<Sphere>();	//Get Component
										//Read variables from lua table
	for (auto it = t.begin(); it != t.end(); ++it) {
		auto key = (*it).first;	//Get element key
		std::string s = key.as<std::string>();		//Get element value
		if (key.get_type() == sol::type::string) {
			auto value = (*it).second;
			//Set Component variables
			if (value.get_type() == sol::type::number) {
				if (s == "Radius") {
					sphere->m_fRadius = (*it).second.as<float>();
				}
			}
			else if (value.get_type() == sol::type::table) {
				if (s == "Center") {
					sphere->m_vCenter = LuaHelper::readVec3((*it).second);
				}
			}
		}
	}
}

void LuaEntity::setOBB(sol::table t)
{
	if (!m_entity->has<OBB>()) {
		m_entity->attach<OBB>();	//Attach component
	}
	auto obb = m_entity->get<OBB>();	//Get Component
	//Read variables from lua table
	for (auto it = t.begin(); it != t.end(); ++it) {
		auto key = (*it).first;	//Get element key
		std::string s = key.as<std::string>();		//Get element value
		if (key.get_type() == sol::type::string) {
			auto value = (*it).second;
			//Set Component variables
			
			if (value.get_type() == sol::type::table) {
				if (s == "Center") {
					obb->m_vCenter = LuaHelper::readVec3((*it).second);
				}
			}
			else if (value.get_type() == sol::type::table) {
				if (s == "Position") {
					obb->m_vPosition = LuaHelper::readVec3((*it).second);
				}
			}
			else if (value.get_type() == sol::type::table) {
				if (s == "Scale") {
					obb->m_vScale = LuaHelper::readVec3((*it).second);
				}
			}
			else if (value.get_type() == sol::type::table) {
				if (s == "Rotation") {
					obb->m_vPosition = LuaHelper::readVec3((*it).second);
				}
			}
		}
	}
}

void LuaEntity::setComponents(sol::table t)
{
	//if (!m_entity) {
	//	//Create and add entity into the scene
	//	m_entity = std::make_shared<Entity>();	//Pointer to handled entity
	//	m_bDestroyed = false;
	//	MessageHandler::getInstance()->sendMessage<SceneMessage::AddEntity>(m_entity);

	//	lua_pushnil(m_activeScript);  // first key
	//	//Iterate through table elements
	//	for (auto it = t.begin(); it != t.end(); ++it) {
	//		auto key = (*it).first;	//Get element key
	//		if (key.get_type() == sol::type::string) {
	//			//Only process string keys
	//			std::string s = key.as<std::string>();		//Get key value
	//			auto value = (*it).second;					//Get value this should be a table
	//			//Read table data
	//			if (key.get_type() == sol::type::string) {
	//				if (value.is<sol::table>()) {
	//					//Set variables
	//					if (s == "Transformable") { setTransformable(value); }
	//					else if (s == "Model") { setModel(value); }
	//					else if (s == "Physical") { setPhysical(value); }
	//					else if (s == "AABB") { setAABB(value); }
	//					else if (s == "Sphere") { setSphere(value); }
	//					else if (s == "OBB") { setOBB(value); }
	//					
	//				}
	//				else if (value.is<std::string>()) {
	//					if (s == "Name") {
	//						//std::cout << "Name: " << value.as<std::string>() << "\n";
	//						m_entity->setName(value.as<std::string>());
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
}

void LuaEntity::handleEntity(const std::string & name)
{
	m_entity = SceneManager::getInstance()->getActiveScene()->getEntityManager()->getEntityByName(name);
}

bool LuaEntity::hasEntity()
{
	if (m_entity) {
		return true;
	}
	else {
		return false;
	}
}

bool LuaEntity::hasComponent(const std::string & sComponent)
{
	if (sComponent == "Transformable") return m_entity->has<Component::Transformable>();
	else if (sComponent == "Model") return m_entity->has<Component::Model>();;
}

unsigned int LuaEntity::getID()
{
	if (m_entity) {
		return this->m_entity->getUID();
	}
}

std::string LuaEntity::getName()
{
	if (m_entity) {
		return this->m_entity->getName();
	}
}

void LuaEntity::tSetPosition(float x, float y, float z)
{
	if (m_entity) {
		if (m_entity->has<Component::Transformable>()) {
			auto t = m_entity->get<Component::Transformable>();
			t->setPosition(glm::vec3(x, y, z));
		}
	}
}

void LuaEntity::tSetRotation(float x, float y, float z)
{
	if (m_entity) {
		if (m_entity->has<Component::Transformable>()) {
			auto t = m_entity->get<Component::Transformable>();
			t->setRotation(glm::vec3(x, y, z));
		}
	}
}

void LuaEntity::tSetScale(float x, float y, float z)
{
	if (m_entity) {
		if (m_entity->has<Component::Transformable>()) {
			auto t = m_entity->get<Component::Transformable>();
			t->setScale(glm::vec3(x, y, z));
		}
	}
}

void LuaEntity::tSetOrigin(float x, float y, float z)
{
	if (m_entity) {
		if (m_entity->has<Component::Transformable>()) {
			auto t = m_entity->get<Component::Transformable>();
			t->setOrigin(glm::vec3(x, y, z));
		}
	}
}

float LuaEntity::tGetPosX()
{
	if (m_entity) {
		if (m_entity->has<Component::Transformable>()) {
			auto t = m_entity->get<Component::Transformable>();
			return t->getPosition().x;
		}
	}
	else return 0;
}

float LuaEntity::tGetPosY()
{
	if (m_entity) {
		if (m_entity->has<Component::Transformable>()) {
			auto t = m_entity->get<Component::Transformable>();
			return t->getPosition().y;
		}
	}
	else return 0;
}

float LuaEntity::tGetPosZ()
{
	if (m_entity) {
		if (m_entity->has<Component::Transformable>()) {
			auto t = m_entity->get<Component::Transformable>();
			return t->getPosition().z;
		}
	}
	else return 0;
}

void LuaEntity::pSetMass(float newMass)
{
	if (m_entity) {
		if (m_entity->has<Physical>()) {
			auto p = m_entity->get<Physical>();
			p->setMass(newMass);
		}
	}
}

void LuaEntity::pSetInvMass(float newInvMass)
{
	if (m_entity) {
		if (m_entity->has<Physical>()) {
			auto p = m_entity->get<Physical>();
			p->setMass(newInvMass);
		}
	}
}

void LuaEntity::pSetRestitution(float newRestituion)
{
	if (m_entity) {
		if (m_entity->has<Physical>()) {
			auto p = m_entity->get<Physical>();
			p->setMass(newRestituion);
		}
	}
}

void LuaEntity::pSetVelocity(float x, float y, float z)
{
	if (m_entity) {
		if (m_entity->has<Physical>()) {
			auto p = m_entity->get<Physical>();
			p->setVelocity(glm::vec3(x, y, z));
		}
	}
}

void LuaEntity::pCollisionListen()
{

}

bool LuaEntity::pHasCollidedByID(int entityID)
{
	if (m_entity) {
		for (auto it = m_entity->m_vCollidedWith.begin(); it != m_entity->m_vCollidedWith.end(); ++it) {
			if ((*it)->getUID() == entityID) return true;
		}
	}
	return false;
}

int LuaEntity::pHasCollidedByName(std::string entityName)
{
	if (m_entity) {
		for (auto it = m_entity->m_vCollidedWith.begin(); it != m_entity->m_vCollidedWith.end(); ++it) {
			if ((*it)->getName() == entityName) return (*it)->getUID();
		}
	}
	return -1;	//No Collision
}

void LuaEntity::pApplyImpulse(float nx, float ny, float nz, float force)
{
	if (m_entity) {
		auto p = m_entity->get<Physical>();
		p->applyImpulse(glm::vec3(nx, ny, nz), force);
	}
}

void LuaEntity::pMove(float forwardX, float forwardY, float forwardZ, float speed)
{
	if (m_entity->has<Physical>()  && m_entity->has<Component::Transformable>()) {
		auto p = m_entity->get<Physical>();
		auto t = m_entity->get<Component::Transformable>();
		glm::vec4 vForward(forwardX, forwardY, forwardZ, 0.0f);
		vForward = t->getTransform() * vForward;			//Rotate forward vector
		p->applyImpulse(glm::vec3(vForward),speed);
	}
}

void LuaEntity::sPlay()
{
	if (m_entity->has<Component::Sound>() && m_entity->has<Component::Transformable>()) {
		auto p = m_entity->get<Physical>();
		auto s = m_entity->get<Component::Sound>();
		s->setPlaying(true);
	}
}

void LuaEntity::destroy()
{
	if (m_entity) {
		m_entity->destroy();
		//m_entity = NULL;
	}
	//m_bDestroyed = true;
	//CollisionReporter::getInstance()->dettachReceiver(this);
}

bool LuaEntity::isDestroyed()
{
	return m_bDestroyed;
}

void LuaEntity::log()
{
	if (m_entity) {
		//std::cout << "Entity: " << m_entity->getName() << "\n";
		if (m_entity->has<Component::Transformable>()) {
			auto t = m_entity->get<Component::Transformable>();
			std::cout << "- Pos: x:" << t->getPosition().x << " y:" << t->getPosition().y << " z:" << t->getPosition().z << std::endl;
			std::cout << "- Rot: x:" << t->getRotation().x << " y:" << t->getRotation().y << " z:" << t->getRotation().z << std::endl;
		}
		std::cout << "- Destroyed: " << m_entity->isDestroyed() << "\n";
	}
}

void LuaEntity::register_lua(lua_State* L)
{
	//if (!m_lua_state) m_lua_state = L;
	//if (!m_activeScript) m_activeScript = L;
	sol::state_view state(L);

	state.new_usertype<LuaEntity>("Entity",
		//Entity
		"setComponents", &LuaEntity::setComponents,
		"handleEntity", &LuaEntity::handleEntity,
		"hasEntity", &LuaEntity::hasEntity,
		"getID", &LuaEntity::getID,
		"getName", &LuaEntity::getName,
		"destroy", &LuaEntity::destroy,
		"isDestroyed", &LuaEntity::isDestroyed,
		"log", &LuaEntity::log,
		//Transformable
		"tSetPosition", &LuaEntity::tSetPosition,
		"tSetRotation", &LuaEntity::tSetRotation,
		"tSetScale", &LuaEntity::tSetScale,
		"tSetOrigin", &LuaEntity::tSetOrigin,
		"tGetPosX", &LuaEntity::tGetPosX,
		"tGetPosY", &LuaEntity::tGetPosY,
		"tGetPosZ", &LuaEntity::tGetPosZ,
		//Physical
		"pSetMass", &LuaEntity::pSetMass,
		"pSetInvMass", &LuaEntity::pSetInvMass,
		"pSetRestitution", &LuaEntity::pSetRestitution,
		"pSetVelocity", &LuaEntity::pSetVelocity,
		"pHasCollidedByID", &LuaEntity::pHasCollidedByID,
		"pHasCollidedByName", &LuaEntity::pHasCollidedByName,
		"pApplyImpulse", &LuaEntity::pApplyImpulse,
		"pMove", &LuaEntity::pMove,
		//Sound
		"sPlay",&LuaEntity::sPlay
	);
}

void LuaEntity::registerCollision(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2)
{
	//Check if this entity has collided
	if (entity1->getUID() == m_entity->getUID()) {
		//Record entity has collided with
		m_entity->m_vCollidedWith.push_back(entity2);
	}
}