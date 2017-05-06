#pragma once

#include "Message.h"

namespace EngineMessage {
	struct SetWindow : public Message {
		SetWindow(GLFWwindow* window)
			:m_ptrWindow(window)
		{
			sID = "SetWindow";
		}
		GLFWwindow* m_ptrWindow;
	};

	struct SwitchState : public Message {
		SwitchState(int newState)
			:m_iState(newState)
		{
			sID = "SwitchState";
		}
		int m_iState;
	};

	struct Exit : public Message {
		Exit() {
			sID = "Exit";
		};
	};

	struct WindowResize : public Message {
		WindowResize(unsigned int w, unsigned int h) {
			sID = "WindowResize";
			uiWidth = w;
			uiHeight = h;
		};
		unsigned uiWidth, uiHeight;
	};

	struct FullScreenToggle : public Message {
		FullScreenToggle(bool fullscreen) {
			sID = "FullScreenToggle";
			bFullScreen = fullscreen;
		}
		bool bFullScreen;
	};
}