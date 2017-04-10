#pragma once

#include "Message.h"

namespace InputMessage {
	struct KeyPress : public Message {
		KeyPress(int key, int action)
			: m_iKey(key), m_iAction(action)
		{
			sID = "Input_KeyPress";	//Message ID
		}
		int m_iKey;			//!< GLFW Key ID
		int m_iAction;		//!< Key State/Action
	};
}