#include <stdafx.h>
#include "ResourceManager.h"
#include "EngineMessages.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

std::shared_ptr<ResourceManager> ResourceManager::getInstance()
{
	static std::shared_ptr<ResourceManager> instance = nullptr;

	if (!instance) {
		instance.reset(new ResourceManager);
	}
	return instance;
}

void ResourceManager::addMesh(std::string name, std::shared_ptr<Mesh> mesh) {
	m_meshes.emplace(name, mesh);
}

void ResourceManager::addAssimpMesh(std::string name, std::shared_ptr<AssimpMesh> newaMesh)
{
	m_vAssimpMeshes.emplace(name, newaMesh);
}

void ResourceManager::addTexture(std::string name, std::shared_ptr<Texture> texture) {
	m_textures.emplace(name, texture);
}

void ResourceManager::addMaterial(std::string name, std::shared_ptr<Material> material) {
	m_materials.emplace(name, material);
}

void ResourceManager::addShader(std::string name, std::shared_ptr<GLSLProgram> shader) {
	m_shaders.emplace(name, shader);
}

void ResourceManager::addLoadedResFile(std::string file)
{
	m_vsLoadedResFiles.push_back(file);
}

void ResourceManager::removeLoadedResFile(std::string file)
{
	for (auto it = m_vsLoadedResFiles.begin(); it != m_vsLoadedResFiles.end(); ++it) {
		if ((*it) == file) {
			m_vsLoadedResFiles.erase(it);
			return;
		}
	}
}

std::shared_ptr<Mesh> ResourceManager::getMesh(const std::string& name) {
	auto mesh = m_meshes.find(name);
	if (mesh != m_meshes.end()) {
		return mesh->second;
	}
	if (m_bDebug) std::cout << "Mesh Could Not be Found: " + name << "\n";
	return NULL;
}

std::shared_ptr<AssimpMesh> ResourceManager::getAssimpMesh(const std::string& name)
{
	auto aMesh = m_vAssimpMeshes.find(name);
	if(aMesh != m_vAssimpMeshes.end()) {
		return aMesh->second;
	}
	if (m_bDebug) std::cout << "AssimpMesh Could Not be Found: " + name << "\n";
	return NULL;
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& name) {
	auto texture = m_textures.find(name);
	if (texture != m_textures.end()) {
		return texture->second;
	}
	if (m_bDebug) std::cout << "Texture Could Not be Found: " + name << "\n";
	return NULL;
}

std::shared_ptr<Material> ResourceManager::getMaterial(const std::string& name) {
	auto material = m_materials.find(name);
	if (material != m_materials.end()) {
		return material->second;
	}
	if (m_bDebug) std::cout << "Material Could Not be Found: " + name << "\n";
	return NULL;
}

std::shared_ptr<GLSLProgram> ResourceManager::getShader(const std::string& name) {
	auto shader = m_shaders.find(name);
	if (shader != m_shaders.end()) {
		return shader->second;
	}
}

bool ResourceManager::isResFileLoaded(std::string file)
{
	for (auto it = m_vsLoadedResFiles.begin(); it != m_vsLoadedResFiles.end(); ++it) {
		if ((*it) == file) {
			return true;		//File has already been loaded
		}
	}
	return false;
}

void ResourceManager::ClearResources()
{
	m_vsLoadedResFiles.clear();
	m_meshes.clear();
	m_vAssimpMeshes.clear();
	m_textures.clear();
	m_materials.clear();
	m_shaders.clear();
}
