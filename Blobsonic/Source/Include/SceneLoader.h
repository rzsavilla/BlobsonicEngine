/**
* @class	SceneLoader
* @brief	Loads XML scene file
* @author Rozen Savilla
* Parses XML scene file using tinyxml2, creating and storing objects into a scene class.
* Also loads and stores resouces such as textures and meshes.
* XML Parser :(tinyxml2)http://www.grinninglizard.com/tinyxml2/
*/

#pragma once

/** Factory pattern
	https://sourcemaking.com/design_patterns/factory_method
*/

#include "tinyxml2.h"

#include "ResourceManager.h"
#include "Scene.h"

//Audio engine
#include <irrKlang\irrKlang.h>

// include console I/O methods (conio.h for windows, our wrapper in linux)
#if defined(WIN32)
#include <conio.h>
#endif

class SceneLoader {
private:
	//Scene file location
	const std::string m_sSceneFiles = "Source/Resources/scenes/";		//!< Location of scene xml files

	//Resource Directories
	std::string m_sTextureDir;		//!< File location for textures
	std::string m_sMeshDir;			//!< File location for Meshes
	std::string m_sShadersDir;		//!< File location for Shaders
	std::string m_sMaterialDir;		//!< File location for materials

	std::shared_ptr<ResourceManager> m_res;		//!< Pointer to Resource manager where loaded resources will be stored
	std::shared_ptr<EntityFactory> m_factory;	//!< Create preset entities

	void loadMesh(tinyxml2::XMLElement* e);				//!< Parse file to load mesh
	//!< Parse file to load sprites
	void loadTexture(tinyxml2::XMLElement* e);			//!< Parse file to load texture
	void loadMaterial(tinyxml2::XMLElement* e);			//!< Parse file to load material
	void loadShader(tinyxml2::XMLElement* e);			//!< Parse file to load shader
	
	std::shared_ptr<Entity> loadAudio(tinyxml2::XMLElement* e); //!< Parse file to load audio
	std::shared_ptr<Entity> loadEntity(tinyxml2::XMLElement* e);	//!< Parse and create model
	std::shared_ptr<Entity> loadModel(tinyxml2::XMLElement* e);		//!< Parse and create model
 
	std::shared_ptr<Entity> createEntity(tinyxml2::XMLElement* e);	//!< Parse and create entity from xml
	void attachTransformable(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachModel(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachPhysical(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachAABB(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachSphere(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachOBB(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachCamera(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachDirLight(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachPointLight(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachSpotLight(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachSound(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachSprite(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachPlayer(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);
	void attachPickup(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e);

	std::shared_ptr<Entity> loadSprite(tinyxml2::XMLElement* e);
	std::shared_ptr<Entity> loadButton(tinyxml2::XMLElement* e);
	std::shared_ptr<Entity> loadText(tinyxml2::XMLElement* e);

	std::shared_ptr<Entity> loadLight(tinyxml2::XMLElement* e);		//!< Parse and create light
	std::shared_ptr<Entity> loadCamera(tinyxml2::XMLElement* e);		//!< Parse and create camera

	void readScene(tinyxml2::XMLNode* node);				//!< Parse a scene
	bool readResourceFile(tinyxml2::XMLNode* node,/*! Optional default is false */bool forceReloadRes = false);			//!< Open and parse seperate file containing list of resources
	void readResources(tinyxml2::XMLNode* node);			//!< Parse resources
	bool m_bDebug = true;				//!< Flag for couts
private:	//Parsing functions
	bool readElementText(tinyxml2::XMLElement* e,char*& data);	//!< Read the value of an element returns false if the element is empty
	glm::vec3 parseVec3(tinyxml2::XMLElement*e);				//!< Parse data into a vec3
private:	//Staggered Loading functions and variables
	//! Current loading state
	enum LoadingState {
		LoadScene,
		LoadResource,
		LoadResFile,
		Idle
	};

	LoadingState m_LoadingState;			//!< Current loading state
	std::shared_ptr<Scene> m_SceneLoading;	//!< Scene object where scene is being loaded into

	tinyxml2::XMLDocument m_document;	//!< Current document being loaded
	tinyxml2::XMLNode* m_rootNode;		//!< Root node
	tinyxml2::XMLNode* m_node;			//!< Current xml node
public:
	//! Default constructor
	SceneLoader();		//!< Default constructor
	~SceneLoader();		//!< Destructor

	/*!
	*	Loads the entire scene
	*/
	std::shared_ptr<Scene> fastLoadScene(std::string sFilename,bool forceLoadRes = false);

	/*!
	*	Staggered Scene Loading
	*	Staggers loading allowing for game update and render to run whilst still loading
	*	@return bool Returns true when loading is finished.
	*/
	bool loadScene(std::shared_ptr<Scene>& scene,std::string sFilename, bool forceLoadRes = false);
};