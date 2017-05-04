-- This is where the game logic is updated and is run every game update


require "Source/Resources/scripts/SceneManagement"	-- Debugging purposes fast scene reload

hideCursor(true)


if isKeyDown("p") == true then
	reloadScene()
elseif isKeyDown("o") == true then
	player:destroy()
end

player:tSetScale(100,100,100)


fSpeed = 100

if isKeyDown("up") == true then
	player:pSetVelocity(0,fSpeed,0)
elseif isKeyDown("down") == true then
	player:pSetVelocity(0,-fSpeed,0)
elseif isKeyDown("left") == true then
	player:pSetVelocity(-fSpeed,0,0)
elseif isKeyDown("right") == true then
	player:pSetVelocity(fSpeed,0,0)
end

if isKeyDown("left") == true then

end
