#include "LuaGameObject.h"

#include "../Core.h"

LuaGameObject::LuaGameObject(luabridge::LuaRef u_func)
	: GameObject(LUA_OBJECT), m_Func(u_func)
{
	setSize(sf::Vector2f(40, 40));
	setTexture(Core::getInstance().getAssetsManager().Textures["player"]);
}

LuaGameObject::~LuaGameObject()
{
}

void LuaGameObject::setTextureByName(const char* name)
{
	setTexture(Core::getInstance().getAssetsManager().Textures[name]);
}

void LuaGameObject::setPositionl(const float& x, const float& y)
{
	setPosition(x, y);
}

void LuaGameObject::update()
{
	m_Func(this);
}
