local player = {
	Name = "Player",
	Transformable = {
		Position = { x = 0.0, y = 0.0, z = 0.0},
		Rotation = { x = 0.0, y = 0.0, z = 0.0},
		Scale = { x = 1.0, y = 1.0, z = 1.0},
		Origin = { x = 0.0, y = 0.0, z = 0.0},
	},
	Model = {
		Name = "PlayerModel",
		Mesh = "cube_mesh",
		Texture = "red_texture",
		Shader = "phong_shader"
	}
}
return player