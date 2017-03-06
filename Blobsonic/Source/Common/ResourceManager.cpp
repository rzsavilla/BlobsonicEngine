#include <stdafx.h>
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

void ResourceManager::addMesh(std::string ID, Mesh newMesh)
{
	m_vMeshes.push_back(std::pair<std::string,Mesh>(ID,newMesh));
}

void ResourceManager::addTexture(std::string ID,Texture* newTexture)
{
	m_vTextures.push_back(std::pair<std::string,Texture*>(ID,newTexture));
}

void ResourceManager::addMaterial(std::string ID, Material newMaterial)
{
	m_vMaterials.push_back(std::pair<std::string, Material>(ID, newMaterial));
}

void ResourceManager::addShader(std::string ID, std::shared_ptr<GLSLProgram> newShader)
{
	m_vShaders.push_back(std::pair<std::string, std::shared_ptr<GLSLProgram>>(ID,newShader));
}

void ResourceManager::addUI(std::string ID, UI newUI)
{
	m_vUI.push_back(std::pair<std::string, UI>(ID, newUI));
}

Mesh* ResourceManager::getMesh(std::string ID)
{
	//Look through vector
	for (auto it = m_vMeshes.begin(); it != m_vMeshes.end(); ++it) {
		if ((*it).first == ID) {
			return &(*it).second;		//Returns mesh pointer
		}
	}
	return NULL;
}

Texture* ResourceManager::getTexture(std::string ID)
{
	//Look through vector
	for (auto it = m_vTextures.begin(); it != m_vTextures.end(); ++it) {
		if ((*it).first == ID) {
			return (*it).second;		//Returns texture pointer
		}
	}
	return NULL;
}

Material* ResourceManager::getMaterial(std::string ID)
{
	//Look through vector
	for (auto it = m_vMaterials.begin(); it != m_vMaterials.end(); ++it) {
		if ((*it).first == ID) {
			return &(*it).second;		//Returns material pointer
		}
	}
	return NULL;
}

std::shared_ptr<GLSLProgram> ResourceManager::getShader(std::string ID)
{
	//Look through vector
	for (auto it = m_vShaders.begin(); it != m_vShaders.end(); ++it) {
		if ((*it).first == ID) {
			return (*it).second;		//Returns shader pointer
		}
	}

	return NULL;
}

UI* ResourceManager::getUI(std::string ID)
{
	//Look through vector
	for (auto it = m_vUI.begin(); it != m_vUI.end(); ++it) {
		if ((*it).first == ID) {
			return &(*it).second;		//Returns material pointer
		}
	}
	return NULL;
}