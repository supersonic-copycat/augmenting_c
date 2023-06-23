M = require("math")

function t()
	tortoise_move(4.0)
	tortoise_turn(90.0)
	tortoise_move(4.0)
	tortoise_turn(135.0)
	tortoise_move(4.0*M.sqrt(2.0))
end

t()
