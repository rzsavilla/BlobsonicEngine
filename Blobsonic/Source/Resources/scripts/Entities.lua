-- Used to create the player entity
-- Components required to create player

planeAtt= {
	Transformable = {
		Position = {x = 0, y = 0, z = 0 },
		Rotation = {x = 0, y = 0, z = 0},
		Scale = {x = 10000, y = 1, z = 10000},
		Origin = {x = 0, y = 0, z = 0}
	},
	Model = {
		Mesh = "plane_mesh",
		Material = "default_material",
		Shader = "phong_shader",
		Texture = "floor_texture"
	}
}

boxAtt = {
	Transformable = {
		Position = {x = 2000, y = 4000, z = 0 },
		Rotation = {x = 0, y = 0, z = 0},
		Scale = {x = 1000, y = 1000, z = 1000},
		Origin = {x = 0, y = 0, z = 0}
	},
	Model = {
		Mesh = "cube_mesh",
		Material = "default_material",
		Shader = "phong_shader",
		Texture = "white_texture"
	},
	Physical = {
		Mass = 1.0,
		INVMass = 1.0,
		Restitution = 0.1
	}
}

--Create Entity of player
plane = Entity.new()
plane:setComponents(planeAtt)

boxes = {}	-- Array to store box entities
