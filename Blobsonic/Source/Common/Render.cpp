#include "stdafx.h"
#include "Render.h"
//Messages
#include "CameraMessages.h"
//Components
#include "Model.h"
#include "Transformable.h"
#include "Text.h"
#include "PointLight.h"
#include "SpriteRender.h"
//Messages
#include "RenderMessages.h"
#include "CameraMessages.h"

void System::Render::addEntity(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>>* entities)
{
	for (auto it = entities->begin(); it != entities->end(); ++it) {

		if ((*it)->getUID() == entity->getUID()) {
			return;	//Entity already stored
		}
	}
	entities->push_back(entity);	//Store entity
}

void System::Render::renderModel(std::shared_ptr<Entity> entity)
{
	//Get pointer to model component
	auto model = entity->get<Component::Model>();

	if (model->m_shader != NULL) {
		model->m_shader->use();	//Set shader

		passLightUniforms(model->m_shader);

		if (entity->has<Component::Transformable>()) {	//Apply transformations to model	//Pass model matrix as uniform
			Component::Transformable* transformable = entity->get<Component::Transformable>();

			model->m_shader->setUniform("mModel", transformable->getTransform());
			//transformable->setRotation(transformable->getRotation() + glm::vec3(0.0f, 0.0f, 0.01f));
		}
		else {
			//Pass default transform
			if (model->m_shader != NULL) model->m_shader->setUniform("mModel", glm::mat4(1.0f));
		}

		//Pass Camera uniforms
		if (m_ptrActiveCamera != NULL) {
			model->m_shader->setUniform("mView", m_ptrActiveCamera->getView());				//View matrix
			model->m_shader->setUniform("mProjection", m_ptrActiveCamera->getProjection());	//Projection matrix
			model->m_shader->setUniform("viewPos", m_ptrActiveCamera->getPosition());		//Camera/Eye position
		}
	}

	/*
	//Draw model meshes
	if (!model->m_meshes.empty()) {
	for (int i = 0; i < model->m_meshes.size(); i++) {
	std::shared_ptr<Texture> texture = NULL;
	std::shared_ptr<Mesh> mesh = model->m_meshes.at(i);			//Get pointer to mesh
	//Pass material uniforms to shader
	if (model->m_shader != NULL && i < model->m_materials.size()) {
	//Material reflectivity
	model->m_shader->setUniform("Ka", model->m_materials.at(i)->getAmbient());			//Ambient material reflection
	model->m_shader->setUniform("Kd", model->m_materials.at(i)->getDiffuse());			//Diffuse
	model->m_shader->setUniform("Ks", model->m_materials.at(i)->getSpecular());			//Specular
	model->m_shader->setUniform("shininess", model->m_materials.at(i)->getShininess());	//Shininess
	}
	//Check for texture
	if (!model->m_textures.empty() && i < model->m_textures.size()) {
	texture = model->m_textures.at(i);	//Get pointer to texture
	}
	gl::BindVertexArray(mesh->getVAO());		//Bind VAO
	//Has Texture
	if ((!mesh->getExpandedTexCoords().empty() && !texture == NULL)) {
	gl::BindTexture(gl::TEXTURE_2D, texture->object());							//Bind Texture
	gl::GenerateMipmap(gl::TEXTURE_2D);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR_MIPMAP_LINEAR);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::DrawArrays(gl::TRIANGLES, 0, mesh->getExpandedVertices().size());
	gl::BindTexture(gl::TEXTURE_2D, 0);										//Unbind Texture
	}
	//Has expanded normals
	else if (!mesh->getExpandedNormals().empty()) {
	gl::DrawArrays(gl::TRIANGLES, 0, mesh->getExpandedVertices().size());
	}
	//No Texture and No expaned normals
	else {
	gl::DrawElements(gl::TRIANGLES, mesh->getVertIndices().size(), gl::UNSIGNED_INT, 0);
	}
	gl::BindVertexArray(0);													//Unbind VAO
	}
	}

	*/
	m_fDeltaTime = 0.001;

	//Draw model Assimp meshes
	if (!model->m_aMeshes.empty()) {
		for (int i = 0; i < model->m_aMeshes.size(); i++) {

			std::shared_ptr<Texture> texture = NULL;
			std::shared_ptr<AssimpMesh> aMesh = model->m_aMeshes.at(i);	//Get pointer to amesh

																		//Pass material uniforms to shader
			if (model->m_shader != NULL && i < model->m_materials.size()) {
				//Material reflectivity
				model->m_shader->setUniform("Ka", model->m_materials.at(i)->getAmbient());			//Ambient material reflection
				model->m_shader->setUniform("Kd", model->m_materials.at(i)->getDiffuse());			//Diffuse
				model->m_shader->setUniform("Ks", model->m_materials.at(i)->getSpecular());			//Specular
				model->m_shader->setUniform("shininess", model->m_materials.at(i)->getShininess());	//Shininess

				if (aMesh->getHasBones()) {
					// Vector of bone transformation matrices. 
					std::vector<Matrix4f> Transforms;

					// Obtains newly transformed matrices from the bone hierarchy at the given time. 
					aMesh->BoneTransform(m_fDeltaTime, Transforms);

					// Passes each new bone transformation into the shader. 
					for (unsigned int j = 0; j < Transforms.size(); j++) {
						model->m_shader->setUniformIndex(j, Transforms[j]);

					}
				}
			}

			//Check for texture
			if (!model->m_textures.empty() && i < model->m_textures.size()) {
				texture = model->m_textures.at(i);	//Get pointer to texture
			}

			gl::BindVertexArray(aMesh->getVAO());		//Bind VAO

														//for (unsigned int k = 0; k < aMesh->m_Entries.size(); k++) {
														//	int index = 3;
														//	gl::DrawElementsBaseVertex(gl::TRIANGLES,
														//		aMesh->m_Entries[k].NumIndices,
														//		gl::UNSIGNED_INT,
														//		(void*)(sizeof(unsigned int) * aMesh->m_Entries[k].BaseIndex),
														//		aMesh->m_Entries[k].BaseVertex);
														//}
														//for (int k = 0; k < 1; k++) {
														//Has Texture
			if ((!aMesh->meshes[i].getPosition().empty() && !texture == NULL)) {
				gl::BindTexture(gl::TEXTURE_2D, texture->object());							//Bind Texture
				gl::GenerateMipmap(gl::TEXTURE_2D);
				gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR_MIPMAP_LINEAR);
				gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);

				//gl::DrawElementsBaseVertex(gl::TRIANGLES,
				//	aMesh->m_Entries[k].NumIndices,
				//	gl::UNSIGNED_INT,
				//	(void*)(sizeof(unsigned int) * aMesh->m_Entries[k].BaseIndex),
				//	aMesh->m_Entries[k].BaseVertex);
				//

				gl::DrawArrays(gl::TRIANGLES, 0, aMesh->meshes[i].getVertex().size());
				gl::BindTexture(gl::TEXTURE_2D, 0);										//Unbind Texture	
			}
			//Has expanded normals
			else if (!aMesh->meshes[i].getNormal().empty()) {
				gl::DrawArrays(gl::TRIANGLES, 0, aMesh->meshes[i].getVertex().size());
			}
			//No Texture and No expanded normals
			else {
				gl::DrawElements(gl::TRIANGLES, aMesh->meshes[i].getIndices().size(), gl::UNSIGNED_INT, 0);
			}
			//}
			gl::BindVertexArray(0);	//Unbind VAO
		}
	}

}

