/*
*	@class Entity
*	@brief Container for components
*	@author Rozen Savill
*	Components are stored within this object and are easily attached and detached
*/

#pragma once

#include <map>
#include <memory>
#include <typeindex>

#include "Destroyable.h"
#include "UniqueID.h"
#include "Name.h"

#include "Component.h"

static void LuaLoaded() {
	std::cout << "Lua is working\n";
}

class Entity: public Destroyable, public UniqueID, public std::enable_shared_from_this<Entity> , public Name {
private:
	std::map<std::type_index, std::shared_ptr<void>> m_components;

	const bool m_bDebug = true;	//!< Flag for Couts
public:
	Entity();
	
	~Entity();

	std::vector<std::shared_ptr<Entity>> m_vCollidedWith;	//!< Entities this has collided with cleared every tick

	template<typename T, typename... Args>
	T &attach(Args &&...args) {
		m_components[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
		
		std::shared_ptr<Component::Component> component;
		component = std::static_pointer_cast<Component::Component>(m_components[typeid(T)]);
		component->setParent(shared_from_this());
		return *get<T>();
	}

	template<typename T>
	bool has() {
		return m_components.find(typeid(T)) != m_components.end();
	}

	template<typename T>
	T *get() {
		if (has<T>()) {
			return std::static_pointer_cast<T>(m_components[typeid(T)]).get();
		}
		else {
			std::cout << "ERROR Could Not find Component\n";
			terminate();
		}
	}

	template<typename T>
	T* getComponentByID(const int id) {
		if (has<T>()) {	//Check if entity has component of type T
			for (auto it = m_components.begin(); it != m_components.end(); ++it) {
				Component::Component* comp = std::static_pointer_cast<Component::Component>((*it).second).get();

				if (comp->getUID() == id) {	//Component found
					if (m_bDebug) std::cout << "Component Found\n";
					return std::static_pointer_cast<T>(m_components[typeid(T)]).get();
				}
			}
		}
		//if (m_bDebug) std::cout << "Could Not find Component\n";
		return NULL;
	}

	template<typename T>
	void removeComponent() {
		m_components.erase(typeid(T));
	}
};