#include <stdafx.h>
#include "SplashScene.h"

SplashScene::SplashScene()
{
}

void SplashScene::initScene()
{
	timer.reset();
	//Create text
	m_LoadingText = std::make_shared<Text>("Loading", m_ptrCharacters, 350.0f, 400.0f, glm::vec3(1.0f, 0.0f, 0.0f), 2.0f);
	m_LoadingText->setShader(m_ptrResources->getShader("text_shader"));
}

void SplashScene::handleInput(GLFWwindow * window)
{

}

void SplashScene::update(float dt)
{
	if (timer.getElapsed() > 3.0f) {
		//Create message to switch scenes
		m_ptrMessages->push_back(std::make_shared<SceneMessage::GameScene>());
	}
	else {

	}
}

void SplashScene::draw()
{
	m_LoadingText->draw();
}
