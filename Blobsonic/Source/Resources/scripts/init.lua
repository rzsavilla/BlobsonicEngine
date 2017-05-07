--[[
	This script is responsible for starting the game,
	it determines the initial scene and window/OpenGL properties
--]]

-- Set the loading scene/transition between scenes.
-- If a loading scene is not set then there will just be a black screen


setLoadingScene("Loading.xml")
--changeScene("Main_Menu_Scene.xml")	-- Change to this scene
--changeScene("Level1.xml")
changeScene("Main_Menu_Scene.xml")
