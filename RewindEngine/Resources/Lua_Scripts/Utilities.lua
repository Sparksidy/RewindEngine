--Class support
function class(baseclass, body)
	local ret = body or {}

	--if there is a base class, attach our new class to it
	if (baseclass ~= nil) then
		setmetatable(ret, ret)
		ret.__index = baseclass
	end

	--Add the create function
	ret.Create = function(self, constructionData, origionalSubClass)
		local obj
		if (self.__index ~= nil) then
			if (origionalSubClass ~= nil) then
				obj = self.__index:Create(constructionData, origionalSubClass);
			else
				obj = self.__index:Create(constructionData, self);
			end
		else
			obj = constructionData or {};
		end

		setmetatable(obj, obj);
		obj.__index = self;
		if (self.__operators ~= nil) then
			for key, val in pairs(self.__operators) do
				obj[key] = val
			end
		end
		return obj;
	end

	return ret;
end

--[[
--Utility classes
Vector3 = class(nil, {x = 0, y = 0, z = 0})
Vector4 = class(nil, {x = 0, y = 0, z = 0, w = 0})

--Utility class function example
function Vector3:AsArg()
	return vec3Temp(self.x, self.y, self.z);
end

function Vector4:AsArg()
	return vec4Temp(self.x, self.y, self.z, self.w);
end
]]--

--declare base character class
Character = class(nil, nil)
function Character:Initialize()
end
function Character:Update(dt)
end
function Character:Unload()
end