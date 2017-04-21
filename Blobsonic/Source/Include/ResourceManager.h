#pragma once

#include <stdafx.h>
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Text.h"
#include "GLSLProgram.h"
#include "AssimpMesh.h"

#include "MessageHandler.h"

class ResourceManager {
private:
	std::map<std::string, std::shared_ptr<Mesh>> m_meshes;
	std::map<std::string, std::shared_ptr<AssimpMesh>> m_vAssimpMeshes;
	std::map<std::string, std::shared_ptr<Texture>> m_textures;
	std::map<std::string, std::shared_ptr<Material>> m_materials;
	std::map<std::string, std::shared_ptr<GLSLProgram>> m_shaders;

	std::vector<std::string> m_vsLoadedResFiles;	//!< Stores file locations of loaded ResourceFiles
public:
	ResourceManager();

	void addMesh(std::string name, std::shared_ptr<Mesh> mesh);

	void addAssimpMesh(std::string ID, std::shared_ptr<AssimpMesh> newaMesh);

	void addTexture(std::string name, std::shared_ptr<Texture> texture);

	void addMaterial(std::string name, std::shared_ptr<Material> material);

	void addShader(std::string name, std::shared_ptr<GLSLProgram> shader);

	void addLoadedResFile(std::string file);	//!< Record Resource file that has been added

	void removeLoadedResFile(std::string file);	//!< Remove loaded Resource file from list

	std::shared_ptr<Mesh> getMesh(const std::string& name);

	std::shared_ptr<AssimpMesh> getAssimpMesh(const std::string& ID);

	std::shared_ptr<Texture> getTexture(const std::string& name);

	std::shared_ptr<Material> getMaterial(const std::string& name);

	std::shared_ptr<GLSLProgram> getShader(const std::string& name);

	bool isResFileLoaded(std::string file);	//!< Check if resource file has been loaded
};