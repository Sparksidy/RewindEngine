require ("Resources/Lua_Scripts/class")

BaseScript = class()

function BaseScript:init(gameobject)

	self.gameobject = gameobject
	--comment line
	--[[ comment block
	self.dir_x = -1 + math.random() * 2
	self.dir_y = -1 + math.random() * 2
	]]--
end

function BaseScript:tick(dt)
--[[
	local name = go:get_name()

	go.x = go.x + self.dir_x
	go.y = go.y + self.dir_y

	print(name .. " " .. go.x .. "," .. go.y)]]--

end

function BaseScript:delete()
	print("I've been deleted")
end

function register_script()
	return BaseScript
end