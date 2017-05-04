/*
	OLD CODE 
	NOT BEING USED
*/

#include <stdafx.h>
#include "TestScene.h"

TestScene::TestScene(ResourceManager* res)
{

}

void TestScene::initScene()
{
	////Load Resources
	////Load Meshes
	//std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	//mesh->load("Source\\Resources\\models\\cube.obj");

	////Load Materials
	//std::shared_ptr<Material> material = std::make_shared<Material>();
	//material->setAmbient(0.5f, 0.5f, 0.5f);
	//material->setDiffuse(0.8f, 0.8f, 0.8f);
	//material->setSpecular(0.9f, 0.9f, 0.9f);
	//material->setShininess(0.1f);
	////Load Textures
	//Bitmap bmp = Bitmap::bitmapFromFile("Source\\Resources\\textures\\red.png");
	//bmp.flipVertically();
	////Create texture
	//std::shared_ptr<Texture> texture = std::make_shared<Texture>(bmp);

	////Load Shaders
	//std::shared_ptr<GLSLProgram> shader = std::make_shared<GLSLProgram>();
	//try {
	//	shader->compileShader("Source\\Resources\\shader\\phong.vert");
	//	shader->compileShader("Source\\Resources\\shader\\phong.frag");
	//	shader->link();
	//	shader->validate();
	//	shader->use();
	//}
	//catch (GLSLProgramException & e) {
	//	std::cerr << e.what() << std::endl;
	//	exit(EXIT_FAILURE);
	//}

	////Store resources into manager
	//m_ptrResources->addMesh("cube", mesh);
	//m_ptrResources->addMaterial("default", material);
	//m_ptrResources->addShader("phong", shader);
	//m_ptrResources->addTexture("red", texture);

	////m_entities.addEntity(m_factory->createPlayer(glm::vec3(0.0f, 0.0f, 0.0f)));
	////m_entities.addEntity(m_factory->createCamera(glm::vec3(0.0f, 5.0f, 100.0f)));
}

void TestScene::update(float dt)
{

}