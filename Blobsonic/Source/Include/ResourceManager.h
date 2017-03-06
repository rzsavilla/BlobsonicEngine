/**
* @class	ResourceManager
* @brief	Stores all resources
* Used to store and retrieve resources by string id
*/

#pragma once

#include <stdafx.h>
#include "Mesh.h"
#include "Texture.h"
#include "QuatCamera.h"
#include "Material.h"
#include "GLSLProgram.h"
#include "UI.h"

class ResourceManager {
private:
	std::vector<std::pair<std::string, Mesh>> m_vMeshes;			//!< Stores meshes
	std::vector<std::pair<std::string, Texture*>> m_vTextures;		//!< Stores textures
	std::vector<std::pair<std::string, Material>> m_vMaterials;		//!< Stores materials
	std::vector<std::pair<std::string, std::shared_ptr<GLSLProgram>>> m_vShaders;		//!<Stores shaders
	std::vector<std::pair<std::string, UI>> m_UI;

public:
	ResourceManager();	//!< Default constructor

	/**	Store a mesh
		Stores mesh into a vector of meshes.
	*/
	void addMesh(std::string ID, Mesh newMesh);

	/**	Store a mesh
		Stores texture into a vector of texture.
	*/
	void addTexture(std::string ID,Texture* newTexture);

	/**	Store a material
		Stores material into a vector of material.
	*/
	void addMaterial(std::string ID, Material newMaterial);

	/**	Store a shader program
	Stores shader program into a vector of GLSLShader.
	*/
	void addShader(std::string ID, std::shared_ptr<GLSLProgram> newShader);

	/** Returns pointer to pointer mesh
		\return Returns pointer to mesh element
	*/
	Mesh* getMesh(std::string ID);

	/** Returns pointer to pointer texture
		\return Returns pointer to texture element
	*/
	Texture* getTexture(std::string ID);

	/** Returns pointer to pointer material
		\return Returns pointer to material element
	*/
	Material* getMaterial(std::string ID);

	/** Returns pointer to shader pointer
		\return Returns pointer to shader element
	*/
	std::shared_ptr<GLSLProgram> getShader(std::string ID);
};