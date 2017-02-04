#include <stdafx.h>
#include "Render.h"

Render::Render()
{
}

void Render::setWindow(GLFWwindow * ptr)
{
	m_ptrWindow = ptr;
}

void Render::init()
{

}

void Render::handleMessage(std::shared_ptr<Message> msg)
{
	//Place object to be drawn in vector, ready to be drawn
	if (msg->sID == "Render_Draw") {
		//Get data from message
		std::shared_ptr<Drawable> drawable = static_cast<RenderComponent::Draw*>(msg.get())->drawObj;
		//Store data
		m_ptrDrawObjects.push_back(drawable);	
	}
	else if (msg->sID == "SetWindow") {
		//Get data from message
		m_ptrWindow = static_cast<SetWindow*>(msg.get())->window;
	}
	else if (msg->sID == "Scene_Reload") {
		m_ptrDrawObjects.clear();				//Empty array of objects to be drawn
	}
}

void Render::update(float dt)
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	for (auto objIt = m_ptrDrawObjects.begin(); objIt != m_ptrDrawObjects.end(); ++objIt) {
		(*objIt)->draw();
	}
	m_ptrDrawObjects.clear();	//All objects have been drawn, clear vector

	glfwSwapInterval(1);			//VSYNC
	glfwSwapBuffers(m_ptrWindow);
}
