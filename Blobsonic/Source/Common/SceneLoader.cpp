#include "stdafx.h"
#include "SceneLoader.h"

//Components
#include "Transformable.h"
#include "Model.h"
#include "Camera.h"
#include "AABB.h"
#include "Player.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Spotlight.h"
#include "Button.h"
#include "Physical.h"
#include "AABB.h"
#include "OBB.h"
#include "Sphere.h"
#include "Sound.h"
#include "SpriteRender.h"
#include "Pickup.h"
#include "Text.h"

#include "EntityFactory.h"

//Audio engine
#include <irrKlang\irrKlang.h>

// include console I/O methods (conio.h for windows, our wrapper in linux)
#if defined(WIN32)
#include <conio.h>
#endif

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
				//Create texture
				texture = std::make_shared<Texture>(bmp);
			};
		}
		else if (strcmp(childValue, "Instancing") == 0) {

			if (readElementText(Child, c)) {
				std::string sInstance(c, strlen(c));
				//Load image
				Bitmap bmp = Bitmap::bitmapFromFile(sInstance);
				//Create texture
				texture = std::make_shared<Texture>(bmp);
			};
		}
	}
	m_res->addTexture(s, texture);
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
				//mesh->load(sFile);
				aMesh->load(sFile);
			};
		}
		else if (strcmp(childValue, "Texture") == 0) {

		}
	}
	m_res->addAssimpMesh(s, aMesh);	//Add mesh to resource manager;
									//m_res->addMesh(s, mesh);	//Add mesh to resource manager;
									//m_res->addMesh(s,mesh);	//Add mesh to resource manager;
	if (m_bDebug) std::cout << " Mesh Loaded: " << s << "\n";
}

