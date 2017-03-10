/**
* @class	MessageReceiver
* @brief	Abstract class for receiving messages
* Class inherits this in order to be notified of messages
*/

#pragma once

#include <stdafx.h>
#include "Message.h"

class MessageReceiver {
public:
	virtual void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) = 0;
};