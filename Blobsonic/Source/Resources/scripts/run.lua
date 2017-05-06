-- This is where the game logic is updated and is run every game update


fSpeed = 1000

if getActiveScene() == "WorldTest.xml" then

	if isKeyDown("p") == true then
		reloadScene()
	end

	if isKeyDown("up") == true then
		--player:tSetPosition(0,1000,0)
		--player:destroy()
	elseif isKeyDown("down") == true then
		--player:pSetVelocity(0,-fSpeed,0)
	elseif isKeyDown("left") == true then
		--player:pSetVelocity(-fSpeed,0,0)
	elseif isKeyDown("right") == true then
		--player:pSetVelocity(fSpeed,0,0)
	end


	if player:pHasCollidedByName(floorHandle:getName()) == true then
		player:tSetPosition(0,1000,0)
	end

end
