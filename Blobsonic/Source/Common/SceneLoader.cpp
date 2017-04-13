#include <stdafx.h>
#include "SceneLoader.h"
#include <cstdlib>
#include "SplashScene.h"

//Components
#include "Model.h"
#include "Camera.h"
#include "AABB.h"

void SceneLoader::loadMesh(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	std::shared_ptr<AssimpMesh> aMesh = std::make_shared<AssimpMesh>();
	char* c = "";
	std::string s;
	for (XMLElement* Child = e->FirstChildElement(); Child != NULL; Child = Child->NextSiblingElement()) {
		const char* childValue = Child->Value();
		if (strcmp(childValue, "ID") == 0) {
			//Set mesh ID
			if (readElementText(Child, c)) {
				s = std::string(c, strlen(c));		//Mesh ID
			}
		}
		else if (strcmp(childValue, "File") == 0) {
			//Load mesh
			if (readElementText(Child, c)) {
				std::string sFile(c, strlen(c));
				mesh->load(sFile);
				aMesh->load(sFile);
			};
		}
		else if (strcmp(childValue, "Texture") == 0) {

		}
	}
	m_res->addAssimpMesh(s, aMesh);	//Add mesh to resource manager;
	m_res->addMesh(s, mesh);	//Add mesh to resource manager;
	m_res->addMesh(s,mesh);	//Add mesh to resource manager;
	if (m_bDebug) std::cout << " Mesh Loaded: " << s << "\n";
}

void SceneLoader::loadTexture(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* c = "";
	std::string s;
	std::shared_ptr<Texture> texture = NULL;
	for (XMLElement* Child = e->FirstChildElement(); Child != NULL; Child = Child->NextSiblingElement()) {
		const char* childValue = Child->Value();
		if (strcmp(childValue, "ID") == 0) {
			//Set texture ID
			if (readElementText(Child, c)) {
				s = std::string(c, strlen(c));
			}
		}
		else if (strcmp(childValue, "File") == 0) {
			
			if (readElementText(Child, c)) {
				std::string sFile(c, strlen(c));
				//Load image
				Bitmap bmp = Bitmap::bitmapFromFile(sFile);
				bmp.flipVertically();
				//Create texture
				texture = std::make_shared<Texture>(bmp);
			};
		}
	}
	m_res->addTexture(s,texture);
	if (m_bDebug) std::cout << " Texture Loaded: " << s << "\n";
}

void SceneLoader::loadMaterial(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* c = "";
	std::string s;
	std::shared_ptr<Material> material = std::make_shared<Material>();
	glm::vec3 v;
	for (XMLElement* Child = e->FirstChildElement(); Child != NULL; Child = Child->NextSiblingElement()) {
		const char* childValue = Child->Value();
		if (strcmp(childValue, "ID") == 0) {
			//Set texture ID
			if (readElementText(Child, c)) {
				s = std::string(c, strlen(c));
			}
		}
		else if (strcmp(childValue, "AmbientReflect") == 0) {
			v = parseVec3(Child);
			material->setAmbient(v);
		}
		else if (strcmp(childValue, "DiffuseReflect") == 0) {
			v = parseVec3(Child);
			material->setDiffuse(v);
		}
		else if (strcmp(childValue, "SpecularReflect") == 0) {
			v = parseVec3(Child);
			material->setSpecular(v);
		}
		else if (strcmp(childValue, "Shininess") == 0) {
			if (readElementText(Child, c)) {
				material->setShininess(atof(c));
			}
		}
	}
	m_res->addMaterial(s, material);
	if (m_bDebug) std::cout << " Material Loaded: " << s << "\n";
}

