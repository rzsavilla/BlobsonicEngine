#include "stdafx.h"
#include "Scene.h"

#include "ResourceManager.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	clearScene();
}

void Scene::clearScene()
{
	m_entities.destroyAll();
}