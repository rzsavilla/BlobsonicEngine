#include <stdafx.h>
#include "InputHandler.h"

/*

http://gamedev.stackexchange.com/questions/58541/how-can-i-associate-a-key-callback-with-a-wrapper-class-instance
*/

InputHandler::InputHandler()
{

}

void InputHandler::init()
{

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	g_keys.push_back(std::pair<int, int>(key, action));
}


void InputHandler::createKeyMessage()
{
	//for (auto it = g_keys.begin(); it != g_keys.end(); ++it) {
	//	m_ptrLocalMessages->push_back(std::make_shared<InputMessage::KeyPress>((*it).first,(*it).second));
	//}
}

void InputHandler::handleMessage(std::shared_ptr<Message> msg)
{
	//if (msg->sID == "SetWindow") {
	//	//Get data from message
	//	m_ptrWindow = static_cast<SetWindow*>(msg.get())->window;
	//	glfwSetKeyCallback(m_ptrWindow,key_callback);
	//}
}

void InputHandler::update(float dt)
{
	glfwPollEvents();
}
