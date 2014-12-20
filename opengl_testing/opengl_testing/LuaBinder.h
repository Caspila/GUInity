#pragma once

#include "Module.h"
#include "Actor.h"

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

class LuaBinder
{
public:
	LuaBinder();
	~LuaBinder();


	/* initialize Lua */
	lua_State* L;
	void RunScript(const char* path);

	static shared_ptr<Actor> player;

	static int transform(lua_State* L);

};

