require ("Resources/Lua_Scripts/class")

TestScript1 = class(BaseScript)

function TestScript1:init(gameobject)

	
	self.gameobject = gameobject
	self.madeUpVar = 89
	i = 0
	transformArray = {}
	currentTime = 0;
	for i=0,200 do
	   transformArray[i] = vec2(0,0)
    end


end

	--comment line
	--[[ comment block
	self.dir_x = -1 + math.random() * 2
	self.dir_y = -1 + math.random() * 2
	]]--

function TestScript1:tick(dt)

	--print(dt)
	local transform = self.gameobject:GetTransformComponent()
	local RigidBody = self.gameobject:GetRigidbodyComponent()

	--RigidBody.mass = 1;

	currentTime = currentTime + 1.0/60.0
	if(i < 200 and currentTime >= .6) then 
		transformArray[i].x = transform.translation.x
		transformArray[i].y = transform.translation.y
		i = i + 1
		currentTime = 0.0
	end

	--print(i)
	local speed = 10.0

	if(KeyboardEvent.IsKeyPressed(KeyboardKeys.KEY_R))
	then
		print("R pressed")
		--cut the animation speed in half
		local animatedComponent = self.gameobject:GetAnimatedSpriteComponent()

		if(i > 0) then
			i = i-1
			local newCurrent = vec2(0,0)
			newCurrent.x = transformArray[i].x
			newCurrent.y = transformArray[i].y
			--print(newCurrent.x)
			--print(newCurrent.y)

			self.gameobject:GetTransformComponent().translation = newCurrent
		end
	end

	if(KeyboardEvent.IsKeyPressed(KeyboardKeys.KEY_D) ) then
		--tr.rotation = tr.rotation + speed
		local pos = transform.translation
		pos.x = pos.x + speed
		--self.gameobject:GetTransformComponent().rotation = tr.rotation
		self.gameobject:GetTransformComponent().translation = pos
		--print(self.madeUpVar)

	elseif(KeyboardEvent.IsKeyPressed(KeyboardKeys.KEY_A) ) then
		--tr.rotation = tr.rotation + speed
		local pos = transform.translation
		pos.x = pos.x - speed
		--self.gameobject:GetTransformComponent().rotation = tr.rotation
		self.gameobject:GetTransformComponent().translation = pos
		--print(self.madeUpVar)
	end

	if(KeyboardEvent.IsKeyReleased(32)) then
		print("space released")
		RigidBody.acceleration = 5;


	end

end

function TestScript1:delete()
	print("I've been deleted")
end

function register_script()
	return TestScript1
end

function SavePosition()
	--local transform = self.gameobject:GetTransformComponent()
	--print("SavePosition");
end
 