std::shared_ptr<Entity> SceneLoader::loadEntity(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* cData = "";			//Temporary storage for element data
	if (m_bDebug) std::cout << "\nLoading Model \n  ";
	std::shared_ptr<Entity> entity = m_factory->createActor();

	//model
	auto model = entity->get<Component::Model>();

	//transform
	auto transform = entity->get<Component::Transformable>();

	//Collildable
	glm::vec3 Dimensions;
	float radius;

	//physical
	float mass = 1;
	float restitution = 0.5;

	//components
	const char* Value;
	std::string sID;

	//Look at Model Element
	for (XMLElement* entityChild = e->FirstChildElement(); entityChild != NULL; entityChild = entityChild->NextSiblingElement())
	{

		const char* childValue = entityChild->Value();

		if (strcmp(childValue, "Component") == 0)
		{

			for (XMLElement* ComponentChild = entityChild->FirstChildElement(); ComponentChild != NULL; ComponentChild = ComponentChild->NextSiblingElement())
			{
				if (strcmp(childValue, "ID") == 0) {
					if (readElementText(ComponentChild, cData)) {
						sID = std::string(cData, strlen(cData));
						if (m_bDebug) std::cout << "ID: " << sID << "\n";
						if (sID == "AABB")
						{
							//read the AABB info
							if (strcmp(childValue, "Position") == 0) 
							{
								glm::vec3 v = parseVec3(ComponentChild);
								transform->setPosition(v);
								if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
							}
							else if (strcmp(childValue, "Scale") == 0) 
							{
								//Set model scale
								glm::vec3 v = parseVec3(ComponentChild);
								transform->setScale(v);
								if (m_bDebug) std::cout << "Scale Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
							}
							else if (strcmp(childValue, "Dimensions") == 0) 
							{
								//Set model scale
								glm::vec3 v = parseVec3(ComponentChild);
								Dimensions = v;
								if (m_bDebug) std::cout << "Dimensions Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
							}

							m_factory->attachAABB(entity, transform->m_vPosition, Dimensions, transform->m_vScale);
						}
						if (sID == "Sphere")
						{

						}
						if (sID == "OBB")
						{

						}
						if (sID == "Capsule")
						{

						}
						if (sID == "Physical")
						{

						}

					}
				}
			}
			

		}
		else if (strcmp(childValue, "Model") == 0)
		{
			for (XMLElement* modelChild = entityChild->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement())
			{
				if (strcmp(childValue, "Mesh") == 0)
				{
					if (readElementText(modelChild, cData)) {
						//model->m_meshes.push_back(m_res->getMesh(std::string(cData, strlen(cData))));
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
			}
		}
	}
	return entity;
}

std::shared_ptr<Entity> SceneLoader::loadSprite(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* cData = "";			//Temporary storage for element data
	if (m_bDebug) std::cout << "\nLoading Sprite \n  ";
	std::shared_ptr<Entity> entity = m_factory->createSprite();
	auto sprite = entity->get<Component::SpriteRenderer>();
	auto transform = entity->get<Component::Transformable>();

	std::string sID;
	//Look at Model Element
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()) {
		const char* childValue = modelChild->Value();
		if (strcmp(childValue, "ID") == 0) {
			if (readElementText(modelChild, cData)) {
				sID = std::string(cData, strlen(cData));
				if (m_bDebug) std::cout << "ID: " << sID << "\n";
			}
		}
		else if (strcmp(childValue, "Shader") == 0) {
			if (readElementText(modelChild, cData)) {
				sprite->setShader((m_res->getShader(std::string(cData, strlen(cData)))));
			}
		}

		else if (strcmp(childValue, "Texture") == 0) {
			if (readElementText(modelChild, cData)) {
				sprite->setTexture(m_res->getTexture(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			transform->setPosition(v);
			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Rotation") == 0) {
			//Set model rotation
			glm::vec3 v = parseVec3(modelChild);
			transform->setRotation(v);
			if (m_bDebug) std::cout << "Rotation Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Scale") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			transform->setScale(v);
			if (m_bDebug) std::cout << "Scale Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Colour") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			sprite->setColor(v);
			if (m_bDebug) std::cout << "Colour Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "ID") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			sprite->setID(v);
			if (m_bDebug) std::cout << "ID : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
	}
	return entity;
}

std::shared_ptr<Entity> SceneLoader::loadButton(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* cData = "";			//Temporary storage for element data
	if (m_bDebug) std::cout << "\nLoading Button \n  ";
	std::shared_ptr<Entity> entity = m_factory->createSprite();
	entity->attach<Component::Button>();
	//entity->attach<Component::Text>();
	auto sprite = entity->get<Component::SpriteRenderer>();
	auto transform = entity->get<Component::Transformable>();
	auto button = entity->get<Component::Button>();
	//auto Text = entity->get<Component::Text>();

	std::string sID;
	//Look at Model Element
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()) {
		const char* childValue = modelChild->Value();
		if (strcmp(childValue, "ID") == 0) {
			if (readElementText(modelChild, cData)) {
				sID = std::string(cData, strlen(cData));
				if (m_bDebug) std::cout << "ID: " << sID << "\n";
			}
		}
		else if (strcmp(childValue, "Shader") == 0) {
			if (readElementText(modelChild, cData)) {
				sprite->setShader(m_res->getShader(std::string(cData, strlen(cData))));
			}
		}

		else if (strcmp(childValue, "Texture") == 0) {
			if (readElementText(modelChild, cData)) {
				sprite->setTexture(m_res->getTexture(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			transform->setPosition(v);
			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Rotation") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			transform->setRotation(v);
			if (m_bDebug) std::cout << "Rotation Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Scale") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			transform->setScale(v);
			if (m_bDebug) std::cout << "Scale Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Colour") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			sprite->setColor(v);
			if (m_bDebug) std::cout << "Colour Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "sID") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			button->setButtonID(v.x);
			if (m_bDebug) std::cout << "ID : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
	}
	return entity;
}

std::shared_ptr<Entity> SceneLoader::loadText(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* cData = "";			//Temporary storage for element data
	if (m_bDebug) std::cout << "\nLoading Text \n  ";
	std::shared_ptr<Entity> entity = m_factory->createText();
	entity->attach<Component::Text>();
	auto text = entity->get<Component::Text>();
	auto transform = entity->get<Component::Transformable>();
	//auto button = entity->get<Component::Button>();
	//auto Text = entity->get<Component::Text>();

	std::string sID;
	//Look at Model Element
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()) {
		const char* childValue = modelChild->Value();
		if (strcmp(childValue, "ID") == 0) {
			if (readElementText(modelChild, cData)) {
				sID = std::string(cData, strlen(cData));
				if (m_bDebug) std::cout << "ID: " << sID << "\n";
			}
		}
		else if (strcmp(childValue, "Shader") == 0) {
			if (readElementText(modelChild, cData)) {
				text->setShader(m_res->getShader(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "String") == 0) {
			if (readElementText(modelChild, cData)) {
				string sString = std::string(cData, strlen(cData));
				text->setString(sString);
			}
			//if (m_bDebug) std::cout << "String : " << sString << "\n  ";
		}
		else if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			transform->setPosition(v);
			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Colour") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			text->setColour(vec4(v, 1.0f));
			if (m_bDebug) std::cout << "Colour Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
	}
	return entity;
}

std::shared_ptr<Entity> SceneLoader::loadModel(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* cData = "";			//Temporary storage for element data
	if (m_bDebug) std::cout << "\nLoading Model \n  ";
	std::shared_ptr<Entity> entity = m_factory->createActor();
	auto model = entity->get<Component::Model>();
	auto transform = entity->get<Component::Transformable>();
	glm::vec3 Dimensions;
	float radius;
	float mass = 1;
	float restitution = 0.5;
	const char* Value;
	vector<std::string> components;
	std::string tempString;

	std::string sID;
	//Look at Model Element
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement())
	{
		const char* childValue = modelChild->Value();
		if (strcmp(childValue, "ID") == 0) {
			if (readElementText(modelChild, cData)) {
				sID = std::string(cData, strlen(cData));
				if (m_bDebug) std::cout << "ID: " << sID << "\n";
				entity->setName(sID);
			}
		}
		if (strcmp(childValue, "Component") == 0) {
			if (readElementText(modelChild, cData)) {
				tempString = std::string(cData, strlen(cData));
				if (m_bDebug) std::cout << "Adding component : " << tempString << "\n";
				components.push_back(tempString);
			}
		}
		else if (strcmp(childValue, "Player") == 0) {
			//Attach player component
			entity->attach<Component::Player>();
			if (readElementText(modelChild, cData)) {
				entity->get<Component::Player>()->setMoveSpeed(atof(cData));
			}
		}
		else if (strcmp(childValue, "Mesh") == 0) {
			if (readElementText(modelChild, cData)) {
		
				model->m_aMeshes.push_back(m_res->getAssimpMesh(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Shader") == 0) {
			if (readElementText(modelChild, cData)) {
				model->m_shader = (m_res->getShader(std::string(cData, strlen(cData))));
				model->m_shader->initialiseBoneUniforms();
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
			transform->setScale(v);
			if (m_bDebug) std::cout << "Scale Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Rotation") == 0) {
			//Set model rotation
			glm::vec3 v = parseVec3(modelChild);
			transform->setRotation(v);
			if (m_bDebug) std::cout << "Rotation Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Dimensions") == 0) {
			//Set model scale
			glm::vec3 v = parseVec3(modelChild);
			Dimensions = v;
			if (m_bDebug) std::cout << "Dimensions Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Origin") == 0) {
			//Set model origin
			glm::vec3 v = parseVec3(modelChild);
			transform->m_vOrigin = v;
			if (m_bDebug) std::cout << "Origin Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Material") == 0) {
			if (readElementText(modelChild, cData)) {
				model->m_materials.push_back((m_res->getMaterial(std::string(cData, strlen(cData)))));
			}
		}
		else if (strcmp(childValue, "Radius") == 0) {
			if (readElementText(modelChild, cData)) {
				radius = atof(cData);
			}
		}
		else if (strcmp(childValue, "Mass") == 0) {
			if (readElementText(modelChild, cData)) {
				mass = atof(cData);
			}
		}
		else if (strcmp(childValue, "Restitution") == 0) {
			if (readElementText(modelChild, cData)) {
				restitution = atof(cData);
			}
		}

	}

	return entity;
}

std::shared_ptr<Entity> SceneLoader::createEntity(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* cData = "";			//Temporary storage for element data
	if (m_bDebug) std::cout << "\nLoading Model \n  ";
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();	//Create entity

	//Attach components
	std::string sTemp;	//Temporary string
	for (XMLElement* parent = e->FirstChildElement(); parent != NULL; parent = parent->NextSiblingElement())
	{
		const char* childValue = parent->Value();
		if (strcmp(childValue, "Name") == 0) {
			if (readElementText(parent, cData)) {
				sTemp = std::string(cData, strlen(cData));
				entity->setName(sTemp);
				if (m_bDebug) std::cout << "Name: " << sTemp << "\n";
			}
		}
		else if (strcmp(childValue, "Transformable") == 0) {
			attachTransformable(entity, parent);
		}
		else if (strcmp(childValue, "Model") == 0) {
			attachModel(entity, parent);
		}
		else if (strcmp(childValue, "Physical") == 0) {
			attachPhysical(entity, parent);
		}
		else if (strcmp(childValue, "AABB") == 0) {
			attachAABB(entity, parent);
		}
		else if (strcmp(childValue, "OBB") == 0) {
			attachOBB(entity, parent);
		}
		else if (strcmp(childValue, "Sphere") == 0) {
			attachSphere(entity, parent);
		}
		else if (strcmp(childValue, "Camera") == 0) {
			attachCamera(entity, parent);
		}
		else if (strcmp(childValue, "Sound") == 0) {
			attachSound(entity, parent);
		}
		else if (strcmp(childValue, "DirLight") == 0) {
			attachDirLight(entity, parent);
		}
		else if (strcmp(childValue, "PointLight") == 0) {
			attachPointLight(entity, parent);
		}
		else if (strcmp(childValue, "SpotLight") == 0) {
			attachSpotLight(entity, parent);
		}
		else if (strcmp(childValue, "Sprite") == 0) {
			attachSprite(entity, parent);
		}
		else if (strcmp(childValue, "Player") == 0) {
			attachPlayer(entity, parent);
		}
	}

	return entity;
	return std::shared_ptr<Entity>();
}

void SceneLoader::attachTransformable(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* cData = ""; //Temporary storage for element data
	entity->attach<Component::Transformable>();	//Attach component
	auto t = entity->get<Component::Transformable>();	//Get pointer to attached component
	if (m_bDebug) std::cout << "Transformable Component Attached\n";
	//Set component variables
	for (XMLElement* parent = e->FirstChildElement(); parent != NULL; parent = parent->NextSiblingElement()) {
		const char* childValue = parent->Value();
		if (m_bDebug) std::cout << " ";
		if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(parent);	//Parse vec3 data
			t->setPosition(v);			//Set
			if (m_bDebug) std::cout << "Position: " << t  << "\n";
		}
		else if (strcmp(childValue, "Rotation") == 0) {
			glm::vec3 v = parseVec3(parent);	//Parse vec3 data
			t->setRotation(v);			//Set
			if (m_bDebug) std::cout << "Rotation: " << t << "\n";
		}
		else if (strcmp(childValue, "Scale") == 0) {
			glm::vec3 v = parseVec3(parent);	//Parse vec3 data
			t->setScale(v);			//Set
			if (m_bDebug) std::cout << "Scale: " << t << "\n";
		}
		else if (strcmp(childValue, "Origin") == 0) {
			glm::vec3 v = parseVec3(parent);	//Parse vec3 data
			t->setOrigin(v);			//Set
			if (m_bDebug) std::cout << "Origin: " << t << "\n";
		}
	}
}

void SceneLoader::attachModel(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	entity->attach<Component::Model>();			//Attach component
	auto m = entity->get<Component::Model>();	//Get pointer to attached component
	if (m_bDebug) std::cout << "Model Component Attached\n";
	
	char* cData = "";	//Temporary storage for element data
	std::string sTemp;	//Temporary string
	for (XMLElement* parent = e->FirstChildElement(); parent != NULL; parent = parent->NextSiblingElement()) {
		const char* childValue = parent->Value();
		if (m_bDebug) std::cout << " ";
		if (strcmp(childValue, "Mesh") == 0) {
			if (readElementText(parent, cData)) {
				m->addMesh(m_res->getAssimpMesh(std::string(std::string(cData, strlen(cData)))));
			}
		}
		else if (strcmp(childValue, "Shader") == 0) {
			if (readElementText(parent, cData)) {
				m->setShader(m_res->getShader(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Texture") == 0) {
			if (readElementText(parent, cData)) {
				m->addTexture(m_res->getTexture(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Material") == 0) {
			if (readElementText(parent, cData)) {
				m->addMaterial(m_res->getMaterial(std::string(cData, strlen(cData))));
			}
		}
	}
}

void SceneLoader::attachPhysical(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	entity->attach<Physical>();	//Attach component
	auto p = entity->get<Physical>();	//Get pointer to attached component
	if (m_bDebug) std::cout << "Physical Component Attached\n";

	char* cData = "";	//Temporary storage for element data
	std::string sTemp;	//Temporary string
	for (XMLElement* parent = e->FirstChildElement(); parent != NULL; parent = parent->NextSiblingElement()) {
		const char* childValue = parent->Value();
		if (m_bDebug) std::cout << " ";
		if (strcmp(childValue, "Mass") == 0) {
			if (readElementText(parent, cData)) {
				p->m_fMass = stof(parent->ToElement()->GetText());//Set
			}
		}
		else if (strcmp(childValue, "Restitution") == 0) {
			if (readElementText(parent, cData)) {
				p->m_fRestitution = stof(parent->ToElement()->GetText());//Set
			}
		}
	}
}

void SceneLoader::attachAABB(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* cData = ""; //Temporary storage for element data
	entity->attach<AABB>();	//Attach component
	auto a = entity->get<AABB>();	//Get pointer to attached component
	if (m_bDebug) std::cout << "Transformable Component Attached\n";
	//Set component variables
	for (XMLElement* parent = e->FirstChildElement(); parent != NULL; parent = parent->NextSiblingElement()) {
		const char* childValue = parent->Value();
		if (m_bDebug) std::cout << " ";
		if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(parent);	//Parse vec3 data
			a->m_vPosition = v;		//Set
			auto t = entity->get<Component::Transformable>();
			a->m_vLocalTransform =  t->getPosition() - v;		//Set
		}
		else if (strcmp(childValue, "Scale") == 0) {
			glm::vec3 v = parseVec3(parent);	//Parse vec3 data
			a->m_vScale = v;			//Set
		}
		else if (strcmp(childValue, "Origin") == 0) {
			glm::vec3 v = parseVec3(parent);	//Parse vec3 data
			a->m_vOrigin = v;			//Set
		}
	}
}

void SceneLoader::attachSphere(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* cData = ""; //Temporary storage for element data
	entity->attach<Sphere>();	//Attach component
	auto sphere = entity->get<Sphere>();	//Get pointer to attached component
	if (m_bDebug) std::cout << "Sphere Component Attached\n";
	//Set component variables
	for (XMLElement* parent = e->FirstChildElement(); parent != NULL; parent = parent->NextSiblingElement()) {
		const char* childValue = parent->Value();
		if (m_bDebug) std::cout << " ";
		if (strcmp(childValue, "Center") == 0) {
			glm::vec3 v = parseVec3(parent);	//Parse vec3 data
			sphere->m_vCenter = v;		//Set
			if (entity->has<Component::Transformable>()) {
				auto t = entity->get<Component::Transformable>();
				sphere->m_localCenter = t->getPosition() - v;
			}
		}
		else if (strcmp(childValue, "Radius") == 0) {
			sphere->m_fRadius = stof(parent->ToElement()->GetText());//Set
		}
	}
}

void SceneLoader::attachOBB(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* cData = ""; //Temporary storage for element data
	entity->attach<OBB>();	//Attach component
	auto b = entity->get<OBB>();	//Get pointer to attached component
	if (m_bDebug) std::cout << "OBB Component Attached\n";
	//Set component variables
	for (XMLElement* parent = e->FirstChildElement(); parent != NULL; parent = parent->NextSiblingElement()) {
		const char* childValue = parent->Value();
		if (m_bDebug) std::cout << " ";
		if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(parent);	//Parse vec3 data
			b->m_vPosition = v;		//Set
			if (entity->has<Component::Transformable>()) {
				auto t = entity->get<Component::Transformable>();
				b->m_vLocalPos = t->getPosition() - v;
			}
		}
		else if (strcmp(childValue, "Rotation") == 0) {
			glm::vec3 v = parseVec3(parent);	//Parse vec3 data
			b->m_vRotation;					//Set
		}
		else if (strcmp(childValue, "Scale") == 0) {
			glm::vec3 v = parseVec3(parent);	//Parse vec3 data
			b->m_vScale = v;			//Set
		}
		else if (strcmp(childValue, "Origin") == 0) {
			glm::vec3 v = parseVec3(parent);	//Parse vec3 data
			b->m_vOrigin = v;			//Set
		}
	}
}

void SceneLoader::attachCamera(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	//Attach component
	if (m_bDebug) std::cout << "Camera Component Attached\n";

	entity->attach<Component::Camera>();
	auto camera = entity->get<Component::Camera>();	//Get handle to component
	
	char* cData = "";			//Temporary storage for element data
	std::string s;
	char * c;
	std::string sID;
	//Look at Model Element
	for (XMLElement* child = e->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
		const char* childValue = child->Value();
		std::cout << " ";
		if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(child);
			camera->setPosition(v);
			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Orientation") == 0) {
			glm::vec3 v = parseVec3(child);
			camera->setOrientation(v);
			if (m_bDebug) std::cout << "Orientation Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "FOV") == 0) {
			if (readElementText(child, c)) {
				camera->setFOV(atof(c));
			}
			if (m_bDebug) std::cout << "Field of View: " << c << "\n  ";
		}
		else if (strcmp(childValue, "AspectRatio") == 0) {
			if (readElementText(child, c)) {
				camera->setAspectRatio(atof(c));
			}
			if (m_bDebug) std::cout << "Aspect Ratio: " << c << "\n  ";
		}
		else if (strcmp(childValue, "FarPlane") == 0) {
			if (readElementText(child, c)) {
				camera->setFarPlane(atof(c));
			}
			if (m_bDebug) std::cout << "Far plane: " << c << "\n  ";
		}
		else if (strcmp(childValue, "NearPlane") == 0) {
			if (readElementText(child, c)) {
				camera->setNearPlane(atof(c));
			}
			if (m_bDebug) std::cout << "NearPlane: " << c << "\n  ";
		}
		else if (strcmp(childValue, "MoveSpeed") == 0) {
			if (readElementText(child, c)) {
				camera->setMoveSpeed((atof(c)));
			}
			if (m_bDebug) std::cout << "MoveSpeed Speed: " << c << "\n  ";
		}
		else if (strcmp(childValue, "Reach") == 0) {
			if (readElementText(child, c)) {
				camera->setReach(atof(c));
			}
			if (m_bDebug) std::cout << "Reach: " << c << "\n  ";
		}
		else if (strcmp(childValue, "EnableRotation") == 0) {
			if (readElementText(child, c)) {
				camera->enableRotation(atoi(c));
			}
			if (m_bDebug) std::cout << "EnableRotation: " << c << "\n  ";
		}
	}
}

void SceneLoader::attachDirLight(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{	
	using namespace tinyxml2;
	if (m_bDebug) std::cout << "DirectionalLight Component Attached\n";
	char* cData = "";			//Temporary storage for element data
	
	entity->attach<Component::DirectionalLight>();
	auto dir = entity->get<Component::DirectionalLight>();

	std::string sType = "";
	glm::vec3 v;
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()) {
		const char* childValue = modelChild->Value();
		if (m_bDebug) std::cout << " ";
		if (strcmp(childValue, "Ambient") == 0) {
			v = parseVec3(modelChild);
			dir->setAmbient(v);
			if (m_bDebug) std::cout << "Ambient intensity: " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Diffuse") == 0) {
			v = parseVec3(modelChild);
			if (m_bDebug) std::cout << "Diffuse intensity: " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Specular") == 0) {
			v = parseVec3(modelChild);
			if (m_bDebug) std::cout << "Specular intensity: " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
	}
}

void SceneLoader::attachPointLight(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	if (m_bDebug) std::cout << "Point Component Attached\n";
	char* cData = "";			//Temporary storage for element data

	entity->attach<Component::PointLight>();
	auto dir = entity->get<Component::PointLight>();

	std::string sType = "";
	glm::vec3 v;
	float f;
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()) {
		const char* childValue = modelChild->Value();
		if (m_bDebug) std::cout << " ";
		if (strcmp(childValue, "Ambient") == 0) {
			v = parseVec3(modelChild);
			dir->setAmbient(v);
			if (m_bDebug) std::cout << "Ambient intensity: " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Diffuse") == 0) {
			v = parseVec3(modelChild);
			dir->setDiffuse(v);
			if (m_bDebug) std::cout << "Diffuse intensity: " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Specular") == 0) {
			v = parseVec3(modelChild);
			dir->setSpecular(v);
			if (m_bDebug) std::cout << "Specular intensity: " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Radius") == 0) {
			if (readElementText(modelChild, cData)) { 
				f = atof(cData);
				dir->setRadius(f);
				if (m_bDebug) std::cout << "Radius: " << f << "\n  ";
			}
		}
	}
}

void SceneLoader::attachSpotLight(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	if (m_bDebug) std::cout << "SpotLight Component Attached\n";
	char* cData = "";			//Temporary storage for element data

	entity->attach<Component::Spotlight>();
	auto light = entity->get<Component::Spotlight>();

	std::string sType = "";
	glm::vec3 v;
	float f;
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()) {
		const char* childValue = modelChild->Value();
		if (m_bDebug) std::cout << " ";
		if (strcmp(childValue, "Ambient") == 0) {
			v = parseVec3(modelChild);
			light->setAmbient(v);
			if (m_bDebug) std::cout << "Ambient intensity: " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Diffuse") == 0) {
			v = parseVec3(modelChild);
			light->setDiffuse(v);
			if (m_bDebug) std::cout << "Diffuse intensity: " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Specular") == 0) {
			v = parseVec3(modelChild);
			light->setSpecular(v);
			if (m_bDebug) std::cout << "Specular intensity: " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "CutOff") == 0) {
			if (readElementText(modelChild, cData)) {
				f = atof(cData);
				light->setCutOff(f);
				if (m_bDebug) std::cout << "CutOff: " << f << "\n  ";
			}
		}
		else if (strcmp(childValue, "OuterCutOff") == 0) {
			if (readElementText(modelChild, cData)) {
				f = atof(cData);
				light->setOuterCutOff(f);
				if (m_bDebug) std::cout << "CutOff: " << f << "\n  ";
			}
		}
		else if (strcmp(childValue, "Constant") == 0) {
			if (readElementText(modelChild, cData)) {
				f = atof(cData);
				light->setConstant(f);
				if (m_bDebug) std::cout << "CutOff: " << f << "\n  ";
			}
		}
		else if (strcmp(childValue, "Linear") == 0) {
			if (readElementText(modelChild, cData)) {
				f = atof(cData);
				light->setLinear(f);
				if (m_bDebug) std::cout << "CutOff: " << f << "\n  ";
			}
		}
		else if (strcmp(childValue, "Quadratic") == 0) {
			if (readElementText(modelChild, cData)) {
				f = atof(cData);
				light->setLinear(f);
				if (m_bDebug) std::cout << "Quadratic: " << f << "\n  ";
			}
		}
	}
}

void SceneLoader::attachSound(std::shared_ptr<Entity> entity, tinyxml2::XMLElement* e)
{
	using namespace tinyxml2;
	
	if (m_bDebug) std::cout <<  "Audio Component Attached\n  ";
	auto sound = entity->get<Component::Sound>();
	
	char* cData = "";			//Temporary storage for element data
	std::string s;
	char * c;
	glm::vec3 v;
	//Look at Model Element
	for (XMLElement* child = e->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
		const char* childValue = child->Value();
		if (m_bDebug) std::cout << " ";
		if (strcmp(childValue, "File") == 0) {
			//Load file
			if (readElementText(child, c)) {
				std::string sFile(c, strlen(c));
				sound->setFile(sFile);
				if (m_bDebug) std::cout << "File Set : " << sFile << "\n  ";
			}
		}
		else if (strcmp(childValue, "isPlaying") == 0) {
			if (readElementText(child, c)) {
				std::string var(c, strlen(c));
				if (strcmp(c, "false") == 0)
					sound->setPlaying(false);
				else if (strcmp(c, "true") == 0)
					sound->setPlaying(true);
			}
			if (m_bDebug) std::cout << "isPlaying Set : " << atof(c) << "\n  ";
		}
		else if (strcmp(childValue, "isInitialized") == 0) {
			if (readElementText(child, c)) {
				std::string var(c, strlen(c));
				if (strcmp(c, "false") == 0)
					sound->setInitialized(false);
				else if (strcmp(c, "true") == 0)
					sound->setInitialized(true);
			}
			if (m_bDebug) std::cout << "isInitialized Set : " << atof(c) << "\n  ";
		}
		else if (strcmp(childValue, "isLooping") == 0) {
			if (readElementText(child, c)) {
				std::string var(c, strlen(c));
				if (strcmp(c, "false") == 0)
					sound->setLooping(false);
				else if (strcmp(c, "true") == 0)
					sound->setLooping(true);
			}
			if (m_bDebug) std::cout << "isLooping set: " << c << "\n  ";
		}
		else if (strcmp(childValue, "startsPaused") == 0) {
			if (readElementText(child, c)) {
				std::string var(c, strlen(c));
				if (strcmp(c, "false") == 0)
					sound->setPaused(false);
				else if (strcmp(c, "true") == 0)
					sound->setPaused(true);
			}
			if (m_bDebug) std::cout << "startsPaused set: " << c << "\n  ";
		}
		else if (strcmp(childValue, "sound3D") == 0) {
			if (readElementText(child, c)) {
				std::string var(c, strlen(c));
				if (strcmp(c, "false") == 0)
					sound->setSound3D(false);
				else if (strcmp(c, "true") == 0)
					sound->setSound3D(true);
			}
			if (m_bDebug) std::cout << "3D sound set: " << c << "\n  ";
		}
		else if (strcmp(childValue, "Volume") == 0) {
			if (readElementText(child, c)) {
				sound->setVolume(atof(c));
			}
			if (m_bDebug) std::cout << "Volume set: " << c << "\n  ";
		}
		else if (strcmp(childValue, "MinDistance") == 0) {
			if (readElementText(child, c)) {
				sound->setMinDist(atof(c));
			}
			if (m_bDebug) std::cout << "Minimum distance set: " << c << "\n  ";
		}
	}

}

void SceneLoader::attachSprite(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;

	if (m_bDebug) std::cout << "Sprite Component Attached\n  ";
	auto sprite = entity->get<Component::SpriteRenderer>();

	char* cData = "";			//Temporary storage for element data
	std::string s;
	char * c;
	glm::vec3 v;
	//Look at Model Element
	for (XMLElement* child = e->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
		const char* childValue = child->Value();
		if (m_bDebug) std::cout << " ";
		if (strcmp(childValue, "Shader") == 0) {
			if (readElementText(child, c)) {
				std::string sFile(c, strlen(c));
				if (readElementText(child, cData)) {
					sprite->setShader(m_res->getShader(sFile));
				}
				if (m_bDebug) std::cout << "Shader Set : " << sFile << "\n  ";
			}
		}
		else if (strcmp(childValue, "Texture") == 0) {
			if (readElementText(child, c)) {
				std::string sFile(c, strlen(c));
				if (readElementText(child, cData)) {
					sprite->setTexture(m_res->getTexture(sFile));
				}
				if (m_bDebug) std::cout << "Texture Set : " << sFile << "\n  ";
			}
		}
		else if (strcmp(childValue, "Color") == 0) {
			if (readElementText(child, c)) {
				glm::vec3 v = parseVec3(child);	//Parse vec3 data
				sprite->setColor(v);			//Set
				if (m_bDebug) std::cout << "Colour: " << v.x << " " << v.y << " " << v.z << "\n";
			}
		}
	}

}

void SceneLoader::attachPlayer(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	entity->attach<Component::Player>();
	auto p = entity->get<Component::Player>();
	
	if (m_bDebug) std::cout << "Player Component Attached\n  ";

	char* cData = "";			//Temporary storage for element data
	std::string s;
	char * c;
	glm::vec3 v;
	//Look at Model Element
	for (XMLElement* child = e->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
		const char* childValue = child->Value();
		if (m_bDebug) std::cout << " ";
		if (strcmp(childValue, "MoveSpeed") == 0) {
			if (readElementText(child, c)) {
				p->setMoveSpeed(atof(c));
			}
			if (m_bDebug) std::cout << "MoveSpeed: " << c << "\n  ";
		}
		else if (strcmp(childValue, "TurnSpeed") == 0) {
			if (readElementText(child, c)) {
				p->setTurnSpeed(atof(c));
			}
			if (m_bDebug) std::cout << "TurnSpeed: " << c << "\n  ";
		}
	}
}

void SceneLoader::attachPickup(std::shared_ptr<Entity> entity, tinyxml2::XMLElement * e)
{
	entity->attach<Component::Pickup>();
}

std::shared_ptr<Entity> SceneLoader::loadLight(tinyxml2::XMLElement * e)
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();

	entity->attach<Component::Transformable>();

	glm::vec3 vPosition;
	glm::vec3 vAmbient, vDiffuse, vSpecular;
	glm::vec3 vDirection = glm::vec3(0.0f, -1.0f, 0.0f);
	float fRadius = 0.0f;

	//Default values
	float fCutOff = 45.0f;
	float fOuterCutoff = 45.0f;
	float fConstant = 1.0f;
	float fLinear = 0.09f;
	float fQuadratic = 0.032f;

	using namespace tinyxml2;

	char* cData = "";			//Temporary storage for element data

	if (m_bDebug) std::cout << "\nLoading Light \n  ";

	std::string sID;
	std::string sType = "";
	//Look at Model Element
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()) {
		const char* childValue = modelChild->Value();
		if (strcmp(childValue, "ID") == 0) {
			if (readElementText(modelChild, cData)) {
				sID = std::string(cData, strlen(cData));
			}
		}
		else if (strcmp(childValue, "Type") == 0) {
			if (readElementText(modelChild, cData)) {
				sType = std::string(cData, strlen(cData));
			}
		}
		else if (strcmp(childValue, "Position") == 0) {
			vPosition = parseVec3(modelChild);
			if (m_bDebug) std::cout << "Position Set : " << vPosition.x << ", " << vPosition.y << ", " << vPosition.z << "\n  ";
		}
		else if (strcmp(childValue, "Radius") == 0) {
			if (readElementText(modelChild, cData)) { fRadius = atof(cData); }
			if (m_bDebug) std::cout << "Radius Set : " << fRadius << "\n  ";
		}
		else if (strcmp(childValue, "Direction") == 0) {
			vDirection = parseVec3(modelChild);
			if (m_bDebug) std::cout << "Light Direction: " << vDirection.x << ", " << vDirection.y << ", " << vDirection.z << "\n  ";
		}
		else if (strcmp(childValue, "Ambient") == 0) {
			vAmbient = parseVec3(modelChild);
			if (m_bDebug) std::cout << "Ambient intensity: " << vAmbient.x << ", " << vAmbient.y << ", " << vAmbient.z << "\n  ";
		}
		else if (strcmp(childValue, "Diffuse") == 0) {
			vDiffuse = parseVec3(modelChild);
			if (m_bDebug) std::cout << "Diffuse intensity: " << vDiffuse.x << ", " << vDiffuse.y << ", " << vDiffuse.z << "\n  ";
		}
		else if (strcmp(childValue, "Specular") == 0) {
			vSpecular = parseVec3(modelChild);
			if (m_bDebug) std::cout << "Specular intensity: " << vSpecular.x << ", " << vSpecular.y << ", " << vSpecular.z << "\n  ";
		}
		else if (strcmp(childValue, "CutOff") == 0) {
			if (readElementText(modelChild, cData)) { fCutOff = atof(cData); }
			if (m_bDebug) std::cout << "CutOff Set : " << fCutOff << "\n  ";
		}
		else if (strcmp(childValue, "OuterCutOff") == 0) {
			if (readElementText(modelChild, cData)) { fOuterCutoff = atof(cData); }
			if (m_bDebug) std::cout << "OuterCutOff Set : " << fOuterCutoff << "\n  ";
		}
		else if (strcmp(childValue, "Constant") == 0) {
			if (readElementText(modelChild, cData)) { fConstant = atof(cData); }
			if (m_bDebug) std::cout << "Constant Set : " << fConstant << "\n  ";
		}
		else if (strcmp(childValue, "Linear") == 0) {
			if (readElementText(modelChild, cData)) { fLinear = atof(cData); }
			if (m_bDebug) std::cout << "Linear Set : " << fLinear << "\n  ";
		}
		else if (strcmp(childValue, "Quadratic") == 0) {
			if (readElementText(modelChild, cData)) { fQuadratic = atof(cData); }
			if (m_bDebug) std::cout << "Quadratic Set : " << fQuadratic << "\n  ";
		}
	}

	auto t = entity->get<Component::Transformable>();

	if (sType == "Directional") {
		entity->attach<Component::DirectionalLight>();
		auto dirLight = entity->get<Component::DirectionalLight>();
		dirLight->setDirection(vDirection);
		dirLight->setIntensity(vAmbient, vDiffuse, vSpecular);
	}
	else if (sType == "Point") {
		entity->attach<Component::PointLight>();
		auto pointLight = entity->get<Component::PointLight>();
		if (entity->has<Component::Transformable>()) {
			t = entity->get<Component::Transformable>();
			t->setPosition(vPosition);
		}
		pointLight->setIntensity(vAmbient, vDiffuse, vSpecular);
		pointLight->setRadius(fRadius);
	}
	else if (sType == "Spotlight") {
		entity->attach<Component::Spotlight>();
		auto spotlight = entity->get<Component::Spotlight>();
		if (entity->has<Component::Transformable>()) {
			t->setPosition(vPosition);
		}
		spotlight->setIntensity(vAmbient, vDiffuse, vSpecular);
		spotlight->setDirection(vDirection);
		spotlight->setCutOff(fCutOff);
		spotlight->setOuterCutOff(fOuterCutoff);
		spotlight->setConstant(fConstant);
		spotlight->setLinear(fLinear);
		spotlight->setQuadratic(fQuadratic);
	}
	else {
		entity->destroy();					//Returns empty destroyed entity
		return std::make_shared<Entity>();	//Return empty entity
	}
	return entity;
}

std::shared_ptr<Entity> SceneLoader::loadCamera(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;

	char* cData = "";			//Temporary storage for element data

	if (m_bDebug) std::cout << "\nLoading Camera \n  ";

	std::shared_ptr<Entity> entity = m_factory->createCamera(glm::vec3(0.0f));

	auto camera = entity->get<Component::Camera>();

	std::string s;
	char * c;
	std::string sID;
	float fNear = 0.1f;
	float fFar = 1000.0f;
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
			camera->setPosition(v);
			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Orientation") == 0) {
			glm::vec3 v = parseVec3(child);
			//camera->setRotation(v);
			camera->setOrientation(v);
			if (m_bDebug) std::cout << "Orientation Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "FOV") == 0) {
			if (readElementText(child, c)) {
				camera->setFOV(atof(c));
			}
			if (m_bDebug) std::cout << "Field of View: " << c << "\n  ";
		}
		else if (strcmp(childValue, "AspectRatio") == 0) {
			if (readElementText(child, c)) {
				camera->setAspectRatio(atof(c));
			}
			if (m_bDebug) std::cout << "Aspect Ratio: " << c << "\n  ";
		}
		else if (strcmp(childValue, "FarPlane") == 0) {
			if (readElementText(child, c)) {
				camera->setFarPlane(atof(c));
			}
			if (m_bDebug) std::cout << "Far plane: " << c << "\n  ";
		}
		else if (strcmp(childValue, "NearPlane") == 0) {
			if (readElementText(child, c)) {
				camera->setNearPlane(atof(c));
			}
			if (m_bDebug) std::cout << "NearPlane: " << c << "\n  ";
		}
		else if (strcmp(childValue, "MoveSpeed") == 0) {
			if (readElementText(child, c)) {
				camera->setMoveSpeed((atof(c)));
			}
			if (m_bDebug) std::cout << "MoveSpeed Speed: " << c << "\n  ";
		}
	}
	return entity;
}

