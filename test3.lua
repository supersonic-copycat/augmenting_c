M = require("math")

local function koch_move(length, depth)
	if depth == 0 then
		tortoise_move(length)
	else
		local sub_length = length / 3
		local sub_depth = depth - 1
		local move = function (angle)
			koch_move(sub_length, sub_depth)
			tortoise_turn(angle)
		end
		local angles = {60, -120, 60, 0}
		for _, a in ipairs(angles) do
			move(a)
		end

	end
end

local function snowflake(length, depth, sign)
	for _=0, 4 do
		koch_move(length, depth)
		tortoise_turn(-120 * sign)
	end
end

snowflake(6, 3, 1)
tortoise_turn(180)
snowflake(6, 3, -1)
