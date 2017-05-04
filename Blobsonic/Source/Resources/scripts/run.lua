-- This is where the game logic is updated and is run every game update


require "Source/Resources/scripts/SceneManagement"	-- Debugging purposes fast scene reload

hideCursor(true)


if isKeyDown("p") == true then
	reloadScene()
elseif isKeyDown("o") == true then
	forceReloadScene()
end

player:tSetScale(100,100,100)