void SceneLoader::loadShader(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* c = "";
	std::string s;

	std::shared_ptr<GLSLProgram> shader = std::make_shared<GLSLProgram>();
	try {
		
		for (XMLElement* Child = e->FirstChildElement(); Child != NULL; Child = Child->NextSiblingElement()) {
			const char* childValue = Child->Value();
			if (strcmp(childValue, "ID") == 0) {
				//Set ID
				if (readElementText(Child, c)) {
					s = std::string(c, strlen(c));
				}
			}
			else if (strcmp(childValue, "Vertex") == 0) {
				if (readElementText(Child, c)) {				//Read file location
					shader->compileShader(c);					//Compile vertex shader
				}
			}
			else if (strcmp(childValue, "Fragment") == 0) {
				if (readElementText(Child, c)) {				//Read file location
					shader->compileShader(c);					//Compile fragment shader
				}
			}
		}
		shader->link();
		shader->validate();
		shader->use();
	}
	catch (GLSLProgramException & e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	m_res->addShader(s, shader);
	if (m_bDebug) std::cout << " Shader Loaded: " << s << "\n";
}

std::shared_ptr<Entity> SceneLoader::loadModel(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;

	char* cData = "";			//Temporary storage for element data

	if (m_bDebug) std::cout << "\nLoading Model \n  ";

	std::shared_ptr<Entity> entity = m_factory.createActor();
	//entity->attach<AABB>();
	

	auto model = entity->get<Component::Model>();
	auto transform = entity->get<Component::Transformable>();
	//auto aabb = entity->get<AABB>();

	std::string sID;
	//Look at Model Element
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()) {
		const char* childValue = modelChild->Value();
		if (strcmp(childValue, "ID") == 0) {
			if (readElementText(modelChild, cData)) {
				sID = std::string(cData, strlen(cData));
			}
		}
		else if (strcmp(childValue, "Mesh") == 0) {
			if (readElementText(modelChild, cData)) {
				model->m_meshes.push_back(m_res->getMesh(std::string(cData, strlen(cData))));
				model->m_aMeshes.push_back(m_res->getAssimpMesh(std::string(cData, strlen(cData))));

			}
		}
		else if (strcmp(childValue, "Shader") == 0) {
			if (readElementText(modelChild, cData)) {
				model->m_shader = (m_res->getShader(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Texture") == 0) {
			if (readElementText(modelChild, cData)) {
				model->m_textures.push_back(m_res->getTexture(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			transform->setPosition(v);
			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Scale") == 0) {
			//Set model scale
			glm::vec3 v = parseVec3(modelChild);
			transform->m_transform = glm::scale(transform->m_transform, v);
			transform->m_vScale = v;
			if (m_bDebug) std::cout << "Scale Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Dimensions") == 0) {
			//Set model scale
			glm::vec3 v = parseVec3(modelChild);
			transform->m_transform = glm::scale(transform->m_transform, v);
			transform->m_vDimensions = v;
			if (m_bDebug) std::cout << "Dimension Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		//else if (strcmp(childValue, "Origin") == 0) {
		//	//Set model origin
		//	glm::vec3 v = parseVec3(modelChild);
		//	transform->setOrigin(v);
		//	if (m_bDebug) std::cout << "Origin Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		//}
		else if (strcmp(childValue, "Material") == 0) {
			if (readElementText(modelChild, cData)) {
				model->m_materials.push_back((m_res->getMaterial(std::string(cData, strlen(cData)))));
			}
		}
	}

	m_factory.attachAABB(entity, transform->getPosition(),transform->m_vDimensions, transform->m_vScale);
	return entity;
}

/*
std::shared_ptr<Entity> SceneLoader::loadLight(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;

	char* cData = "";			//Temporary storage for element data

	if (m_bDebug) std::cout << "\nLoading Light \n  ";

	Light light;
	std::string sID;
	//Look at Model Element
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()) {
		const char* childValue = modelChild->Value();
		if (strcmp(childValue, "ID") == 0) {
			if (readElementText(modelChild, cData)) {
				sID = std::string(cData, strlen(cData));
			}
		}
		else if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			light.setPosition(v);

			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Ambient") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			light.setAmbient(v);
			if (m_bDebug) std::cout << "Ambient intensity: " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Diffuse") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			light.setDiffuse(v);
			if (m_bDebug) std::cout << "Diffuse intensity: " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Specular") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			light.setSpecular(v);
			if (m_bDebug) std::cout << "Specular intensity: " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Radius") == 0) {
			if (readElementText(modelChild, cData)) {
				light.setRadius(atof(cData));
			}
		}
	}

	return std::pair<std::string, Light>(sID, light);
}
*/

std::shared_ptr<Entity> SceneLoader::loadCamera(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;

	char* cData = "";			//Temporary storage for element data

	if (m_bDebug) std::cout << "\nLoading Camera \n  ";

	std::shared_ptr<Entity> entity = m_factory.createCamera(glm::vec3(0.0f));

	auto camera = entity->get<Component::Camera>();

	std::string s;
	char * c;
	std::string sID;
	float fNear = 0.1f;
	float fFar = 100.0f;
	//Look at Model Element
	for (XMLElement* child = e->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
		const char* childValue = child->Value();
		if (strcmp(childValue, "ID") == 0) {
			if (readElementText(child, cData)) {
				sID = std::string(cData, strlen(cData));
			}
		}
		else if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(child);
			camera->m_vPosition = v;
			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		/*	else if (strcmp(childValue, "Orientation") == 0) {
			glm::vec3 v = parseVec3(child);
			camera.rotate(v.x,v.y);
			camera.roll(v.z);
			if (m_bDebug) std::cout << "Orientation Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}*/
		else if (strcmp(childValue, "FOV") == 0) {
			if (readElementText(child, c)) {
				camera->m_fFarPlane = (atof(c));
			}
			if (m_bDebug) std::cout << "Field of View: " << c << "\n  ";
		}
		else if (strcmp(childValue, "AspectRatio") == 0) {
			if (readElementText(child, c)) {
				camera->m_fAspectRatio = (atof(c));
			}
			if (m_bDebug) std::cout << "Aspect Ratio: " << c << "\n  ";
		}
		else if (strcmp(childValue, "FarPlane") == 0) {
			if (readElementText(child, c)) {
				camera->m_fFarPlane = atof(c);
			}
			if (m_bDebug) std::cout << "Far plane: " << c << "\n  ";
		}
		else if (strcmp(childValue, "NearPlane") == 0) {
			if (readElementText(child, c)) {
				camera->m_fNearPlane = atof(c);
			}
			if (m_bDebug) std::cout << "NearPlane: " << c << "\n  ";
		}
		//else if (strcmp(childValue, "RotSpeed") == 0) {
		//	if (readElementText(child, c)) {
		//		camera->m_fMoveSpeed(atof(c));
		//	}
		//	if (m_bDebug) std::cout << "Rotation Speed: " << c << "\n  ";
		//}
		else if (strcmp(childValue, "MoveSpeed") == 0) {
			if (readElementText(child, c)) {
				camera->m_fMoveSpeed = (atof(c));
			}
			if (m_bDebug) std::cout << "MoveSpeed Speed: " << c << "\n  ";
		}
	}
	return entity;
}

void SceneLoader::readScene(tinyxml2::XMLNode * node)
{
	bool bTypeFound = false;

	char* c = "";
	std::string str;
	if (readElementText(node->FirstChildElement("Type"), c)) {
		str = std::string(c, strlen(c));
	}
	using namespace tinyxml2;
	std::string sID;

	//-- Add entities into the scene --//
	if (str == "Game") {
		std::shared_ptr<GameScene> scene = std::make_shared<GameScene>(m_res);				//Create scene
		EntityManager* entities = scene->getEntityManager();	//Get scene entity manager used to add entities in to the scene

		//Add Scene Entities
		if (m_bDebug) std::cout << "\nLoading Scene elements\n ";
		for (XMLElement* element = node->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
		{
			if (strcmp(element->Value(), "ID") == 0) {
				if (readElementText(element, c)) {
					sID = std::string(c, strlen(c));		//ID
				}
			}
			else if (strcmp(element->Value(), "Model") == 0) {
				entities->addEntity(loadModel(element));
			}
			else if (strcmp(element->Value(), "Light") == 0) {
				//entities->addEntity(loadLight(element));
			}
			else if (strcmp(element->Value(), "Camera") == 0) {
				entities->addEntity(loadCamera(element));
			}
			else if (strcmp(element->Value(), "Physics") == 0) {
				entities->addEntity(loadModel(element));
			}
		}
		//Attach Scene to engine
		m_scenes->emplace(sID, scene);
	}
}

void SceneLoader::readResources(tinyxml2::XMLNode* node)
{
	using namespace tinyxml2;
	std::cout << "\nReading Resources\n";
	for (XMLElement* element = node->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		const char* c = element->Value();
		if (strcmp(c, "Mesh") == 0) {
			loadMesh(element);
		}
		else if (strcmp(c, "Texture") == 0) {
			loadTexture(element);
		}
		else if (strcmp(c, "Material") == 0) {
			loadMaterial(element);
		}
		else if (strcmp(c, "Shader") == 0) {
			loadShader(element);
		}
	}
}

bool SceneLoader::readElementText(tinyxml2::XMLElement* e,char*& data)
{
	data = (char*)e->GetText();
	if (data != nullptr) {
		//Text exists
		return true;
	}
	//Text does not exist
	data = nullptr;
	return false;
}

glm::vec3 SceneLoader::parseVec3(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* cData = "";		//Temp data storage

	glm::vec3 v(0.0f,0.0f,0.0f);

	for (XMLElement* childElement = e->FirstChildElement(); childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		const char* c = childElement->Value();
		if ((strcmp(c, "X")) == 0) {
			if (readElementText(childElement, cData)) {	//Check if text exists
				v.x = atof(cData);	//Convert to float and place into float array
			}
		}
		else if ((strcmp(c, "Y")) == 0) {
			if (readElementText(childElement, cData)) {	//Check if text exists
				v.y = atof(cData);	//Convert to float and place into float array
			}
		}
		else if ((strcmp(c, "Z")) == 0) {
			if (readElementText(childElement, cData)) {	//Check if text exists
				v.z = atof(cData);	//Convert to float and place into float array
			}
		}
	}

	return v;		//Return vector
}

SceneLoader::SceneLoader(ResourceManager * res, std::map<std::string, std::shared_ptr<Scene>>* scenes)
	:m_factory(res)
{
	m_res = res;		//Pointer to Resource manager
	m_scenes = scenes;	//Pointer to vector of scenes
}

SceneLoader::~SceneLoader()
{

}

int SceneLoader::load(std::string sFilename)
{
	using namespace tinyxml2;
	//Load xml scene file
	XMLDocument doc;
	if (doc.LoadFile(sFilename.c_str()) != XML_SUCCESS) {
		//Failed to load
		std::cout << "Could not load file: " << sFilename << "\n";
		return false;
	}

	if (m_bDebug) std::cout << "Reading scene file: " << sFilename << "\n";

	XMLNode *ptrRoot = doc.FirstChild();
	if (ptrRoot == nullptr) {
		std::cout << "No root: " << sFilename << "\n";
		return false;
	}

	for (XMLNode* node = ptrRoot; node != NULL; node = node->NextSiblingElement()) {
		const char* value = node->Value();

		if (strcmp(node->Value(), "Resources") == 0) {
			readResources(node);
		}
		else if (strcmp(node->Value(), "Scene") == 0) {
			readScene(node);
		}
	}
	return XML_SUCCESS;
}