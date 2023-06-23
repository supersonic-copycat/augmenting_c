M = require("math")
local function drawShape(perimeter, vertices)
	local side = perimeter / vertices
	local angle = 360 / vertices
	for _=0,vertices do
		tortoise_move(side)
		tortoise_turn(angle)
	end
end

drawShape(18, 3)
drawShape(10, 30)
