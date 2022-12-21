#pragma once
#include "../scripting/LuaBinding.h"
#include "GameObject.h"

class LuaGameObject sealed :
	public GameObject
{
public:
	explicit LuaGameObject(luabridge::LuaRef u_func);
	~LuaGameObject();
	LuaGameObject(const LuaGameObject&) = delete;

	void setTextureByName(const char* name); // LUA WRAP
	void setPositionl(const float& x, const float& y); // LUA WRAP

	void update() override;
private:
	luabridge::LuaRef m_Func;
};