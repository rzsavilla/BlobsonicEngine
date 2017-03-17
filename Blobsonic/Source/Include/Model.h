#pragma once

#include <stdafx.h>
#include "Component.h"
#include "Mesh.h"
#include "Material.h"

namespace Component {
	struct Model : public Component {
		Model() {}
		std::vector<std::shared_ptr<Mesh>> m_meshes;
		std::vector<std::shared_ptr<Texture>> m_textures;
		std::vector<std::shared_ptr<Material>> m_materials;
		std::shared_ptr<GLSLProgram> m_shader;
	};
}