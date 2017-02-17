#include <stdafx.h>
#include "GameObject.h"

OC::GameObject::GameObject()
{
}

void OC::GameObject::sendMessage(Message * msg)
{
}

void OC::GameObject::update(float dt)
{

}

void OC::GameObject::handleGlobalMessages()
{
	if (m_vptrGlobalMessages != NULL) {
		for (auto it = m_vptrGlobalMessages->begin(); it != m_vptrGlobalMessages->end(); ++it) {

		}
	}
}

void OC::GameObject::handleLocalMessages()
{
	if (m_vptrGlobalMessages != NULL) {
		for (auto it = m_vptrLocalMessages->begin(); it != m_vptrLocalMessages->end(); ++it) {

		}
	}
}