std::shared_ptr<Entity> SceneLoader::loadAudio(tinyxml2::XMLElement* e)
{
	using namespace tinyxml2;

	char* cData = "";			//Temporary storage for element data

	if (m_bDebug) std::cout << "\nLoading Audio \n  ";

	std::shared_ptr<Entity> entity = m_factory->createSound();
	auto sound = entity->get<Component::Sound>();

	std::string s;
	char * c;
	std::string sID;
	glm::vec3 v;

	//Look at Model Element
	for (XMLElement* child = e->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
		const char* childValue = child->Value();
		if (strcmp(childValue, "ID") == 0) {
			if (readElementText(child, cData)) {
				sID = std::string(cData, strlen(cData));
			}
		}
		else if (strcmp(childValue, "File") == 0) {
			//Load file
			if (readElementText(child, c)) {
				std::string sFile(c, strlen(c));
				sound->setFile(sFile);
				if (m_bDebug) std::cout << "File Set : " << sFile << "\n  ";
			}
		}
		else if (strcmp(childValue, "isPlaying") == 0) {
			if (readElementText(child, c)) {
				std::string var(c, strlen(c));
				if (strcmp(c, "false") == 0)
					sound->setPlaying(false);
				else if (strcmp(c, "true") == 0)
					sound->setPlaying(true);
			}
			if (m_bDebug) std::cout << "isPlaying Set : " << atof(c) << "\n  ";
		}
		else if (strcmp(childValue, "isInitialized") == 0) {
			if (readElementText(child, c)) {
				std::string var(c, strlen(c));
				if (strcmp(c, "false") == 0)
					sound->setInitialized(false);
				else if (strcmp(c, "true") == 0)
					sound->setInitialized(true);
			}
			if (m_bDebug) std::cout << "isInitialized Set : " << atof(c) << "\n  ";
		}
		else if (strcmp(childValue, "isLooping") == 0) {
			if (readElementText(child, c)) {
				std::string var(c, strlen(c));
				if (strcmp(c, "false") == 0)
					sound->setLooping(false);
				else if (strcmp(c, "true") == 0)
					sound->setLooping(true);
			}
			if (m_bDebug) std::cout << "isLooping set: " << c << "\n  ";
		}
		else if (strcmp(childValue, "startsPaused") == 0) {
			if (readElementText(child, c)) {
				std::string var(c, strlen(c));
				if (strcmp(c, "false") == 0)
					sound->setPaused(false);
				else if (strcmp(c, "true") == 0)
					sound->setPaused(true);
			}
			if (m_bDebug) std::cout << "startsPaused set: " << c << "\n  ";
		}
		else if (strcmp(childValue, "sound3D") == 0) {
			if (readElementText(child, c)) {
				std::string var(c, strlen(c));
				if (strcmp(c, "false") == 0)
					sound->setSound3D(false);
				else if (strcmp(c, "true") == 0)
					sound->setSound3D(true);

				entity->attach<Component::Transformable>();
			}
			if (m_bDebug) std::cout << "3D sound set: " << c << "\n  ";
		}
		else if (strcmp(childValue, "Volume") == 0) {
			if (readElementText(child, c)) {
				sound->setVolume(atof(c));
			}
			if (m_bDebug) std::cout << "Volume set: " << c << "\n  ";
		}
		else if (strcmp(childValue, "MinDistance") == 0) {
			if (readElementText(child, c)) {
				sound->setMinDist(atof(c));
			}
			if (m_bDebug) std::cout << "Minimum distance set: " << c << "\n  ";
		}
		else if (strcmp(childValue, "Position") == 0) {
			v = parseVec3(child);
			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
	}
	if (entity->has<Component::Transformable>()) {
		auto t = entity->get<Component::Transformable>();
		t->setPosition(v);
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
	std::string sName;

	//-- Add entities into the scene --//
	if (str == "Game") {
		EntityManager* entities = m_SceneLoading->getEntityManager();	//Get scene entity manager used to add entities in to the scene
																//Add Scene Entities
		if (m_bDebug) std::cout << "\nLoading Scene elements\n ";
		for (XMLElement* element = node->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
		{
			if (strcmp(element->Value(), "Name") == 0) {
				if (readElementText(element, c)) {
					m_SceneLoading->setName(std::string(c, strlen(c)));	//Set Scene Name
				}
			}
			else if (strcmp(element->Value(), "Model") == 0) {
				entities->addEntity(loadModel(element));
			}
			else if (strcmp(element->Value(), "Entity") == 0) {
				//entities->addEntity(loadEntity(element));
				entities->addEntity(createEntity(element));
			}
			else if (strcmp(element->Value(), "Light") == 0) {
				entities->addEntity(loadLight(element));
			}
			else if (strcmp(element->Value(), "Camera") == 0) {
				entities->addEntity(loadCamera(element));
			}
			else if (strcmp(element->Value(), "Physics") == 0) {
				entities->addEntity(loadModel(element));
			}
			else if (strcmp(element->Value(), "Audio") == 0) {
				entities->addEntity(loadAudio(element));
			}
			else if (strcmp(element->Value(), "Text") == 0) {
				entities->addEntity(loadText(element));
			}
			else if (strcmp(element->Value(), "Sprite") == 0) {
				entities->addEntity(loadSprite(element));
			}
			else if (strcmp(element->Value(), "Button") == 0) {
				entities->addEntity(loadButton(element));
			}
		}
	}
}

bool SceneLoader::readResourceFile(tinyxml2::XMLNode * node, bool forceReloadRes)
{
	if (forceReloadRes) {
		m_res->ClearResources();
	}
	using namespace tinyxml2;
	//Get Resource File Location
	std::string sFile = node->FirstChildElement()->GetText();

	//Check if resources need to be loaded
	if (!m_res->isResFileLoaded(sFile)) {
		XMLDocument doc;
		if (doc.LoadFile(sFile.c_str()) != XML_SUCCESS) {
			//Failed to load
			std::cout << "Could not load ResourceFile : " << sFile << "\n";
			return false;
		}

		//Empty the resource manager
		m_res->ClearResources();

		if (m_bDebug) std::cout << "Reading Resource file: " << sFile << "\n";

		XMLNode *ptrRoot = doc.FirstChild();
		if (ptrRoot == nullptr) {
			std::cout << "No root: " << sFile << "\n";
			return false;
		}

		for (XMLNode* node = ptrRoot; node != NULL; node = node->NextSiblingElement()) {
			const char* value = node->Value();

			if (strcmp(node->Value(), "Resources") == 0) {
				readResources(node);
			}
		}
		m_res->addLoadedResFile(sFile);	//Record that this file has been loaded
		return true;
	}
	else {
		if (m_bDebug) std::cout << "Resource file has already been loaded: " << sFile << "\n";
		return true;
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

bool SceneLoader::readElementText(tinyxml2::XMLElement* e, char*& data)
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

	glm::vec3 v(0.0f, 0.0f, 0.0f);

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

SceneLoader::SceneLoader()
{
	m_factory = EntityFactory::getInstance();
	m_res = ResourceManager::getInstance();		//Pointer to Resource manager
	m_LoadingState = Idle;
	m_node = NULL;
	m_rootNode = NULL;
}

SceneLoader::~SceneLoader()
{

}

std::shared_ptr<Scene> SceneLoader::fastLoadScene(std::string sFilename, bool forceLoadRes /*!< Optional default is false*/)
{
	std::string sLocation = m_sSceneFiles + sFilename;
	using namespace tinyxml2;
	m_SceneLoading = std::make_shared<Scene>();
	//Load xml scene file
	XMLDocument doc;
	if (doc.LoadFile(sLocation.c_str()) != XML_SUCCESS) {
		//Failed to load
		std::cout << "Could not load file: " << sLocation << "\n";
		return false;
	}

	if (m_bDebug) std::cout << "Reading scene file: " << sLocation << "\n";

	XMLNode *ptrRoot = doc.FirstChild();
	if (ptrRoot == nullptr) {
		std::cout << "No root: " << sLocation << "\n";
		return false;
	}

	for (XMLNode* node = ptrRoot; node != NULL; node = node->NextSiblingElement()) {
		const char* value = node->Value();

		if (strcmp(node->Value(), "Resources") == 0) {
			readResources(node);
		}
		else if (strcmp(node->Value(), "ResourceFile") == 0) {
			readResourceFile(node, forceLoadRes);
		}
		else if (strcmp(node->Value(), "Scene") == 0) {
			m_SceneLoading = std::make_shared<Scene>();	//Create Scene
			readScene(node);
		}
	}
	return m_SceneLoading;	// Return loaded scene
}

bool SceneLoader::loadScene(std::shared_ptr<Scene>& scene, std::string sFilename, bool forceLoadRes)
{
	using namespace tinyxml2;
	//Load xml scene file
	if (m_LoadingState == Idle) {
		std::string sLocation = m_sSceneFiles + sFilename;
		if (m_document.LoadFile(sLocation.c_str()) != XML_SUCCESS) {
			//Failed to load
			std::cout << "Could not load file: " << sLocation << "\n";
			return false;
		}

		if (m_bDebug) std::cout << "Reading scene file: " << sLocation << "\n";
		m_SceneLoading = std::make_shared<Scene>();
		m_rootNode = m_document.FirstChild();
		m_node = m_rootNode;
		if (m_rootNode == nullptr) {
			std::cout << "No root: " << sLocation << "\n";
			terminate();
		}
		m_LoadingState = LoadScene;
	}
	//Choose a loading state
	else {
		if (m_node != NULL) {
			const char* value = m_node->Value();

			if (strcmp(m_node->Value(), "Resources") == 0) {
				readResources(m_node);
			}
			else if (strcmp(m_node->Value(), "ResourceFile") == 0) {
				readResourceFile(m_node, forceLoadRes);
			}
			else if (strcmp(m_node->Value(), "Scene") == 0) {
				readScene(m_node);
			}
			m_node = m_node->NextSiblingElement();	//Next Node
		}
		else {
			//Finished Reading XML file
			m_rootNode = NULL;
			scene = std::shared_ptr<Scene >(m_SceneLoading);
			m_SceneLoading = NULL;
			m_LoadingState = Idle;
			return true;
		}
	}

	return false;	// Not finished loading
}
