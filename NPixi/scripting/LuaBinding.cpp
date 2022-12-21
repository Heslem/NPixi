#include "LuaBinding.h"

#include <iostream>
#include <filesystem>
#include <string>

#include "../Core.h"
#include "../states/StateManager.h"
#include "../objects/GameObject.h"
#include "../objects/entities/Player.h"
#include "../objects/LuaGameObject.h"

bool intersects(const sf::Rect<float>& a, const sf::Rect<float>& b) {
	return a.intersects(b);
}


LuaBinding::LuaBinding()
{
	this->L = luaL_newstate();
	luaL_openlibs(L);
	using namespace luabridge;

	// Register SFML
	// Register vector
	getGlobalNamespace(L)
		.beginClass<sf::Vector2<float>>("Vector2f")
		.addConstructor <void (*) (float x, float y)>()
		.addProperty("x", &sf::Vector2<float>::x, &sf::Vector2<float>::x)
		.addProperty("y", &sf::Vector2<float>::y, &sf::Vector2<float>::y)
		.endClass();

	getGlobalNamespace(L)
		.beginClass<sf::Vector2<int>>("Vector2i")
		.addProperty("x", &sf::Vector2<int>::x, &sf::Vector2<int>::x)
		.addProperty("y", &sf::Vector2<int>::y, &sf::Vector2<int>::y)
		.endClass();

	getGlobalNamespace(L)
		.beginClass<sf::Vector2<unsigned int>>("Vector2u")
		.addProperty("x", &sf::Vector2<unsigned int>::x, &sf::Vector2<unsigned int>::x)
		.addProperty("y", &sf::Vector2<unsigned int>::y, &sf::Vector2<unsigned int>::y)
		.endClass();

	// TODO: register float rect

	getGlobalNamespace(L)
		.beginClass<sf::Rect<float>>("FloatRect")
		.addConstructor <void (*) (float x, float y, float width, float height)>()
		.addProperty("x", &sf::Rect<float>::left, &sf::Rect<float>::left)
		.addProperty("y", &sf::Rect<float>::top, &sf::Rect<float>::top)
		.addProperty("width", &sf::Rect<float>::width, &sf::Rect<float>::width)
		.addProperty("height", &sf::Rect<float>::height, &sf::Rect<float>::height)
		.endClass();

	getGlobalNamespace(L).addFunction("intersects", &intersects);

	////////////////////////
	
	// Register game classes
	
	// Register class World
	getGlobalNamespace(L)
		.beginClass<IState>("IState")
		.endClass()
		.deriveClass<World, IState>("World")
		.addFunction("GetName", &World::getName)
		.addFunction("Spawn", &World::spawn)
		.endClass();

	// Register class GameObject
	getGlobalNamespace(L)
		.beginClass<GameObject>("GameObject")
		.endClass()
		.deriveClass<LuaGameObject, GameObject>("Object")
		.addConstructor <void (*) (LuaRef)>()
		.addFunction("Destroy", &LuaGameObject::destroy)
		.addFunction("Flip", &LuaGameObject::flip)
		.addFunction("Move", &LuaGameObject::movePhysics)
		.addFunction("SetTexture", &LuaGameObject::setTextureByName)
		.addFunction("GetPosition", &LuaGameObject::getPosition)
		.addFunction("SetPosition", &LuaGameObject::setPositionl)
		.addFunction("SetSize", &LuaGameObject::setSize)
		
		
		.endClass();
	
	getGlobalNamespace(L)
		.beginClass<GameObject>("GameObject")

		.endClass()
		.deriveClass<Player, GameObject>("Player")
		.addFunction("Destroy", &Player::destroy)
		.addFunction("Flip", &Player::flip)
		.addFunction("Move", &Player::movePhysics)
		.addConstructor <void (*) (bool)>()

		.endClass();
	
	// Register class StateManager
	getGlobalNamespace(L)
		.beginClass<StateManager>("StateManager")
		.addFunction("SetState", &StateManager::setCurrentState)
		//.addFunction("GetCurrentState", &StateManager::getCurrentState)
		.endClass();
	// Register class core.
	getGlobalNamespace(L).addFunction("_getCore", Core::getInstance);

	getGlobalNamespace(L)
		.beginClass<Core>("Core")
		.addFunction("Close", &Core::close)
		.addFunction("IsFocus", &Core::isFocus)
		.addFunction("GetStateManager", &Core::getStateManager)
		.addFunction("GetWindowSize", &Core::getWindowSize)
		.endClass();

	////////////////////////
	
	
}

LuaBinding::~LuaBinding()
{
	std::cout << "Close lua." << std::endl;
	lua_close(L);
}

void LuaBinding::doAllScripts(World& world)
{
	using namespace std;
	
	luabridge::setGlobal(L, &world, "_world");

	static const string texturesPath = "content/scripts/";
	for (const auto& entry : filesystem::directory_iterator(texturesPath)) {
		
		try
		{
			luaL_dofile(L, (entry.path().string()).c_str()); 
			luabridge::LuaRef startFunc = luabridge::getGlobal(L, "start");
			startFunc();
		}
		catch (const luabridge::LuaException& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

bool LuaBinding::checkError(int err)
{
	if (err != LUA_OK) {
		std::string message = lua_tostring(L, -1);
		std::cout << message << std::endl;
		return false;
	}
	return true;
}

void LuaBinding::doFile(std::string name)
{
	static const std::string path_to_scripts = "content/scripts/";

	checkError(luaL_dofile(L, (path_to_scripts + name).c_str()));
	//lua_pcall(L, 0, 0, 0);
	luabridge::LuaRef startFunc = luabridge::getGlobal(L, "start");
	startFunc();
}

void LuaBinding::doString(const std::string& str)
{
	checkError(luaL_dostring(L, str.c_str()));
}