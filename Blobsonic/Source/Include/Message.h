#pragma once

#include <stdafx.h>

struct Message {
	std::string sID;
};


//#pragma once
//
//#include <stdafx.h>
//#include <string>
//
///**
//* @file	Message
//* Message used to communicate with components or pass data
//*/
//
///*! 
//	Message stores an ID which indicates its purpose
//	and the data that it stores.
//
//	It is used to pass data/commands/instructions to or between components
//*/

//struct Message {
//	Message() {}
//	//Abstract struct
//	std::string sID;
//};

//
//struct SetPositionMessage : public Message {
//	SetPositionMessage(glm::vec3 newPos)
//		:vPos(newPos)
//	{
//		sID = "SetPosition";
//	}
//	glm::vec3 vPos;	//New Position data
//};
//
//struct KeyEvent : public Message {
//	KeyEvent(unsigned int key, bool isPressed)
//		: iKey(key)
//		, isDown(isPressed)
//	{
//		sID = "KeyEvent";
//	}
//
//	unsigned int iKey;
//	bool isDown;
//};
//
////Messages for passing input
//namespace InputMessage {
//	struct KeyPress : public Message {
//		KeyPress(int key, int action)
//			: iKey(key)
//			, iAction(action)
//		{
//			sID = "Input_KeyPress";
//		}
//		int iKey;
//		int iAction;
//	};
//
//	struct MouseMove : public Message {
//		MouseMove(double x, double y)
//			: dXPos(x)
//			, dYPos(y)
//		{
//			sID = "Input_MouseMove";
//		}
//		double dXPos;
//		double dYPos;
//	};
//
//	struct MouseClick : public Message {
//		MouseClick(bool isDown, int button)
//			: bIsDown(isDown)
//			, iButton(button)
//		{
//			sID = "Input_MouseClick";
//		}
//		bool bIsDown;
//		int iButton;
//	};
//};
//
//struct SetWindow : public Message {
//	SetWindow(GLFWwindow* obj)
//		:window(obj)
//	{
//		sID = "SetWindow";
//	}
//	GLFWwindow* window;		//Object to be drawn
//};
//
////Messages to change scenes or instructions for scenes
//namespace SceneMessage {
//	struct SceneSplash : public Message {
//		SceneSplash() { sID = "Scene_Splash"; }
//	};
//
//	struct StartScene : public Message {
//		StartScene() { sID = "Scene_Start"; }
//	};
//
//	struct GameScene : public Message {
//		GameScene() { sID = "Scene_Game"; }
//	};
//
//	struct Reload : public Message {
//		Reload() { sID = "Scene_Reload"; }
//	};
//
//	struct Exit : public Message {
//		Exit() { sID = "Scene_Exit"; }
//	};
//}
//
//namespace EngineMessage {
//	struct FrameCount : public Message {
//		FrameCount(int fps)
//			: iFrames(fps)
//		{ sID = "Engine_FrameCount"; }
//		int iFrames;
//	};
//}