/**
* @class	SceneLoader
* @brief	Loads XML scene file
* @author Rozen Savilla
* Parses XML scene file using tinyxml2, creating and storing objects into a scene class.
* Also loads and stores resouces such as textures and meshes.
* XML Parser :http://www.grinninglizard.com/tinyxml2/
*/

#pragma once

/** Factory pattern
	https://sourcemaking.com/design_patterns/factory_method
*/

#include "ResourceManager.h"
#include "GLSLProgram.h"
#include "Light.h"
#include "ModelOLD.h"
#include "GameScene.h"

#include "tinyxml2.h"

class SceneLoader {
private:

	//Resource Directories
	std::string m_sTextureDir;
	std::string m_sMeshDir;
	std::string m_sShadersDir;
	std::string m_sMaterialDir;


	ResourceManager* m_res;									//!< Pointer to Resource manager where loaded resources will be stored
	std::map<std::string,std::shared_ptr<Scene>>* m_scenes;	//!< Pointer to vector of scenes to store all loaded scenes
	void loadMesh(tinyxml2::XMLElement* e);				//!< Parse file to load mesh
				//!< Parse file to load sprites
	void loadTexture(tinyxml2::XMLElement* e);			//!< Parse file to load texture
	void loadMaterial(tinyxml2::XMLElement* e);			//!< Parse file to load material
	void loadShader(tinyxml2::XMLElement* e);			//!< Parse file to load shader

	std::shared_ptr<Entity> loadModel(tinyxml2::XMLElement* e);			//!< Parse and create model
	std::shared_ptr<Entity> loadSprite(tinyxml2::XMLElement* e);
	//std::shared_ptr<Entity> loadLight(tinyxml2::XMLElement* e);		//!< Parse and create light
	std::shared_ptr<Entity> loadCamera(tinyxml2::XMLElement* e);		//!< Parse and create camera

	void readScene(tinyxml2::XMLNode* node);				//!< Parse a scene

	bool readResourceFile(tinyxml2::XMLNode* node);								//!< Open and read seperate file containing list of resources
	void readResources(tinyxml2::XMLNode* node);			//!< Parse resources

	bool m_bDebug = true;				//!< Flag for couts

	//! Checks whether element text exists
	bool readElementText(tinyxml2::XMLElement* e,char*& data);	//!< Read the value of an element returns false if the element is empty
	
	EntityFactory m_factory;									//!< Create preset entities
	
	//! Read X,Y,Z elements
	glm::vec3 parseVec3(tinyxml2::XMLElement*e);				//!< Parse data into a vec3
public:
	//! Default constructor
	SceneLoader(ResourceManager* res, std::map<std::string, std::shared_ptr<Scene>>* scenes);							//!< Default constructor
	~SceneLoader();							//!< Destructor

	//Loads scene
	//Can load resources directly to ResourceManager and 
	//load scene directly into Scene;
	int load(std::string sFilename); 
};