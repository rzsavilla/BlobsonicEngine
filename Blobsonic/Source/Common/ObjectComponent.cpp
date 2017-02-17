#include <stdafx.h>
#include "ObjectComponent.h"

void OC::ObjectComponent::setGlobalMessagePtr(std::shared_ptr<Message> ptrGlobalMsg)
{
	m_vptrGlobalMessages->push_back(ptrGlobalMsg);
	m_bGlobalMsgs = true;
}

void OC::ObjectComponent::setLocalMessagePtr(std::shared_ptr<Message> ptrLocallMsg)
{
	m_vptrLocalMessages->push_back(ptrLocallMsg);
	m_bLocalMsgs = true;
}

void OC::ObjectComponent::sendLocalMsg(std::shared_ptr<Message> msg)
{
	m_vptrLocalMessages->push_back(msg);
}

void OC::ObjectComponent::setGlobalMsg(std::shared_ptr<Message> msg)
{
	m_vptrGlobalMessages->push_back(msg);
}

void OC::ObjectComponent::attachComponent(std::unique_ptr<ObjectComponent> newComponent)
{
	m_vptrComponents.push_back(std::move(newComponent));
}

void OC::ObjectComponent::attachGlobalMsg(std::vector<std::shared_ptr<Message>>* vptrMsgs)
{
	m_vptrGlobalMessages = vptrMsgs;
}

void OC::ObjectComponent::attachLocalMsg(std::vector<std::shared_ptr<Message>>* vptrMsgs)
{
	m_vptrLocalMessages = vptrMsgs;
}