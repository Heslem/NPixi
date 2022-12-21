
print("I'm running.'")

function update(me)
	me:Move(1, 0)
end

function start()
	print("Script started.")
	--print(_world:getName())

	if _world ~= nil then
		print("World isn't nil")
		print(_world:GetName())

		obj = Object(update)
		obj:SetTexture("staff")
		
		vectorSize = Vector2f(10, 10)
		obj:SetSize(vectorSize)
		_world:Spawn(obj)
	end
end
