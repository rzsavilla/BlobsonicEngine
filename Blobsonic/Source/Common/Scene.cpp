#include "stdafx.h"
#include "Scene.h"

#include "ResourceManager.h"

Scene::Scene()
{
	m_ptrResources = ResourceManager::getInstance();
}

Scene::~Scene()
{
	clearScene();
}

void Scene::clearScene()
{
	m_entities.destroyAll();
}