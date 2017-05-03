-- This is where the game logic is updated and is run every game update


require "Source/Resources/scripts/SceneManagement"	-- Debugging purposes fast scene reload

hideCursor(true)


player:setPosition(0,0,0)

if isKeyDown("p") == true then
	reloadScene()
elseif isKeyDown("o") == true then
	forceReloadScene()
end

player:setPosition(0,25,0)
