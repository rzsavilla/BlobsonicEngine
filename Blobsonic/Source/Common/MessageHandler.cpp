#include <stdafx.h>
#include "MessageHandler.h"

MessageHandler::MessageHandler()
{

}

MessageHandler::~MessageHandler()
{
}

std::shared_ptr<MessageHandler> MessageHandler::getInstance()
{
	static std::shared_ptr<MessageHandler> instance = nullptr;

	if (!instance)
	{
		if (!instance) {
			instance.reset(new MessageHandler());
		}
	}
	return instance;
}

void MessageHandler::attachReceiver(MessageReceiver* receiver)
{
	m_vReceivers.push_back(receiver);
}

void MessageHandler::sendMessage(std::shared_ptr<Message> msg)
{
	m_vMessages.push_back(msg);
}

void MessageHandler::notify()
{
	for (auto it = m_vReceivers.begin(); it != m_vReceivers.end(); ++it) {
		(*it)->processMessages(&m_vMessages);
	}
	m_vMessages.clear();
}