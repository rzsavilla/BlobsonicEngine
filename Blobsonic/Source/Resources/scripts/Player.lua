-- Used to create the player entity
-- Components required to create player
playerAtt = {
	Transformable = {
		Position = {x = 0, y = 2000, z = 0 },
		Rotation = {x = 0, y = 0, z = 0},
		Scale = {x = 1000, y = 1000, z = 1000},
		Origin = {x = 0, y = 0, z = 0}
	},
	Model = {
		Mesh = "cube_mesh",
		Material = "default_material",
		Shader = "phong_shader",
		Texture = "floor_texture"
	},
	Physical = {
		Mass = 1.0,
		INVMass = 1.0,
		Restitution = 0.1
	},
	AABB = {
		Dimensions = {x = 1,1,1}
	}
}

boxAtt = {
	Transformable = {
		Position = {x = 0, y = -1000, z = 0 },
		Rotation = {x = 0, y = 0, z = 0},
		Scale = {x = 10000, y = 100, z = 10000},
		Origin = {x = 0, y = 0, z = 0}
	},
	Model = {
		Mesh = "cube_mesh",
		Material = "default_material",
		Shader = "phong_shader",
		Texture = "white_texture"
	},
	Physical = {
		Mass = 0.0,
		INVMass = 0.0,
		Restitution = 0.0
	},
	AABB = {
		Dimensions = {x = 1,1,1}
	}
}

--Create Entity of player
player = Entity.new()
player:setComponents(playerAtt)
player:tSetPosition(0,10000,0)

--Create Solid entity
box1 = Entity.new()
box1:setComponents(boxAtt)
