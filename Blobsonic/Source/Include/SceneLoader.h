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
	std::string m_sTextureDir;		//!< File location for textures
	std::string m_sMeshDir;			//!< File location for Meshes
	std::string m_sShadersDir;		//!< File location for Shaders
	std::string m_sMaterialDir;		//!< File location for materials

	ResourceManager* m_res;									//!< Pointer to Resource manager where loaded resources will be stored
	EntityFactory m_factory;								//!< Create preset entities

	std::map<std::string,std::shared_ptr<Scene>>* m_scenes;	//!< Pointer to vector of scenes to store all loaded scenes
	void loadMesh(tinyxml2::XMLElement* e);				//!< Parse file to load mesh
	void loadTexture(tinyxml2::XMLElement* e);			//!< Parse file to load texture
	void loadMaterial(tinyxml2::XMLElement* e);			//!< Parse file to load material
	void loadShader(tinyxml2::XMLElement* e);			//!< Parse file to load shader
	
	std::shared_ptr<Entity> loadAudio(tinyxml2::XMLElement* e); //!< Parse file to load audio
	std::shared_ptr<Entity> loadEntity(tinyxml2::XMLElement* e);			//!< Parse and create model
	std::shared_ptr<Entity> loadModel(tinyxml2::XMLElement* e);			//!< Parse and create model
	std::shared_ptr<Entity> loadLight(tinyxml2::XMLElement* e);		//!< Parse and create light
	std::shared_ptr<Entity> loadCamera(tinyxml2::XMLElement* e);		//!< Parse and create camera

	void readScene(tinyxml2::XMLNode* node);				//!< Parse a scene
	bool readResourceFile(tinyxml2::XMLNode* node,/*! Optional default is false */bool forceReloadRes = false);			//!< Open and parse seperate file containing list of resources
	void readResources(tinyxml2::XMLNode* node);			//!< Parse resources
	bool m_bDebug = true;				//!< Flag for couts

private:	//Parsing functions
	bool readElementText(tinyxml2::XMLElement* e,char*& data);	//!< Read the value of an element returns false if the element is empty
	glm::vec3 parseVec3(tinyxml2::XMLElement*e);				//!< Parse data into a vec3
public:
	//! Default constructor
	SceneLoader(ResourceManager* res, std::map<std::string, std::shared_ptr<Scene>>* scenes);							//!< Default constructor
	~SceneLoader();		//!< Destructor

	/*!
	*	Load xml scene file
	*/
	int load(std::string sFilename,/*!< Optional default is false*/bool forceLoadRes = false);
};