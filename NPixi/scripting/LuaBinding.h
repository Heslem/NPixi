#pragma once

#include <string>


extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include <LuaBridge/LuaBridge.h>
#include "../states/World.h"

class LuaBinding sealed {
public:
	
	LuaBinding();
	~LuaBinding();
	LuaBinding(const LuaBinding&) = delete;

	void doFile(std::string name);
	void doString(const std::string& str);


	void doAllScripts(World& world);
private:
	bool checkError(int err);

	lua_State* L;
};