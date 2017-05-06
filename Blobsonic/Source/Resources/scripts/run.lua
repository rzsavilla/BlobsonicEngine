-- This is where the game logic is updated and is run every game update

fSpeed = 5

if isKeyDown("p") == true then
		reloadScene()
end

if getActiveScene() == "WorldTest.xml" then
	if isKeyDown("w") == true then
		player:pApplyImpulse(0,0,-1,fSpeed)
	elseif isKeyDown("s") == true then
		player:pApplyImpulse(0,0,1,fSpeed)
	elseif isKeyDown("a") == true then
		player:pApplyImpulse(-1,0,0,fSpeed)
	elseif isKeyDown("d") == true then
		player:pApplyImpulse(1,0,-1,fSpeed)
	elseif isKeyDown("space") == true then
		player:pApplyImpulse(0,1,0,fSpeed)
fSpeed = 1000
if isKeyDown("p") == true then
		reloadScene()
	end
	
if getActiveScene() == "WorldTest.xml" then

	if player:tGetPosY() < 0 then
		--player:tSetPosition(player:tGetPosX(),0,player:tGetPosZ())
	
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

	if player:pHasCollidedByName("pickup") == true then
		--reloadScene()
	if player:pHasCollidedByName(floorHandle:getName()) == true then
		player:tSetPosition(0,1000,0)
	end

end
