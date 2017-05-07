-- This is where the game logic is updated and is run every game update

fSpeed = 50

if isKeyDown("p") == true then
		reloadScene()
end

if getActiveScene() == "WorldTest.xml" then
	if isKeyDown("w") == true then
		player:pMove(0,0,1,fSpeed)
	elseif isKeyDown("s") == true then
		player:pMove(0,0,-1,fSpeed)
	elseif isKeyDown("a") == true then
		player:pMove(1,0,0,fSpeed)
	elseif isKeyDown("d") == true then
		player:pMove(-1,0,0,fSpeed)
	end
	if isKeyDown("space") == true then
		if jumpTimer:getElapsed() > 0.6 then
			player:pMove(0,1,0,fSpeed * 25)
			jumpTimer:reset()
		end
	end

	if player:tGetPosY() < 0.0 then
		--player:tSetPosition(player:tGetPosX(),0,player:tGetPosZ())
	end
	
	--Collect pickup
	if player:pHasCollidedByName("pickup1") then
		--pickup1:destroy()
	end
	
end
