-- Used to create the player entity handle
--[[
Creating entities within lua is currently disabled
Must handle entities already created in the scene by XML
playerAtt = {
	Name = "Player",
	Transformable = {
		Position = {x = 0, y = 5000, z = 0 },
		Rotation = {x = 0, y = 0, z = 0},
		Scale = {x = 1000, y = 1000, z = 1000},
		Origin = {x = 0, y = 0, z = 0}
	},
	Model = {
		Mesh = "cube_mesh",
		Material = "default_material",
		Shader = "phong_shader",
		Texture = "red_texture"
	},
	Physical = {
		Mass = 1.0,
		INVMass = 1.0,
		Restitution = 0.1
	},
	AABB = {
		Dimensions = {x = 1, y = 1, z = 1}
	},
	Sphere = {
		Radius = 1.0
	}
}
--]]

player = Entity.new()
player:handleEntity("deer")
