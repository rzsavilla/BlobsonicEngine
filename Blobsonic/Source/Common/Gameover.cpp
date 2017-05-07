#include "stdafx.h"
#include "Button.h"
#include "SpriteRender.h"
#include "Transformable.h"
#include "Message.h"
#include "SceneManager.h"
#include "Gameover.h"
//Messages
#include "RenderMessages.h"
#include "EngineMessages.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Cursor callback functions
/// 
static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);
void cursorEnterCallback(GLFWwindow *window, int entered);

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos)
{
	std::cout << xPos << " : " << yPos << "\n";
}

void System::Gameover::addEntity(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>>* entities)
{
	for (auto it = entities->begin(); it != entities->end(); ++it) {

		if ((*it)->getUID() == entity->getUID()) {
			return;	//Entity already stored
		}
	}
	entities->push_back(entity);	//Store entity
}

System::Gameover::Gameover()
{

}

void System::Gameover::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	//Iterate through all entities
	for (auto it = entities->begin(); it != entities->end(); ++it) {
		if ((*it)->has<Component::Button>()) {
			addEntity((*it), &m_entities);
		}
	}
}

void System::Gameover::update(float dt)
{
	double x, y;

	/// Gets the x & y position of the cursor relative to the current window.
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	//cursorPositionCallback(glfwGetCurrentContext(), x, y);

	for (auto it = m_entities.begin(); it != m_entities.end(); ++it) {
		if ((*it)->has<Component::Transformable>()) {
			auto t = (*it)->get <Component::Transformable>();
			auto b = (*it)->get <Component::Button>();
			auto s = (*it)->get <Component::SpriteRenderer>();

			double xpos, ypos, width, height;

			/// Gets the x & y postion of the button
			xpos = t->getPosition().x;
			ypos = t->getPosition().y;

			/// Gets the width and height of the button
			width = t->getScale().x;
			height = t->getScale().y;

			/// gets the ID of the button
			int bID;
			bID = b->getButtonID();

			if (bID == 11) /// Energy bar
			{
				t->setScale(vec3(t->getScale().x - 0.1, t->getScale().y, 0.0));
				if (width <= 0.0f)
				{
					m_bNoEnergy = true;
					t->setScale(vec3(234.0f, t->getScale().y, 0.0));
					SceneManager::getInstance()->setLoadingScene("Loading.xml");
					SceneManager::getInstance()->changeScene("Gameover.xml", true);
				}
			}
		}
	}
	///Remove Destroyed Entities
	removeDestroyed(&m_entities);
}

void System::Gameover::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	for (auto it = msgs->begin(); it != msgs->end(); ++it) {
		if ((*it)->sID == "WindowResize")
		{
			auto data = static_cast<EngineMessage::WindowResize*>((*it).get());
		}
	}

}

void System::Gameover::removeDestroyed(std::vector<std::shared_ptr<Entity>>* entities)
{
	for (int i = 0; i < entities->size(); i++) {
		if (entities->at(i)->isDestroyed()) {
			entities->erase(entities->begin() + i);
		}
	}
}