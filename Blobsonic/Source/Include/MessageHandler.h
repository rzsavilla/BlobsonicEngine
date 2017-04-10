/**
* @class	Message Handler
* @brief	Stores messages for communication
* Only a single MessageHandler instance can exist (Singleton).
*/

//Singleton using smartpointer implementation guide
//http://silviuardelean.ro/2012/06/05/few-singleton-approaches/

#pragma once

#include <stdafx.h>
#include <typeindex>
#include <MessageReceiver.h>

class MessageHandler {
private:
	//---Singleton---
	MessageHandler();
	static std::shared_ptr<MessageHandler>& m_ptrInstance;
private:
	//--Observer Pattern--
	std::vector<MessageReceiver*> m_vReceivers;			//!< Pointer to objects that want to be notified
	std::vector<std::shared_ptr<Message>> m_vMessages;	//!< Messages
public:
	//---Singleton---
	~MessageHandler();
	static std::shared_ptr<MessageHandler> getInstance();

	void attachReceiver(MessageReceiver* receiver);

	void sendMessage(std::shared_ptr<Message> msg);

	void notify();	//!< Notify all receivers
};