-- This is where the game logic is updated and is run every game update

local player = Entity.new()
player:handleEntity("deer")



fSpeed = 1000


--[[


if isKeyDown("up") == true then
	player:pSetVelocity(0,fSpeed,0)
elseif isKeyDown("down") == true then
	player:pSetVelocity(0,-fSpeed,0)
elseif isKeyDown("left") == true then
	player:pSetVelocity(-fSpeed,0,0)
elseif isKeyDown("right") == true then
	player:pSetVelocity(fSpeed,0,0)
end

if isMouseDown("Right") == true then
	local bb = Entity.new()
	bb:setComponents(boxAtt)
	boxes[#boxes + 1] = bb
end

if (player:tGetPosY() < -1000) then
	player:tSetPosition(0,5000,0)
end

player:tSetPosition(0,5000,0)

--Loop Through array entities
for i, entity in ipairs(boxes) do
	if entity:tGetPosY() < 200 then
		entity:destroy()
		entity = nil
	end
end
--]]

if isKeyDown("p") == true then
	reloadScene()
elseif isKeyDown("o") == true then
	player:destroy()
end
