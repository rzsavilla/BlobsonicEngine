#include <stdafx.h>
#include "GameScene.h"
#include "SceneMessages.h"

/*

void GameScene::updateCamera(std::shared_ptr<GLSLProgram> shader, QuatCamera cam)
{
	//Pass camera uniforms to shader
	shader->setUniform("mView", cam.view());				//View matrix
	shader->setUniform("mProjection", cam.projection());	//Projection matrix
	shader->setUniform("viewPos", cam.position());			//Camera position
}

void GameScene::updateLights(std::shared_ptr<GLSLProgram> shader)
{
	//Loop through vector of lights to pass light uniforms into shader
	for (int i = 0; i < m_vLights.size(); i++) {
		Light light = m_vLights.at(i).second;

		std::string sLA = "pLight[" + std::to_string(i) + std::string("].La");
		std::string sLD = "pLight[" + std::to_string(i) + std::string("].Ld");
		std::string sLS = "pLight[" + std::to_string(i) + std::string("].Ls");
		std::string sPosition = "pLight[" + std::to_string(i) + std::string("].position");
		std::string sRadius = "pLight[" + std::to_string(i) + std::string("].radius");

		shader->setUniform(sPosition.data(), light.getPosition());
		shader->setUniform(sRadius.data(), light.getRadius());

		//Pass light intesity
		shader->setUniform(sLA.data(), light.getAmbient());	//Ambient light
		shader->setUniform(sLD.data(), light.getDiffuse());	//Diffuse light
		shader->setUniform(sLS.data(), light.getSpecular());	//Specular light
	}
}

void GameScene::nextCamera()
{
	if (m_uiCameraActive < m_vCamera.size()-1) m_uiCameraActive++;
}

void GameScene::prevCamera()
{
	if (m_uiCameraActive > 0 && m_iKey_Q > 0) m_uiCameraActive--;
}

bool GameScene::collision(MyRobot * robot, Model * model)
{
	// c = sqrt(a^2 + b^2)
	glm::vec3 a = robot->getPosition();
	glm::vec3 b = model->getPosition();

	float distance = sqrt(pow(b.x - a.x, 2) + pow(b.z - a.z, 2));

	//std::cout << distance << "\n";
	if (distance <= 7.0f) {
		return true;				//Collision has occured
	}
	return false;
}

GameScene::GameScene()
{

}

void GameScene::addModel(std::pair<std::string, Model> model)
{
	m_vModels.push_back(model);
}

void GameScene::addLight(std::pair<std::string, Light> light)
{
	m_vLights.push_back(light);
}

void GameScene::addCamera(std::pair<std::string, QuatCamera> camera)
{
	m_vCamera.push_back(camera);
}

void GameScene::addRobot(std::pair<std::string, MyRobot> robot)
{
	m_vRobots.push_back(robot);
}

void GameScene::addPhysical(std::pair<std::string, Model> model)
{
	if (model.first == "Sphere")
	{
		m_vSphere.push_back(model);
	}
	if (model.first == "OBB")
	{
		m_vOBB.push_back(model);
	}
	if (model.first == "AABB")
	{
		m_vAABB.push_back(model);
	}
	
	
}

void GameScene::addButton(std::pair<std::string, Button> button)
{
	m_vButton.push_back(button);
}

void GameScene::initScene()
{
	m_iKey_W = 0, m_iKey_S = 0, m_iKey_A = 0, m_iKey_D = 0;
	m_dMouseX = 0.0, m_dMouseY = 0.0;
	m_dPrevMouseX = 0.0, m_dPrevMouseY = 0.0;
	m_uiCameraActive = 0;

	// Button initalizer
	addButton(std::pair<std::string, Button>("MyButton", m_ptrResources->getMesh("cube_mesh")));
	m_vButton.begin()->second.setShader(m_ptrResources->getShader("button_shader"));
	m_vButton.begin()->second.setMaterial(m_ptrResources->getMaterial("default_material"));

	//Create Text
	m_PickupCounterText = std::make_shared<Text>("", m_ptrCharacters, 1.0f, 10.0f, glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
	m_PickupCounterText->setShader(m_ptrResources->getShader("text_shader"));

	m_iTotalPickups = 0;
	m_iCollected = 0;
	//Count the number of pickups
	for (int i = 0; i < m_vModels.size(); i++) {
		if (m_vModels.at(i).first == "pickup_model") m_iTotalPickups++;
	}
}

void GameScene::handleInput(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//Key Press
	m_iKey_W = glfwGetKey(window, GLFW_KEY_W);
	m_iKey_S = glfwGetKey(window, GLFW_KEY_S);
	m_iKey_A = glfwGetKey(window, GLFW_KEY_A);
	m_iKey_D = glfwGetKey(window, GLFW_KEY_D);

	m_iKey_Up = glfwGetKey(window, GLFW_KEY_UP);
	m_iKey_Down = glfwGetKey(window, GLFW_KEY_DOWN);
	m_iKey_Left = glfwGetKey(window, GLFW_KEY_LEFT);
	m_iKey_Right = glfwGetKey(window, GLFW_KEY_RIGHT);

	m_iKey_Q = glfwGetKey(window, GLFW_KEY_Q);
	m_iKey_E = glfwGetKey(window, GLFW_KEY_E);
	m_iKey_R = glfwGetKey(window, GLFW_KEY_R);

	m_iKey_Escape = glfwGetKey(window, GLFW_KEY_ESCAPE);
	m_iKey_Space = glfwGetKey(window, GLFW_KEY_ESCAPE);
	

	//Mouse movement
	glfwGetCursorPos(window, &m_dMouseX, &m_dMouseY);
	m_dDeltaMouseX = m_dPrevMouseX - m_dMouseX;
	m_dDeltaMouseY = m_dPrevMouseY - m_dMouseY;
	m_dPrevMouseX = m_dMouseX;
	m_dPrevMouseY = m_dMouseY;
}

void GameScene::update(float dt)
{


	//move box
	if (m_iKey_W) m_vOBB[0].second.movementForTesting(0.0f,1.0f,0.0f);
	else if(m_iKey_S)m_vOBB[0].second.movementForTesting(0.0f, -1.0f, 0.0f);
	if (m_iKey_A) m_vOBB[0].second.movementForTesting(-1.0f, 0.0f, 0.0f);
	else if (m_iKey_D)m_vOBB[0].second.movementForTesting(1.0f, 0.0f, 0.0f);

	//move Sphere
	if (m_iKey_Up) m_vSphere[0].second.movementForTesting(0.0f, 1.0f, 0.0f);
	else if (m_iKey_Down)m_vSphere[0].second.movementForTesting(0.0f, -1.0f, 0.0f);
	if (m_iKey_Left) m_vSphere[0].second.movementForTesting(-1.0f, 0.0f, 0.0f);
	else if (m_iKey_Right)m_vSphere[0].second.movementForTesting(1.0f, 0.0f, 0.0f);

	////Robot movement
	//if (m_iKey_W) m_vRobots.begin()->second.moveForward();
	//else if (m_iKey_S) m_vRobots.begin()->second.moveBackward();
	//if (m_iKey_A) m_vRobots.begin()->second.turnLeft();
	//else if (m_iKey_D) m_vRobots.begin()->second.turnRight();
	////std::cout << m_vRobots.begin()->second.getPosition().x << " " << m_vRobots.begin()->second.getPosition().z << "\n";
	////Switch Camera
	//if (m_camSwitchDelay.getElapsed() > 0.2f) {
	//	if (m_iKey_Q) {
	//		prevCamera();
	//		m_camSwitchDelay.reset();
	//	}
	//	else if (m_iKey_E) { 
	//		nextCamera(); 
	//		m_camSwitchDelay.reset();
	//	}
	//}

	//Reload Scene
	if (m_iKey_R) m_ptrMessages->push_back(std::make_shared<SceneMessage::Reload>());

	//Close Game
	if (m_iKey_Escape) m_ptrMessages->push_back(std::make_shared<SceneMessage::Exit>());


	//Rotate camera based on mouse movement
	if (!m_vCamera.empty()) {
		float fSpeed = m_vCamera.at(m_uiCameraActive).second.getRotateSpeed();
		m_vCamera.at(m_uiCameraActive).second.rotate(
			(-m_dDeltaMouseX * dt),
			(-m_dDeltaMouseY * dt)
		);
	}

	

	std::vector<int> viDelete;	//Stores model index for models to be deleted
	//Update models
	for (int i = 0; i < m_vModels.size(); i++) {
		//Update pickup models
		if (m_vModels.at(i).first == "pickup_model") {
			m_vModels.at(i).second.rotate(100.0f * dt, xAxis);
			m_vModels.at(i).second.rotate(100.0f * dt, yAxis);

			//Check for collision with robot
			if (collision(&m_vRobots.begin()->second, &m_vModels.at(i).second)) {
				m_iCollected++;
				viDelete.push_back(i);	//Push model index, ready to be deleted
			}
		}
	}

	//Delete models
	for (int i = 0; i < viDelete.size(); i++) {
		m_vModels.erase(m_vModels.begin() + viDelete[i]);
	}

	for (auto phycicalsIt = m_vOBB.begin(); phycicalsIt != m_vOBB.end(); ++phycicalsIt) {
		(*phycicalsIt).second.update(dt);
	}
	for (auto phycicalsIt = m_vAABB.begin(); phycicalsIt != m_vAABB.end(); ++phycicalsIt) {
		(*phycicalsIt).second.update(dt);
	}
	for (auto phycicalsIt = m_vSphere.begin(); phycicalsIt != m_vSphere.end(); ++phycicalsIt) {
		(*phycicalsIt).second.update(dt);
	}

	//Update Robot
	for (auto robotIt = m_vRobots.begin(); robotIt != m_vRobots.end(); ++robotIt) {
		(*robotIt).second.update(dt);
	}

	//Update Physicals
	checkForCollision(dt);

	//Update Text
	m_PickupCounterText->setString("Collected:" + std::to_string(m_iCollected) + "/" + std::to_string(m_iTotalPickups));
}

void GameScene::checkForCollision(float dt)
{
	m_vSphere[0].second.CollideWithOBB(&m_vOBB[0].second);

}

void GameScene::draw()
{
	gl::Enable(gl::DEPTH_TEST);
	m_PickupCounterText->draw();
	//////////////////RENDER//////////
	for (auto modelIt = m_vModels.begin(); modelIt != m_vModels.end(); ++modelIt) {
		(*modelIt).second.getShader()->use();
		//Pass camera uniforms to shader (For active camera)
		updateCamera((*modelIt).second.getShader(), m_vCamera.at(m_uiCameraActive).second);
		//Pass light uniforms to shaders
		updateLights((*modelIt).second.getShader());

		//Draw model
		(*modelIt).second.draw();
	}

	for (auto robotIt = m_vRobots.begin(); robotIt != m_vRobots.end(); ++robotIt) {
		(*robotIt).second.getShader()->use();
		//Pass camera uniforms to shader (For active camera)
		updateCamera((*robotIt).second.getShader(), m_vCamera.at(m_uiCameraActive).second);
		//Pass light uniforms to shaders
		updateLights((*robotIt).second.getShader());
		//Draw model
		(*robotIt).second.draw();
	}

	for(auto physicalsIt = m_vOBB.begin(); physicalsIt != m_vOBB.end(); ++physicalsIt)
	{
		//set the shader for the physics object
		(*physicalsIt).second.m_RenderModel.getShader()->use();
		//pass data to the camera
		updateCamera((*physicalsIt).second.m_RenderModel.getShader(), m_vCamera.at(m_uiCameraActive).second);
		//update the lights with unifroms
		updateLights((*physicalsIt).second.m_RenderModel.getShader());
		//Draw model
		(*physicalsIt).second.m_RenderModel.draw();
	}
	for (auto physicalsIt = m_vAABB.begin(); physicalsIt != m_vAABB.end(); ++physicalsIt)
	{
		//set the shader for the physics object
		(*physicalsIt).second.m_RenderModel.getShader()->use();
		//pass data to the camera
		updateCamera((*physicalsIt).second.m_RenderModel.getShader(), m_vCamera.at(m_uiCameraActive).second);
		//update the lights with unifroms
		updateLights((*physicalsIt).second.m_RenderModel.getShader());
		//Draw model
		(*physicalsIt).second.m_RenderModel.draw();
	}

	for (auto physicalsIt = m_vSphere.begin(); physicalsIt != m_vSphere.end(); ++physicalsIt)
	{
		//set the shader for the physics object
		(*physicalsIt).second.m_RenderModel.getShader()->use();
		//pass data to the camera
		updateCamera((*physicalsIt).second.m_RenderModel.getShader(), m_vCamera.at(m_uiCameraActive).second);
		//update the lights with unifroms
		updateLights((*physicalsIt).second.m_RenderModel.getShader());
		//Draw model
		(*physicalsIt).second.m_RenderModel.draw();
	}

	// Button drawing
	
	//for (auto buttonIt = m_vButton.begin(); buttonIt != m_vButton.end(); ++buttonIt) {
	//	(*buttonIt).second.getShader()->use();
	//	//Pass camera uniforms to shader (For active camera)
	//	updateCamera((*buttonIt).second.getShader(), m_vCamera.at(m_uiCameraActive).second);
	//	//Pass light uniforms to shaders
	//	updateLights((*buttonIt).second.getShader());
	//	//Draw model
	//	(*buttonIt).second.draw();
	//	
	//}
	
	gl::Disable(gl::DEPTH_TEST);
}

*/