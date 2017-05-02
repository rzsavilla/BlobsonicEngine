
#include "stdafx.h"

#include "AssimpMesh.h"
#include <algorithm>
#include <cctype>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "aModel.h"
#include "Texture.h"
#include "Math3D.h"

/* Code from https://learnopengl.com/#!Model-Loading/Model*/

typedef struct {
	float x, y, z;
	float nx, ny, nz;
};

AssimpMesh::AssimpMesh() {
}

AssimpMesh::AssimpMesh(std::string sFilename) {
	this->load(sFilename);
}

void AssimpMesh::Clear()
{
	if (am_VAO != 0) {
		gl::DeleteVertexArrays(1, &am_VAO);
		am_VAO = 0;
	}
	m_NumBones = 0;
}

bool AssimpMesh::load(std::string sFile) {
	// Release the previously loaded mesh (if it exists)
	Clear();

	scene = import.ReadFile(sFile, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs |
		aiProcess_LimitBoneWeights);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return false;
	}

	m_GlobalInverseTransform = scene->mRootNode->mTransformation;
	m_GlobalInverseTransform.Inverse();

	this->directory = sFile.substr(0, sFile.find_last_of('/'));
	this->processNode(scene->mRootNode, scene);

	return true;
}

void AssimpMesh::processNode(aiNode* node, const aiScene* scene) {

	m_Entries.resize(scene->mNumMeshes);

	vector<aVertex> vertices;
	vector<GLuint> indices;
	vector<VertexBoneData> bones;

	unsigned int NumVertices = 0;
	unsigned int NumIndices = 0;

	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		m_Entries[i].MaterialIndex = scene->mMeshes[i]->mMaterialIndex;

		// Total mesh indices. 
		m_Entries[i].NumIndices = scene->mMeshes[i]->mNumFaces * 3;

		// Set the base vertex of this mesh (initial vertex for this mesh within the vertices array) to the current total vertices. 
		m_Entries[i].BaseVertex = NumVertices;

		// Set the base index of this mesh (initial index for this mesh within the indices array) to the current total indices. 
		m_Entries[i].BaseIndex = NumIndices;

		// Increment total vertices and indices. 
		NumVertices += scene->mMeshes[i]->mNumVertices;
		NumIndices += m_Entries[i].NumIndices;
	}

	// Reserve space in the vectors for the vertex attributes and indices
	vertices.reserve(NumVertices);
	bones.resize(NumVertices);
	indices.reserve(NumIndices);


	/*
	//
	//Vertices are not getting added in processMesh. Al pasar por referencia deber'ian a;adirse y no pasa
	//
	//
	*/



	// Process all the node's meshes
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(i, mesh, scene, vertices, indices, bones));
	}

	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}

	//gl::GenVertexArrays(1, &am_VAO);
	//gl::GenBuffers(3, am_handle);
	//gl::GenBuffers(1, &vbo);
	//gl::GenBuffers(1, &ebo);
	//gl::GenBuffers(1, &boneBo);

	//gl::BindVertexArray(am_VAO);

	////Vertices
	//gl::BindBuffer(gl::ARRAY_BUFFER, am_handle[0]);
	//gl::BufferData(gl::ARRAY_BUFFER, (vertices.size()) * sizeof(aVertex), &vertices[0], gl::STATIC_DRAW);

	//gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, gl::FALSE_, sizeof(aVertex), (GLvoid*)0);
	//gl::EnableVertexAttribArray(0);

	////Normals
	//gl::BindBuffer(gl::ARRAY_BUFFER, am_handle[1]);
	//gl::BufferData(gl::ARRAY_BUFFER, (vertices.size()) * sizeof(aVertex), &vertices[0], gl::STATIC_DRAW);

	//gl::VertexAttribPointer((GLuint)1, 3, gl::FLOAT, gl::FALSE_, sizeof(aVertex), (GLvoid*)(3 * sizeof(GLfloat)));
	//gl::EnableVertexAttribArray(1);
	////gl::VertexAttribPointer((GLuint)1, 3, gl::FLOAT, gl::FALSE_, sizeof(aVertex), (GLvoid*)offsetof(aVertex, Normal));

	////Texture Coordinates
	//gl::BindBuffer(gl::ARRAY_BUFFER, am_handle[2]);
	//gl::BufferData(gl::ARRAY_BUFFER, (vertices.size()) * sizeof(aVertex), &vertices[0], gl::STATIC_DRAW);

	//gl::VertexAttribPointer((GLuint)2, 2, gl::FLOAT, FALSE, sizeof(aVertex), (GLvoid*)(6 * sizeof(GLfloat)));
	//gl::EnableVertexAttribArray(2);

	//// Bind the bone data buffer object
	//gl::BindBuffer(gl::ARRAY_BUFFER, boneBo);
	//gl::BufferData(gl::ARRAY_BUFFER, sizeof(bones[0]) * bones.size(), &bones[0], gl::STATIC_DRAW);

	//gl::VertexAttribIPointer(3, 4, gl::INT, sizeof(VertexBoneData), (const GLvoid*)0);
	//gl::EnableVertexAttribArray(3);

	//gl::VertexAttribPointer(4, 4, gl::FLOAT, FALSE, sizeof(VertexBoneData), (const GLvoid*)16);
	//gl::EnableVertexAttribArray(4);

	//gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ebo);
	//gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0],
	//	gl::STATIC_DRAW);

	//vertices.clear();
	//indices.clear();
	//bones.clear();
}

