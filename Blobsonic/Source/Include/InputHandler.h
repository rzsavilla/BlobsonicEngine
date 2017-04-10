#pragma once

#include "stdafx.h"
#include "Component.h"

//Stores key press events
static std::vector<std::pair<int, int>> g_keys;

class InputHandler: public Component::Component {
private:
	GLFWwindow* m_ptrWindow;

	void createKeyMessage();
public:
	InputHandler();

	void init();

	void handleMessage(std::shared_ptr<Message> msg);

	void update(float dt);	

};