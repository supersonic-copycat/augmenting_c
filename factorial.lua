local function factorial (n)
	local res = 1
	if n > 0 then
	repeat
		res = res*n;
		n = n-1;
	until not (n > 0)
	end
	return res
end

print(factorial(5))
