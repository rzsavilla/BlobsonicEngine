-- Used to create the player entity
-- Components required to create player
playerAtt = {
	Transformable = {
		Position = {x = 0, y = 0, z = 0 },
		Rotation = {x = 0, y = 0, z = 0},
		Scale = {x = 10, y = 10, z = 10},
		Origin = {x = 0, y = 0, z = 0}
	},
	Model = {
		Mesh = "deer_mesh",
		Material = "default_material",
		Shader = "phong_shader",
		Texture = "floor_texture"
	},
	Physical = {
		Mass = 1.0,
		INVMass = 1.0,
		Restitution = 0.1
	}
}

--Create Entity of player
player = Entity.new()
player:setComponents(playerAtt)
