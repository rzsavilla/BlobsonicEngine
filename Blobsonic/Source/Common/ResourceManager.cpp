#include <stdafx.h>
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

void ResourceManager::addMesh(std::string name, std::shared_ptr<Mesh> mesh) {
	m_meshes.emplace(name, mesh);
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

std::shared_ptr<Mesh> ResourceManager::getMesh(const std::string& name) {
	auto mesh = m_meshes.find(name);
	if (mesh != m_meshes.end()) {
		return mesh->second;
	}
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& name) {
	auto texture = m_textures.find(name);
	if (texture != m_textures.end()) {
		return texture->second;
	}
}

std::shared_ptr<Material> ResourceManager::getMaterial(const std::string& name) {
	auto material = m_materials.find(name);
	if (material != m_materials.end()) {
		return material->second;
	}
}

std::shared_ptr<GLSLProgram> ResourceManager::getShader(const std::string& name) {
	auto shader = m_shaders.find(name);
	if (shader != m_shaders.end()) {
		return shader->second;
	}
}
