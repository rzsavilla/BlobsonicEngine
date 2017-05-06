-- This is where the game logic is updated and is run every game update


fSpeed = 500

if isKeyDown("p") == true then
		reloadScene()
end

if getActiveScene() == "WorldTest.xml" then
	if isKeyDown("w") == true then
		player:pSetVelocity(0,0,-fSpeed)
	elseif isKeyDown("s") == true then
		player:pSetVelocity(0,0,fSpeed)
	elseif isKeyDown("a") == true then
		player:pSetVelocity(-fSpeed,0,0)
	elseif isKeyDown("d") == true then
		player:pSetVelocity(fSpeed,0,0)
	elseif isKeyDown("space") == true then
		player:pSetVelocity(0,fSpeed,0)
	end

	if player:tGetPosY() < 0 then
		player:tSetPosition(player:tGetPosX(),0,player:tGetPosZ())
	end

	if player:pHasCollidedByName(floorHandle:getName()) == true then

	end

	if player:pHasCollidedByName("pickup") == true then
		reloadScene()
		player:log()
	end

end