aModel AssimpMesh::processMesh(GLuint ind, aiMesh* mesh, const aiScene* scene, vector<aVertex> vertices, vector<GLuint> indices, vector<VertexBoneData> bones) {
	vector<aTexture> textures;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		aVertex vertex;
		glm::vec3 vector;

		// Positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// Normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		// Texture Coordinates
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	// Load the mesh's bones. 
	if (mesh->HasBones()) {
		LoadBones(ind, mesh, bones);

	}


	// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);

	}

	// Process materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// 1. Diffuse maps
		vector<aTexture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		vector<aTexture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	}

	gl::GenVertexArrays(1, &am_VAO);
	gl::GenBuffers(3, am_handle);
	gl::GenBuffers(1, &vbo);
	gl::GenBuffers(1, &ebo);
	gl::GenBuffers(1, &boneBo);

	gl::BindVertexArray(am_VAO);

	//Vertices
	gl::BindBuffer(gl::ARRAY_BUFFER, am_handle[0]);
	gl::BufferData(gl::ARRAY_BUFFER, (vertices.size()) * sizeof(aVertex), &vertices[0], gl::STATIC_DRAW);
	
	gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, gl::FALSE_, sizeof(aVertex), (GLvoid*)0);
	gl::EnableVertexAttribArray(0);	

	//Normals
	gl::BindBuffer(gl::ARRAY_BUFFER, am_handle[1]);
	gl::BufferData(gl::ARRAY_BUFFER, (vertices.size()) * sizeof(aVertex), &vertices[0], gl::STATIC_DRAW);
	
	gl::VertexAttribPointer((GLuint)1, 3, gl::FLOAT, gl::FALSE_, sizeof(aVertex), (GLvoid*)(3 * sizeof(GLfloat)));
	gl::EnableVertexAttribArray(1);
	//gl::VertexAttribPointer((GLuint)1, 3, gl::FLOAT, gl::FALSE_, sizeof(aVertex), (GLvoid*)offsetof(aVertex, Normal));

	//Texture Coordinates
	gl::BindBuffer(gl::ARRAY_BUFFER, am_handle[2]);
	gl::BufferData(gl::ARRAY_BUFFER, (vertices.size()) * sizeof(aVertex), &vertices[0], gl::STATIC_DRAW);
	
	gl::VertexAttribPointer((GLuint)2, 2, gl::FLOAT, FALSE, sizeof(aVertex), (GLvoid*)(6 * sizeof(GLfloat)));
	gl::EnableVertexAttribArray(2);

	// Bind the bone data buffer object
	gl::BindBuffer(gl::ARRAY_BUFFER, boneBo);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(bones[0]) * bones.size(), &bones[0], gl::STATIC_DRAW);
	
	gl::VertexAttribIPointer(3, 4, gl::INT, sizeof(VertexBoneData), (const GLvoid*)0);
	gl::EnableVertexAttribArray(3);

	gl::VertexAttribPointer(4, 4, gl::FLOAT, FALSE, sizeof(VertexBoneData), (const GLvoid*)16);
	gl::EnableVertexAttribArray(4);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ebo);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0],
		gl::STATIC_DRAW);

	// Return a mesh object created from the extracted mesh data
	return aModel(vertices, indices, textures);

}


