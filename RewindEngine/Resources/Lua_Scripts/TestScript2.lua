require ("Resources/Lua_Scripts/class")

TestScript2 = class(BaseScript)

function TestScript2:init(gameobject)

	
	self.gameobject = gameobject
	self.madeUpVar = 45
	--comment line
	--[[ comment block
	self.dir_x = -1 + math.random() * 2
	self.dir_y = -1 + math.random() * 2
	]]--
end

function TestScript2:tick(dt)

	local go = self.gameobject
	local tr = self.gameobject:GetTransformComponent()
	local rigidbody = self.gameobject:GetRigidbodyComponent()
	rigidbody.mass = 10;
	


	local speed = 2.0
	
	if (KeyboardEvent.IsKeyPressed(KeyboardKeys.KEY_A)) then
		tr.rotation = tr.rotation - speed
		self.gameobject:GetTransformComponent().rotation = tr.rotation
		print(self.madeUpVar)

		local  currentTime = self.gameobject:GetAnimatedSpriteComponent().SecondsPerFrame
		print(currentTime)
		currentTime = currentTime - 0.005
		
		if(currentTime < 0) then
			currentTime = 0
		end

		self.gameobject:GetAnimatedSpriteComponent().SecondsPerFrame = currentTime

	end

	if (KeyboardEvent.IsKeyPressed(KeyboardKeys.KEY_D)) then
		local  currentTime = self.gameobject:GetAnimatedSpriteComponent().SecondsPerFrame
		print(currentTime)
		currentTime = currentTime + 0.005

		self.gameobject:GetAnimatedSpriteComponent().SecondsPerFrame = currentTime
	end

end

function TestScript2:delete()
	print("I've been deleted")
end

function register_script()
	return TestScript2
end