#include <stdafx.h>
#include "Component.h"

void Component::sendMessage(std::shared_ptr<Message> msg)
{
	m_ptrLocalMessages->push_back(msg);
}

void Component::setLocalMsgPtr(std::vector<std::shared_ptr<Message>>* ptr)
{
	m_ptrLocalMessages = ptr;
}
