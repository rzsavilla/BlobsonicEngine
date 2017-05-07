-- Create entity handles for entities within the scene

floorHandle = Entity.new()
floorHandle:handleEntity("floor")

--Pickup variables
pickup1 = Entity.new()
pickup1:handleEntity("pickup1")

pickups = {
	pickup1
}