void AssimpMesh::LoadBones(unsigned int MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones)
{

	// Loop through all bones in the Assimp mesh.
	for (unsigned int i = 0; i < pMesh->mNumBones; i++) {

		unsigned int BoneIndex = 0;

		// Obtain the bone name.
		std::string BoneName(pMesh->mBones[i]->mName.data);

		// If bone isn't already in the map. 
		if (m_BoneMapping.find(BoneName) == m_BoneMapping.end()) {

			// Set the bone ID to be the current total number of bones. 
			BoneIndex = m_NumBones;

			// Increment total bones. 
			m_NumBones++;

			// Push new bone info into bones vector. 
			BoneInfo bi;
			m_BoneInfo.push_back(bi);
		}
		else {
			// Bone ID is already in map. 
			BoneIndex = m_BoneMapping[BoneName];
		}

		m_BoneMapping[BoneName] = BoneIndex;

		// Obtains the offset matrix which transforms the bone from mesh space into bone space. 
		m_BoneInfo[BoneIndex].BoneOffset = pMesh->mBones[i]->mOffsetMatrix;


		// Iterate over all the affected vertices by this bone i.e weights. 
		for (unsigned int j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {

			// Obtain an index to the affected vertex within the array of vertices.
			unsigned int VertexID = (int)m_Entries[MeshIndex].BaseVertex + (int)pMesh->mBones[i]->mWeights[j].mVertexId;
			// The value of how much this bone influences the vertex. 
			float Weight = pMesh->mBones[i]->mWeights[j].mWeight;

			// Insert bone data for particular vertex ID. A maximum of 4 bones can influence the same vertex. 
			Bones[VertexID].AddBoneData(BoneIndex, Weight);
		}
	}
}

void AssimpMesh::BoneTransform(float TimeInSeconds, std::vector<Matrix4f>& Transforms)
{
	Matrix4f Identity;
	Identity.InitIdentity();

	float TicksPerSecond = scene->mAnimations[0]->mTicksPerSecond;
	float TimeInTicks = TimeInSeconds * TicksPerSecond;
	float AnimationTime = fmod(TimeInTicks, scene->mAnimations[0]->mDuration);

	ReadNodeHierarchy(AnimationTime, scene->mRootNode, Identity);

	Transforms.resize(m_NumBones);

	// Populates transforms vector with new bone transformation matrices. 
	for (unsigned int i = 0; i < m_NumBones; i++) {
		Transforms[i] = m_BoneInfo[i].FinalTransformation;
	}

}

unsigned int AssimpMesh::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	// Check if there are rotation keyframes. 
	assert(pNodeAnim->mNumRotationKeys > 0);

	// Find the rotation key just before the current animation time and return the index. 
	for (unsigned int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
			return i;
		}
	}
	assert(0);

	return 0;
}

unsigned int AssimpMesh::FindScale(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumScalingKeys > 0);

	// Find the scaling key just before the current animation time and return the index. 
	for (unsigned int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
			return i;
		}
	}
	assert(0);

	return 0;
}

unsigned int AssimpMesh::FindTranslation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumPositionKeys > 0);

	// Find the translation key just before the current animation time and return the index. 
	for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
			return i;
		}
	}
	assert(0);

	return 0;
}


void AssimpMesh::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	// we need at least two values to interpolate...
	if (pNodeAnim->mNumRotationKeys == 1) {
		Out = pNodeAnim->mRotationKeys[0].mValue;
		return;
	}
	// Obtain the current rotation keyframe. 
	unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);

	// Calculate the next rotation keyframe and check bounds. 
	unsigned int NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);

	// Calculate delta time, i.e time between the two keyframes.
	float DeltaTime = pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime;

	// Calculate the elapsed time within the delta time.  
	float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
	//assert(Factor >= 0.0f && Factor <= 1.0f);

	// Obtain the quaternions values for the current and next keyframe. 
	const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
	const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;

	// Interpolate between them using the Factor. 
	aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);

	// Normalise and set the reference. 
	Out = Out.Normalize();
}

void AssimpMesh::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	// we need at least two values to interpolate...
	if (pNodeAnim->mNumScalingKeys == 1) {
		Out = pNodeAnim->mScalingKeys[0].mValue;
		return;
	}

	unsigned int ScalingIndex = FindScale(AnimationTime, pNodeAnim);
	unsigned int NextScalingIndex = (ScalingIndex + 1);
	assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
	float DeltaTime = pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime;
	float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
	//assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
	const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;

	aiVector3D Delta = End - Start;
	Out = Start + Factor * Delta;
}

