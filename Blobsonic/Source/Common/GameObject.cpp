#include <stdafx.h>
#include "GameObject.h"

void OC::GameObject::handleMessages(std::shared_ptr<Message> msg)
{
	for (auto it = m_vptrComponents.begin(); it != m_vptrComponents.end(); ++it) {
		for (auto jt = m_vptrMessages.begin(); jt != m_vptrMessages.end(); ++it) {
			(*it)->handleMessage((*jt));
		}
	}
}

OC::GameObject::GameObject()
{
}

void OC::GameObject::sendMessage(Message * msg)
{
}

void OC::GameObject::update(float dt)
{

}

void OC::GameObject::attachComponent(std::unique_ptr<ObjectComponent> component)
{
	m_vptrComponents.push_back(std::move(component));
}
