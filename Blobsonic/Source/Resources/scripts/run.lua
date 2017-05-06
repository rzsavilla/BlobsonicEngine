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
	end
end
