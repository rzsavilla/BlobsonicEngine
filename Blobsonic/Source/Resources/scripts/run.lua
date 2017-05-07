-- This is where the game logic is updated and is run every game update

-- For Debugging/Scene testing
if isKeyDown("p") == true then
	reloadScene()
elseif isKeyDown("esc") == true then
	changeScene("Main_Menu_Scene.xml")
end

if getActiveScene() == "WorldTest.xml" then
	hideCursor(true)
	-- Player Controls
	if isKeyDown("w") == true then
		player:pMove(0,0,1,playerSpeed)		-- Move Forwards
	elseif isKeyDown("s") == true then
		player:pMove(0,0,-1,playerSpeed)		--Move Backwards
	end
	
	--Jump
	if isKeyDown("space") == true then
		if jumpTimer:getElapsed() > playerJumpDelay then
			player:pMove(0,1,0,playerJumpForce)
			jumpTimer:reset()
		end
	end

	--Collect Pickup
	if player:pHasCollidedByName("pickup1") then
		pickup1:destroy()
		iCollected = iCollected + 1
	end
else
	hideCursor(false)
end
