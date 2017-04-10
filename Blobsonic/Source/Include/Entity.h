/*
*	@class Entity
*	@brief Container for components
*/

#pragma once

#include <map>
#include <memory>
#include <typeindex>

class Entity {
private:
	bool m_bDestroy;
	std::map<std::type_index, std::shared_ptr<void>> m_components;
public:
	Entity() {}
	~Entity() {}

	template<typename T, typename... Args>
	T &attach(Args &&...args) {
		m_components[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
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
			terminate();
		}
	}

	template<typename T>
	void removeComponent() {
		m_components.erase(typeid(T));
	}

	void destroy();

	bool isDestroyed();
};