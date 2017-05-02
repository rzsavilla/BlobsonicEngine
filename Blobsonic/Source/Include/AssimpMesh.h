#pragma once
/*
* @class	Mesh
* @brief	Mesh loaded from obj file
* Stores objects vertices, indices, normals, texture coordinates, will also parse the obj file
*/

#pragma once

#include "stdafx.h"
#include "ID.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Math3D.h"
#include "aModel.h"

struct VertexBoneData
{
	unsigned int IDs[4]; //!< An array of 4 bone Ids that influence a single vertex.
	float Weights[4]; //!< An array of the weight influence per bone. 

	VertexBoneData()
	{
		// 0's out the arrays. 
		Reset();
	}

	void Reset()
	{
		memset(IDs, 0, 4 * sizeof(IDs[0]));
		memset(Weights, 0, 4 * sizeof(Weights[0]));
	}

	void AddBoneData(unsigned int BoneID, float Weight)
	{
		for (unsigned int i = 0; i < 4; i++) {

			// Check to see if there are any empty weight values. 
			if (Weights[i] == 0.0) {
				// Add ID of bone. 
				IDs[i] = BoneID;

				// Set the vertex weight influence for this bone ID. 
				Weights[i] = Weight;
				return;
			}

		}
		// should never get here - more bones than we have space for
		assert(0);
	}
};

// Stores bone information
struct BoneInfo
{
	Matrix4f FinalTransformation; // Final transformation to apply to vertices 
	Matrix4f BoneOffset; // Initial offset from local to bone space. 

	BoneInfo()
	{
		BoneOffset.SetZero();
		FinalTransformation.SetZero();
	}
};

// A mesh entry for each mesh read in from the Assimp scene. A model is usually consisted of a collection of these. 
#define INVALID_MATERIAL 0xFFFFFFFF
struct MeshEntry {


	unsigned int BaseVertex; //!< Total number of mesh indices. 
	unsigned int BaseIndex; //!< The base vertex of this mesh in the vertices array for the entire model.
	unsigned int NumIndices; //!< The base index of this mesh in the indices array for the entire model. 
	unsigned int MaterialIndex;

	MeshEntry()
	{

		NumIndices = 0;
		BaseVertex = 0;
		BaseIndex = 0;
		MaterialIndex = INVALID_MATERIAL;
	}

	~MeshEntry() {}
};

class AssimpMesh {
public:
	string directory;
	void processNode(aiNode* node, const aiScene* scene);
	aModel processMesh(GLuint ind, aiMesh* mesh, const aiScene* scene, vector<aVertex> vertices, vector<GLuint> indices, vector<VertexBoneData> bones);
	GLint TextureFromFile(const char* path, string directory);

	std::vector<aModel> meshes;
	vector<aTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	vector<aTexture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

public:
	AssimpMesh();	//!< Default Constructor
	AssimpMesh(std::string sFilename);	//!< Constructor set to parse obj file
	bool load(std::string sFilename);	//!< Parse obj file

	void BoneTransform(float TimeInSeconds, std::vector<Matrix4f>& Transforms); //!< Traverses the scene hierarchy and fetches the matrix transformation for each bone given the time. 
	void SetBoneTransform(unsigned int Index, const Matrix4f& Transform); //!< Inserts a bone transformation in the uniform array at the given index. 

	bool getHasBones();

	void setVAO(GLuint vao);
	GLuint getVAO();


	std::vector<MeshEntry> m_Entries; //!< Array of mesh entries 
private:
	GLuint am_VAO;
	GLuint am_handle[3];
	GLuint vbo; //!< Vertex buffer object. 
	GLuint ebo; //!< Indices buffer object. 
	GLuint boneBo; //!< Bone data buffer object. 

	const aiScene* scene; //!< The Assimp aiScene object. 
	Assimp::Importer import; //!< Assimp importer object for reading in files into the aiScene. 

	void LoadBones(unsigned int MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones);
	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim); //!< Calculates the interpolated quaternion between two keyframes. 
	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim); //!< Calculates the interpolated scaling vector between two keyframes. 
	void CalcInterpolatedTranslation(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim); //!< Calculates the interpolated translation vector between two keyframes. 

	unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim); //!< Finds a rotation key given the current animation time. 
	unsigned int FindScale(float AnimationTime, const aiNodeAnim* pNodeAnim); // Finds a scaling key given the current animation time. 
	unsigned int FindTranslation(float AnimationTime, const aiNodeAnim* pNodeAnim); // Finds a translation key given the current animation time. 

	void ReadNodeHierarchy(float AnimationTime, const aiNode* pNode, const Matrix4f& ParentTransform); //!< Recursive function that traverses the scene's node hierarchy and combines the matrix transformations. 

	std::shared_ptr<GLSLProgram> m_pShaderProg;

	void Clear();
	Matrix4f GlobalTransformation; //!< Root node transformation. 
	Matrix4f m_GlobalInverseTransform;
	unsigned int m_NumBones; //!< Total number of bones in the model. 

	std::map<std::string, unsigned int> m_BoneMapping; //!< Map of bone names to ids
	std::vector<BoneInfo> m_BoneInfo; //!< Array containing bone information such as offset matrix and final transformation. 

};