void AssimpMesh::CalcInterpolatedTranslation(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	// we need at least two values to interpolate...
	if (pNodeAnim->mNumPositionKeys == 1) {
		Out = pNodeAnim->mPositionKeys[0].mValue;
		return;
	}


	unsigned int PositionIndex = FindTranslation(AnimationTime, pNodeAnim);
	unsigned int NextPositionIndex = (PositionIndex + 1);
	assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
	float DeltaTime = pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime;
	float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
	//assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
	const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;

	aiVector3D Delta = End - Start;
	Out = Start + Factor * Delta;
}

void AssimpMesh::ReadNodeHierarchy(float AnimationTime, const aiNode* pNode, const Matrix4f& ParentTransform)
{
	Matrix4f IdentityTest;
	IdentityTest.InitIdentity();

	// Obtain the name of the current node 
	std::string NodeName(pNode->mName.data);

	// Use the first animation 
	const aiAnimation* pAnimation = scene->mAnimations[0];

	// Obtain transformation relative to node's parent. 
	Matrix4f NodeTransformation(pNode->mTransformation);

	const aiNodeAnim* pNodeAnim = NULL;

	// Find the animation channel of the current node. 
	for (unsigned i = 0; i < pAnimation->mNumChannels; i++) {
		const aiNodeAnim* pNodeAnimIndex = pAnimation->mChannels[i];

		// If there is a match for a channel with the current node's name, then we've found the animation channel. 
		if (std::string(pNodeAnimIndex->mNodeName.data) == NodeName) {
			pNodeAnim = pNodeAnimIndex;
		}
	}

	if (pNodeAnim) {

		//// Interpolate scaling and generate scaling transformation matrix
		//aiVector3D Scaling;
		//CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
		//Matrix4f ScalingM;
		//ScalingM.InitScaleTransform(Scaling.x, Scaling.y, Scaling.z);

		// Interpolate rotation and generate rotation transformation matrix
		aiQuaternion RotationQ;
		CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
		Matrix4f RotationM = Matrix4f(RotationQ.GetMatrix());

		// Interpolate translation and generate translation transformation matrix
		aiVector3D Translation;
		CalcInterpolatedTranslation(Translation, AnimationTime, pNodeAnim);
		Matrix4f TranslationM;
		TranslationM.InitTranslationTransform(Translation.x, Translation.y, Translation.z);

		// Combine the above transformations
		NodeTransformation = TranslationM * RotationM;/* *ScalingM;*/
	}

	Matrix4f GlobalTransformation = ParentTransform * NodeTransformation;

	// Apply the final transformation to the indexed bone in the array. 
	if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
		unsigned int BoneIndex = m_BoneMapping[NodeName];
		m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform  * GlobalTransformation *
			m_BoneInfo[BoneIndex].BoneOffset;
	}

	// Do the same for all the node's children. 
	for (unsigned i = 0; i < pNode->mNumChildren; i++) {
		ReadNodeHierarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
	}
}

void AssimpMesh::SetBoneTransform(unsigned int Index, const Matrix4f& Transform)
{
	assert(Index < 100);

	m_pShaderProg->setUniformIndex(Index, Transform);
}

bool AssimpMesh::getHasBones()
{
	if (m_NumBones > 0)
		return true;
	else
		return false;
}

vector<aTexture> AssimpMesh::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
	vector<aTexture> textures;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		GLboolean skip = false;

		for (GLuint j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].myPath.C_Str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // If texture hasn't been loaded already, load it
			aTexture texture;
			texture.myId = TextureFromFile(str.C_Str(), this->directory);
			texture.myType = typeName;
			texture.myPath = str;
			textures.push_back(texture);
			this->textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.

		}
	}
	return textures;
}


GLint AssimpMesh::TextureFromFile(const char* path, string directory)
{
	//Generate texture ID and load texture data 
	string filename = string(path);
	filename = directory + '/' + filename;
	GLuint textureID;
	gl::GenTextures(1, &textureID);
	int width, height;

	Texture* texture = NULL;
	//Load image
	Bitmap bmp = Bitmap::bitmapFromFile(filename.c_str());
	bmp.flipVertically();
	//Create texture
	texture = new Texture(bmp);

	textureID = texture->object();
	return textureID;
}

void AssimpMesh::setVAO(GLuint vao)
{
	am_VAO = vao;
}

GLuint AssimpMesh::getVAO()
{
	return am_VAO;
}