void System::Render::renderText(std::shared_ptr<Entity> entity)
{

}

void System::Render::renderSprite(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Texture> texture = NULL;
	auto spriteRender = entity->get <Component::SpriteRenderer>();
	auto t = entity->get <Component::Transformable>();

	spriteRender->getShader()->use();

	glm::mat4 projection = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);
	//glm::mat4 projection = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, -1.0f, 1.0f);
	//glm::mat4 projection = glm::perspective(45.0f, 1.33333f, 0.1f, 1000.0f);

	spriteRender->getShader()->setUniform("projection", projection);
	spriteRender->getShader()->setUniform("spriteColor", spriteRender->getColor());
	spriteRender->getShader()->setUniform("model", t->getTransform());

	gl::ActiveTexture(gl::TEXTURE0);

	//Check for texture
	texture = spriteRender->getTexture();

	// Bind VAO
	gl::BindVertexArray(spriteRender->getVAO());
	// Binds the texture
	gl::BindTexture(gl::TEXTURE_2D, texture->object());
	gl::DrawArrays(gl::TRIANGLES, 0, 6);
}

void System::Render::passLightUniforms(std::shared_ptr<GLSLProgram> shader)
{
	int iDirCount = 0;
	int iPointCount = 0;
	int iSpotCount = 0;

	Component::Transformable* t = NULL;

	//Pass directional lighting parameters to shader
	for (int i = 0; i < m_directionalLights.size(); i++) {	//Iterate through all lights
															//Get Light Component
		auto dirLight = m_directionalLights.at(i)->get<Component::DirectionalLight>();

		//Pass uniforms
		std::string sDirLight = "dirLights[" + std::to_string(i) + "].";
		shader->setUniform((sDirLight + "ambient").data(), dirLight->getAmbient());
		shader->setUniform((sDirLight + "diffuse").data(), dirLight->getDiffuse());
		shader->setUniform((sDirLight + "specular").data(), dirLight->getSpecular());
		shader->setUniform((sDirLight + "direction").data(), dirLight->getDirection());
	}

	//Pass point lighting parameters to shader
	for (int i = 0; i < m_pointLights.size(); i++) {	//Iterate through all lights
														//Get Light Component
		auto pointLight = m_pointLights.at(i)->get<Component::PointLight>();

		//Pass uniforms
		std::string sPointLight = "pointLights[" + std::to_string(i) + "].";
		shader->setUniform((sPointLight + "ambient").data(), pointLight->getAmbient());
		shader->setUniform((sPointLight + "diffuse").data(), pointLight->getDiffuse());
		shader->setUniform((sPointLight + "specular").data(), pointLight->getSpecular());
		shader->setUniform((sPointLight + "radius").data(), pointLight->getRadius());

		if (m_pointLights.at(i)->has<Component::Transformable>()) {
			t = m_pointLights.at(i)->get<Component::Transformable>();
			shader->setUniform((sPointLight + "position").data(), t->getPosition());
		}
	}

	//Pass  spot lighting parameters to shader
	for (int i = 0; i < m_spotlights.size(); i++) {	//Iterate through all lights
													//Get Light Component
		auto spotlight = m_spotlights.at(i)->get<Component::Spotlight>();

		//Pass uniforms
		std::string sSpotLight = "spotlights[" + std::to_string(i) + "].";
		shader->setUniform((sSpotLight + "ambient").data(), spotlight->getAmbient());
		shader->setUniform((sSpotLight + "diffuse").data(), spotlight->getDiffuse());
		shader->setUniform((sSpotLight + "specular").data(), spotlight->getSpecular());
		shader->setUniform((sSpotLight + "direction").data(), spotlight->getDirection());

		shader->setUniform((sSpotLight + "cutOff").data(), spotlight->getCutOff());
		shader->setUniform((sSpotLight + "outerCutOff").data(), spotlight->getOuterCutOff());
		shader->setUniform((sSpotLight + "constant").data(), spotlight->getConstant());
		shader->setUniform((sSpotLight + "linear").data(), spotlight->getLinear());
		shader->setUniform((sSpotLight + "quadratic").data(), spotlight->getQuadratic());

		if (m_spotlights.at(i)->has<Component::Transformable>()) {
			t = m_spotlights.at(i)->get<Component::Transformable>();
			shader->setUniform((sSpotLight + "position").data(), t->getPosition());
		}
	}
}

