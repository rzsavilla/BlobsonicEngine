-- Used to create the player entity handle
--[[
	Creating entities within lua is currently disabled
	Must handle entities already created in the scene by XML
--]]

-- Player jump delay prevent multiple jumps
jumpTimer = Timer.new()
jumpTimer:reset()

player = Entity.new()
player:handleEntity("player")

playerSpeed = 50
playerJumpForce = 1500
playerJumpDelay = 0.6
