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


static std::shared_ptr<EntityFactory> m_EntityFactory = std::make_shared<EntityFactory>();

LuaEntity::LuaEntity()
{
	m_entity = std::make_shared<Entity>();	//Pointer to handled entity
	MessageHandler::getInstance()->sendMessage<SceneMessage::AddEntity>(m_entity);
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
		m_entity->attach<AABB>();	//Attach component
	}
	auto aabb = m_entity->get<AABB>();	//Get Component
												//Read variables from lua table
	for (auto it = t.begin(); it != t.end(); ++it) {
		auto key = (*it).first;	//Get element key
		std::string s = key.as<std::string>();		//Get element value
		if (key.get_type() == sol::type::string) {
			auto value = (*it).second;
			//Set Component variables
			if (value.get_type() == sol::type::table) {
				if (s == "Dimensions") {
					aabb->m_vDimensions = LuaHelper::readVec3((*it).second);
				}
			}
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
			if (value.get_type() == sol::type::number) {
				if (s == "Dimensions") {
					obb->m_vDimensions = LuaHelper::readVec3((*it).second);
				}
			}
			else if (value.get_type() == sol::type::table) {
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
	lua_pushnil(m_activeScript);  // first key
	//Iterate through table elements
	for (auto it = t.begin(); it != t.end(); ++it) {
		auto key = (*it).first;	//Get element key
		if (key.get_type() == sol::type::string) {
			//Only process string keys
			std::string s = key.as<std::string>();		//Get key value
			auto value = (*it).second;					//Get value this should be a table
			//Read table data
			if (key.get_type() == sol::type::string) {
				if (value.is<sol::table>()) {
					//Set variables
					if (s == "Transformable") { setTransformable(value); }
					else if (s == "Model") { setModel(value); }
					else if (s == "Physical") { setPhysical(value); }
					else if (s == "AABB") { setAABB(value); }
					else if (s == "Sphere") { setSphere(value); }
					else if (s == "OBB") { setOBB(value); }
				}
			}
		}
	}
}

bool LuaEntity::hasComponent(const std::string & sComponent)
{
	if (sComponent == "Transformable") return m_entity->has<Component::Transformable>();
	else if (sComponent == "Model") return m_entity->has<Component::Model>();;
}

unsigned int LuaEntity::getID()
{
	return this->m_entity->getUID();
}

void LuaEntity::tSetPosition(float x, float y, float z)
{
	if (m_entity->has<Component::Transformable>()) {
		auto t = m_entity->get<Component::Transformable>();
		t->setPosition(glm::vec3(x,y,z));
	}
}

void LuaEntity::tSetRotation(float x, float y, float z)
{
	if (m_entity->has<Component::Transformable>()) {
		auto t = m_entity->get<Component::Transformable>();
		t->setRotation(glm::vec3(x, y, z));
	}
}

void LuaEntity::tSetScale(float x, float y, float z)
{
	if (m_entity->has<Component::Transformable>()) {
		auto t = m_entity->get<Component::Transformable>();
		t->setScale(glm::vec3(x, y, z));
	}
}

void LuaEntity::tSetOrigin(float x, float y, float z)
{
	if (m_entity->has<Component::Transformable>()) {
		auto t = m_entity->get<Component::Transformable>();
		t->setOrigin(glm::vec3(x, y, z));
	}
}

void LuaEntity::pSetMass(float newMass)
{
	if (m_entity->has<Physical>()) {
		auto p = m_entity->get<Physical>();
		p->setMass(newMass);
	}
}

void LuaEntity::pSetInvMass(float newInvMass)
{
	if (m_entity->has<Physical>()) {
		auto p = m_entity->get<Physical>();
		p->setMass(newInvMass);
	}
}

void LuaEntity::pSetRestitution(float newRestituion)
{
	if (m_entity->has<Physical>()) {
		auto p = m_entity->get<Physical>();
		p->setMass(newRestituion);
	}
}

void LuaEntity::pSetVelocity(float x, float y, float z)
{
	if (m_entity->has<Physical>()) {
		auto p = m_entity->get<Physical>();
		p->setVelocity(glm::vec3(x, y, z));
	}
}

void LuaEntity::destroy()
{
	if (m_entity)(m_entity->destroy());
}

void LuaEntity::register_lua(lua_State* L)
{
	//if (!m_lua_state) m_lua_state = L;
	if (!m_activeScript) m_activeScript = L;
	sol::state_view state(L);

	state.new_usertype<LuaEntity>("Entity",
		//Entity
		"setComponents", &LuaEntity::setComponents,
		"getID", &LuaEntity::getID,
		"destroy", &LuaEntity::destroy,
		//Transformable
		"tSetPosition", &LuaEntity::tSetPosition,
		"tSetRotation", &LuaEntity::tSetRotation,
		"tSetScale", &LuaEntity::tSetScale,
		"tSetOrigin", &LuaEntity::tSetOrigin,
		//Physical
		"pSetMass", &LuaEntity::pSetMass,
		"pSetInvMass", &LuaEntity::pSetInvMass,
		"pSetRestitution", &LuaEntity::pSetRestitution,
		"pSetVelocity", &LuaEntity::pSetVelocity

	);
}
