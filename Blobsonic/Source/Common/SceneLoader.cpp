#include <stdafx.h>
#include "SceneLoader.h"
#include <cstdlib>
#include "SplashScene.h"

void SceneLoader::loadMesh(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	Mesh mesh;
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
				mesh.load(sFile);
			};
		}
		else if (strcmp(childValue, "Texture") == 0) {

		}
	}
	m_res->addMesh(s,mesh);	//Add mesh to resource manager;
	if (m_bDebug) std::cout << " Mesh Loaded: " << s << "\n";
}

void SceneLoader::loadTexture(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* c = "";
	std::string s;
	Texture* texture = NULL;
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
				texture = new Texture(bmp);
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
	Material material;
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
			material.setAmbient(v);
		}
		else if (strcmp(childValue, "DiffuseReflect") == 0) {
			v = parseVec3(Child);
			material.setDiffuse(v);
		}
		else if (strcmp(childValue, "SpecularReflect") == 0) {
			v = parseVec3(Child);
			material.setSpecular(v);
		}
		else if (strcmp(childValue, "Shininess") == 0) {
			if (readElementText(Child, c)) {
				material.setShininess(atof(c));
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

std::pair<std::string, Model> SceneLoader::loadModel(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;

	char* cData = "";			//Temporary storage for element data

	if (m_bDebug) std::cout << "\nLoading Model \n  ";

	Model model;
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
				model.setMesh(m_res->getMesh(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Shader") == 0) {
			if (readElementText(modelChild, cData)) {
				model.setShader(m_res->getShader(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Texture") == 0) {
			if (readElementText(modelChild, cData)) {
				model.setTexture(m_res->getTexture(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			model.setPosition(v);

			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Scale") == 0) {
			//Set model scale
			glm::vec3 v = parseVec3(modelChild);
			model.setScale(v);
			if (m_bDebug) std::cout << "Scale Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Origin") == 0) {
			//Set model origin
			glm::vec3 v = parseVec3(modelChild);
			model.setOrigin(v);
			if (m_bDebug) std::cout << "Origin Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Material") == 0) {
			if (readElementText(modelChild, cData)) {
				model.setMaterial(m_res->getMaterial(std::string(cData, strlen(cData))));
			}
			
		}
	}
	return std::pair<std::string, Model>(sID,model);
}

std::pair<std::string, Model> SceneLoader::loadPhysicsObject(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;

	char* cData = "";			//Temporary storage for element data

	if (m_bDebug) std::cout << "\nLoading Model \n  ";

	Model model;
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
				model.setMesh(m_res->getMesh(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Shader") == 0) {
			if (readElementText(modelChild, cData)) {
				model.setShader(m_res->getShader(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Texture") == 0) {
			if (readElementText(modelChild, cData)) {
				model.setTexture(m_res->getTexture(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			model.setPosition(v);

			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Scale") == 0) {
			//Set model scale
			glm::vec3 v = parseVec3(modelChild);
			model.setScale(v);
			if (m_bDebug) std::cout << "Scale Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Origin") == 0) {
			//Set model origin
			glm::vec3 v = parseVec3(modelChild);
			model.setOrigin(v);
			if (m_bDebug) std::cout << "Origin Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Material") == 0) {
			if (readElementText(modelChild, cData)) {
				model.setMaterial(m_res->getMaterial(std::string(cData, strlen(cData))));
			}

		}
	}
	

	return std::pair<std::string, Model>(sID, model);
}


std::pair<std::string, Light> SceneLoader::loadLight(tinyxml2::XMLElement * e)
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

std::pair<std::string, QuatCamera> SceneLoader::loadCamera(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;

	char* cData = "";			//Temporary storage for element data

	if (m_bDebug) std::cout << "\nLoading Camera \n  ";

	QuatCamera camera;
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
			camera.setPosition(v);
			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Orientation") == 0) {
			glm::vec3 v = parseVec3(child);
			camera.rotate(v.x,v.y);
			camera.roll(v.z);
			if (m_bDebug) std::cout << "Orientation Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "FOV") == 0) {
			if (readElementText(child, c)) {
				camera.setFieldOfView(atof(c));
			}
			if (m_bDebug) std::cout << "Field of View: " << c << "\n  ";
		}
		else if (strcmp(childValue, "AspectRatio") == 0) {
			if (readElementText(child, c)) {
				camera.setAspectRatio(atof(c));
			}
			if (m_bDebug) std::cout << "Aspect Ratio: " << c << "\n  ";
		}
		else if (strcmp(childValue, "FarPlane") == 0) {
			if (readElementText(child, c)) {
				fFar = atof(c);
			}
			if (m_bDebug) std::cout << "Far plane: " << c << "\n  ";
		}
		else if (strcmp(childValue, "NearPlane") == 0) {
			if (readElementText(child, c)) {
				fNear = atof(c);
			}
			if (m_bDebug) std::cout << "NearPlane: " << c << "\n  ";
		}
		else if (strcmp(childValue, "RotSpeed") == 0) {
			if (readElementText(child, c)) {
				camera.setRotateSpeed(atof(c));
			}
			if (m_bDebug) std::cout << "Rotation Speed: " << c << "\n  ";
		}
		else if (strcmp(childValue, "MoveSpeed") == 0) {
			if (readElementText(child, c)) {
				camera.setMoveSpeed(atof(c));
			}
			if (m_bDebug) std::cout << "MoveSpeed Speed: " << c << "\n  ";
		}
	}
	camera.setNearAndFarPlanes(fNear, fFar);
	return std::pair<std::string, QuatCamera>(sID, camera);
}

std::pair<std::string, MyRobot> SceneLoader::loadRobot(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;

	char* cData = "";			//Temporary storage for element data

	if (m_bDebug) std::cout << "\nLoading Model \n  ";

	MyRobot robot(m_res->getMesh("cube_mesh"));
	std::string sID;
	//Look at Model Element
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()) {
		const char* childValue = modelChild->Value();
		if (strcmp(childValue, "ID") == 0) {
			if (readElementText(modelChild, cData)) {
				sID = std::string(cData, strlen(cData));
			}
		}
		else if (strcmp(childValue, "Shader") == 0) {
			if (readElementText(modelChild, cData)) {
				robot.setShader(m_res->getShader(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			robot.setPosition(v.x,v.y,v.z);
			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Material") == 0) {
			if (readElementText(modelChild, cData)) {
				robot.setMaterial(m_res->getMaterial(std::string(cData, strlen(cData))));
			}

		}
	}
	return std::pair<std::string, MyRobot>(sID, robot);
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

	if (str == "Game") {
		//std::shared_ptr<GameScene> gameScene = std::make_unique<GameScene>();	//Create scene

		//if (m_bDebug) std::cout << "\nLoading Scene elements\n ";
		//for (XMLElement* element = node->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
		//{
		//	if (strcmp(element->Value(), "ID") == 0) {
		//		if (readElementText(element, c)) {
		//			sID = std::string(c, strlen(c));		//ID
		//		}
		//	}
		//	else if (strcmp(element->Value(), "Model") == 0) {
		//		gameScene->addModel(loadModel(element));
		//	}
		//	else if (strcmp(element->Value(), "Light") == 0) {
		//		gameScene->addLight(loadLight(element));
		//	}
		//	else if (strcmp(element->Value(), "Camera") == 0) {
		//		gameScene->addCamera(loadCamera(element));
		//	}
		//	else if (strcmp(element->Value(), "Robot") == 0) {
		//		gameScene->addRobot(loadRobot(element));
		//	}
		//	else if (strcmp(element->Value(), "Physics") == 0) {
		//		gameScene->addPhysical(loadModel(element));
		//	}
		//}
		//m_scenes->push_back(std::pair<std::string, std::shared_ptr<Scene>>(sID,gameScene));
	}
	else if (str == "Splash") {
		std::shared_ptr<SplashScene> splashScene = std::make_unique<SplashScene>();
		for (XMLElement* element = node->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
		{
			if (strcmp(element->Value(), "ID") == 0) {
				if (readElementText(element, c)) {
					sID = std::string(c, strlen(c));		//ID
				}
			}
		}
		m_scenes->push_back(std::pair<std::string, std::shared_ptr<Scene>>(sID, splashScene));
	}
	else {

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

SceneLoader::SceneLoader(std::string sFilename, ResourceManager * res, std::vector<std::pair<std::string, std::shared_ptr<Scene>>>* scenes)
{
	m_res = res;		//Pointer to Resource manager
	m_scenes = scenes;	//Pointer to vector of scenes
	load(sFilename);
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
