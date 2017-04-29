#include "stdafx.h"
#include "Scene.h"

Scene::Scene(ResourceManager * res)
	:m_factory(res), m_ptrResources(res)
{

}

Scene::~Scene()
{
	clearScene();
}

void Scene::setResources(ResourceManager * res)
{
	m_ptrResources = res;
}

void Scene::clearScene()
{
	m_entities.destroyAll();
}