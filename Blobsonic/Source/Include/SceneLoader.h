/**
* @class	SceneLoader
* @brief	Loads XML scene file
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

/*
class SceneLoader {
private:
	ResourceManager* m_res;											//!< Pointer to Resource manager where loaded resources will be stored
	std::vector<std::pair<std::string,std::shared_ptr<Scene>>>* m_scenes;	//!< Pointer to vector of scenes to store all loaded scenes

	void loadMesh(tinyxml2::XMLElement* e);				//!< Parse file to load mesh
	void loadTexture(tinyxml2::XMLElement* e);			//!< Parse file to load texture
	void loadMaterial(tinyxml2::XMLElement* e);			//!< Parse file to load material
	void loadShader(tinyxml2::XMLElement* e);			//!< Parse file to load shader

	std::pair<std::string, Model> loadModel(tinyxml2::XMLElement* e);			//!< Parse and create model
	std::pair<std::string, Light> loadLight(tinyxml2::XMLElement* e);			//!< Parse and create light
	std::pair<std::string, QuatCamera> loadCamera(tinyxml2::XMLElement* e);		//!< Parse and create camera
	//std::pair<std::string, MyRobot> loadRobot(tinyxml2::XMLElement* e);			//!< Parse and create robot
	std::pair<std::string, Model> SceneLoader::loadPhysicsObject(tinyxml2::XMLElement * e); //!< parse and create a phyical object

	void readScene(tinyxml2::XMLNode* node);									//!< Parse a scene
	void readResources(tinyxml2::XMLNode* node);								//!< Parse resources

	bool m_bDebug = true;				//!< Flag for couts

	//! Checks whether element text exists
	bool readElementText(tinyxml2::XMLElement* e,char*& data);	//!< Read the value of an element returns false if the element is empty
	
	//! Read X,Y,Z elements
	glm::vec3 parseVec3(tinyxml2::XMLElement*e);				//!< Parse data into a vec3
public:
	//! Default constructor
	SceneLoader(ResourceManager* res, std::vector<std::pair<std::string, std::shared_ptr<Scene>>>*);							//!< Default constructor
	~SceneLoader();							//!< Destructor

	//Loads scene
		//Can load resources directly to ResourceManager and 
		//load scene directly into Scene;
	int load(std::string sFilename); 
};
*/