/*
*	@struct Model
*	@brief Simple component that holds data required to render model
*	@author Rozen Savilla
*/


#pragma once

#include "stdafx.h"
#include "Component.h"
#include "Mesh.h"
#include "Material.h"

#include "ResourceManager.h"
#include "sol.hpp"

namespace Component {
	struct Model : public Component {
		Model() {}

		Model(sol::table t) {
			//Read variables from lua table
			for (auto it = t.begin(); it != t.end(); ++it) {
				auto key = (*it).first;	//Get element key
				std::string s = key.as<std::string>();		//Get element key
				if (key.get_type() == sol::type::string) {
					//Set variables

					if ((*it).second.get_type() == sol::type::string) {
						std::string sValue = (*it).second.as<std::string>();
						if (s == "Name")
							this->setName(sValue);
						else if (s == "Mesh")
							this->addMesh(ResourceManager::getInstance()->getAssimpMesh(sValue));
						else if (s == "Texture")
							this->addTexture(ResourceManager::getInstance()->getTexture(sValue));
						else if (s == "Material")
							this->addMaterial(ResourceManager::getInstance()->getMaterial(sValue));
						else if (s == "Shader")
							this->setShader(ResourceManager::getInstance()->getShader(sValue));
					}
				}
			}
		}

		std::vector<std::shared_ptr<Mesh>> m_meshes;
		std::vector<std::shared_ptr<AssimpMesh>> m_aMeshes;
		std::vector<std::shared_ptr<Texture>> m_textures;
		std::vector<std::shared_ptr<Material>> m_materials;
		std::shared_ptr<GLSLProgram> m_shader;

		void addMesh(std::shared_ptr<AssimpMesh> mesh) {
			m_aMeshes.push_back(mesh);
		}
		void addTexture(std::shared_ptr<Texture> texture) {
			m_textures.push_back(texture);
		}
		void addMaterial(std::shared_ptr<Material> material) {
			m_materials.push_back(material);
		}
		void setShader(std::shared_ptr<GLSLProgram> shader) {
			m_shader = shader;
		}
	};
}