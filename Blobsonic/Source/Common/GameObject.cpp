#include <stdafx.h>
#include "GameObject.h"

void OC::GameObject::handleMessages()
{
	for (auto it = m_vptrComponents.begin(); it != m_vptrComponents.end(); ++it) {
		for (int i = 0; i < m_vptrLocalMessages.size(); i++) {
			(*it)->handleMessage(m_vptrLocalMessages.at(i));
		}
	}
}

void OC::GameObject::sendMessage(Message * msg)
{

}

void OC::GameObject::sendLocalMessage(std::shared_ptr<Message> msg)
{
	m_vptrLocalMessages.push_back(msg);
}

void OC::GameObject::update(float dt)
{
	handleMessages();

	//Update all attached components
	for (auto it = m_vptrComponents.begin(); it != m_vptrComponents.end(); ++it) {
		(*it)->update(dt);
	}
	m_vptrLocalMessages.clear();
}

void OC::GameObject::attachComponent(std::unique_ptr<ObjectComponent> component)
{
	m_vptrComponents.push_back(std::move(component));
}