void System::Render::removeDestroyed(std::vector<std::shared_ptr<Entity>>* entities)
{
	for (int i = 0; i < entities->size(); i++) {
		if (entities->at(i)->isDestroyed()) {
			entities->erase(entities->begin() + i);
		}
	}
}

System::Render::Render()
{
	m_ptrActiveCamera = NULL;
}

void System::Render::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	//Iterate through all entities
	for (auto it = entities->begin(); it != entities->end(); ++it) {
		//Find and set active camera
		if ((*it)->has<Component::Camera>()) {
			auto cam = (*it)->get<Component::Camera>();
			//if (cam->m_bActive) {
			//Set camera pointer to this
			m_ptrActiveCamera = cam;
			//}
		}
		//Find Model Component
		if ((*it)->has<Component::Model>()) {
			renderModel((*it));	//Render Model
		}
		//Find Text Component
		if ((*it)->has<Component::Text>()) {
			renderText(*it);	//Render Text
		}
		if ((*it)->has<Component::SpriteRenderer>()) {
			renderSprite((*it));				//Sprite
		}
		//Find Light Components
		if ((*it)->has<Component::DirectionalLight>()) {	//Directional light
			addEntity((*it), &m_directionalLights);
		}
		if ((*it)->has<Component::PointLight>()) {
			addEntity((*it), &m_pointLights);				//Point light
		}
		if ((*it)->has<Component::Spotlight>()) {
			addEntity((*it), &m_spotlights);				//Spotlight
		}
		
	}
}

void System::Render::update(float dt)
{

	//Remove Destroyed Entities
	removeDestroyed(&m_directionalLights);
	removeDestroyed(&m_pointLights);
	removeDestroyed(&m_spotlights);
}

void System::Render::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	for (auto it = msgs->begin(); it != msgs->end(); ++it) {
		if ((*it)->sID == "SetActiveCamera") {
			//Get data key data from message
			auto data = static_cast<CameraMessage::SetActiveCamera*>((*it).get());

			m_ptrActiveCamera = data->entity->get<Component::Camera>();
		}
	}
}