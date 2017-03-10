#include <stdafx.h>
//Components
#include "Render.h"
#include "Model.h"
#include "Transformable.h"
//Messages
#include "CameraMessages.h"

#include <stdafx.h>
//Components
#include "Render.h"
#include "ModelComponent.h"
#include "TransformableComponent.h"
//Messages
#include "RenderMessages.h"
#include "CameraMessages.h"

void System::Render::renderModel(std::shared_ptr<Entity> entity)
{
	//Get pointer to model component
	auto model = entity->get<Component::Model>();

	if (model->m_shader != NULL) {
		model->m_shader->use();	//Set shader
								//Apply transformations to model	//Pass model matrix as uniform
		if (entity->has<Component::Transformable>()) {
			Component::Transformable* transformable = entity->get<Component::Transformable>();
			model->m_shader->setUniform("mModel", transformable->m_transform);
		}
		else {
			//Pass default transform
			if (model->m_shader != NULL) model->m_shader->setUniform("mModel", glm::mat4(1.0f));
		}

		//Pass Camera uniforms
		if (m_ptrActiveCamera != NULL) {
			model->m_shader->setUniform("mView", m_ptrActiveCamera->m_view);				//View matrix
			model->m_shader->setUniform("mProjection", m_ptrActiveCamera->m_projection);	//Projection matrix
			model->m_shader->setUniform("viewPos", m_ptrActiveCamera->m_vPosition);
		}
	}

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
}

System::Render::Render()
{

}

void System::Render::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	//Iterate through all entities
	for (auto it = entities->begin(); it != entities->end(); ++it) {
		//Find and set active camera
		if ((*it)->has<Component::Camera>()) {
			auto cam = (*it)->get<Component::Camera>();
			if (cam->m_bActive) {
				//Set camera pointer to this
				m_ptrActiveCamera = cam;
			}
		}
		//Find Model Component
		else  if ((*it)->has<Component::Model>()) {
			renderModel((*it));	//Render Model
		}
	}
}

void System::Render::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	for (auto it = msgs->begin(); it != msgs->end(); ++it) {
		if ((*it)->sID == "SetActiveCamera") {
			//Get data key data from message
			auto data = static_cast<CameraMessage::SetActiveCamera*>((*it).get());

			m_ptrActiveCamera = data->ptrCam;
		}
	}
}