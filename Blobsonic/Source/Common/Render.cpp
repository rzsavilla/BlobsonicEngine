#include <stdafx.h>
#include "Render.h"
//Messages
#include "CameraMessages.h"
#include <stdafx.h>
//Components
#include "Model.h"
#include "Transformable.h"
#include "Text.h"
#include "SpriteRender.h"
//#include "GUIButton.h"
//Messages
#include "RenderMessages.h"
#include "CameraMessages.h"

void System::Render::renderModel(std::shared_ptr<Entity> entity)
{
	//Get pointer to model component
	auto model = entity->get<Component::Model>();
	if (model->m_shader != NULL) {
		model->m_shader->use();	//Set shader

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

			// Sets the camera to orthographic and then back to perspective after the value has been passed to the shader
			m_ptrActiveCamera->setPerspective(false);
			model->m_shader->setUniform("mViewO", m_ptrActiveCamera->getProjection());		
			m_ptrActiveCamera->setPerspective(true);
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
				
				//model->m_shader->setUniform("button", );	//Shininess
			}

			//Check for texture
			if (!model->m_textures.empty() && i < model->m_textures.size()) {
				texture = model->m_textures.at(i);	//Get pointer to texture
			}

			gl::BindVertexArray(aMesh->getVAO());		//Bind VAO

			//Has Texture
			if ((!aMesh->meshes[i].getPosition().empty() && !texture == NULL)) {
				gl::BindTexture(gl::TEXTURE_2D, texture->object());							//Bind Texture
				gl::GenerateMipmap(gl::TEXTURE_2D);
				gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR_MIPMAP_LINEAR);
				gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
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
			gl::BindVertexArray(0);													//Unbind VAO
		}
	}
}

void System::Render::renderText(std::shared_ptr<Entity> entity)
{

}

void System::Render::renderSprite(std::shared_ptr<Entity> entity)
{
	//GLSLProgram &shader, Texture &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
	//auto modelS = entity->get<Component::Model>();
	// Prepare transformations
	auto spriteRender = entity->get <Component::SpriteRenderer>();
	
	spriteRender->getShader()->use();/*
	spriteRender->getTexture();
	spriteRender->getColor();
	spriteRender->getPosition();
	spriteRender->getRotate();
	spriteRender->getSize();
	spriteRender->getVertices();
	spriteRender->getVAO();
	*/
	spriteRender->setPosition(glm::vec2(200, 200));
	spriteRender->setSize(glm::vec2(300, 400));
	spriteRender->setRotate(45.0f);
	spriteRender->setColor(glm::vec3(0.0f, 1.0f, 0.0f));

	//spriteRender->

	//spriteRender->getShader().get;

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(spriteRender->getPosition(), 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * spriteRender->getSize().x, 0.5f * spriteRender->getSize().y, 0.0f));
	model = glm::rotate(model, spriteRender->getRotate(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * spriteRender->getSize().x, -0.5f * spriteRender->getSize().y, 0.0f));

	model = glm::scale(model, glm::vec3(spriteRender->getSize(), 1.0f));

	glm::mat4 projection = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, -1.0f, 1.0f);
	//glm::mat4 projection = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);
	//glm::mat4 projection = glm::perspective(45.0f, 1.33333f, 0.1f, 1000.0f);

	
	spriteRender->getShader()->setUniform("projection", projection);
	spriteRender->getShader()->setUniform("spriteColor", spriteRender->getColor());
	spriteRender->getShader()->setUniform("model", model);

	// Set active texture
	// ...

	gl::BindVertexArray(spriteRender->getVAO());
	gl::DrawArrays(gl::TRIANGLES, 0, 6);
	gl::BindVertexArray(0);

	
}

System::Render::Render()
{
	m_ptrActiveCamera = NULL;
}

void System::Render::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	//gl::Disable(gl::DEPTH_TEST);
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
		//Find Sprite Component
		if ((*it)->has<Component::SpriteRenderer>()) {
			renderSprite(*it);	//Render Sprite
		}
	}
}

void System::Render::update(float dt)
{

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