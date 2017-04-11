#pragma once
/*
* @class	Mesh
* @brief	Mesh loaded from obj file
* Stores objects vertices, indices, normals, texture coordinates, will also parse the obj file
*/

#pragma once

#include <stdafx.h>
#include "ID.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "aModel.h"

class AssimpMesh {
public:
	string directory;
	void processNode(aiNode* node, const aiScene* scene);
	aModel processMesh(aiMesh* mesh, const aiScene* scene);
	GLint TextureFromFile(const char* path, string directory);

	std::vector<aModel> meshes;
	vector<aTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	vector<aTexture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

public:
	AssimpMesh();	//!< Default Constructor
	AssimpMesh(std::string sFilename);	//!< Constructor set to parse obj file
	bool load(std::string sFilename);	//!< Parse obj file

};
