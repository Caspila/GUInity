#include "LuaBinder.h"



static int average(lua_State *L)
{
	/* get number of arguments */
	int n = lua_gettop(L);
	double sum = 0;
	int i;

	/* loop through each argument */
	for (i = 1; i <= n; i++)
	{
		/* total the arguments */
		sum += lua_tonumber(L, i);
	}

	/* push the average */
	lua_pushnumber(L, sum / n);

	/* push the sum */
	lua_pushnumber(L, sum);

	/* return the number of results */
	return 2;
}
int LuaBinder::transform(lua_State* L)
{
	//lua_pushlightuserdata(L, player->transform.get());
	
	lua_pushnumber(L, 5);


	glm::vec3 vec3(10, 10, 10);

	lua_newtable(L);

	lua_pushnumber(L, vec3.x);
	lua_setfield(L, -2, "x");
	lua_pushnumber(L, vec3.y);
	lua_setfield(L, -2, "y");
	lua_pushnumber(L, vec3.y);
	lua_setfield(L, -2, "z");


// lua_pushlightuserdata(L, &vec3);

	/* push the sum */
	//lua_pushnumber(L, sum);

	/* return the number of results */
	return 1;
}

LuaBinder::LuaBinder()
{
	L = luaL_newstate();

	/* load Lua base libraries */
	luaL_openlibs(L);

	/* register our function */
	lua_register(L, "transform", transform);
	//lua_register(L, "test", test);
	//lua_register(L, "vec3", vec3);
	//
	///* run the script */

	//

	
}

void LuaBinder::RunScript(const char* path)
{
	//luaL_dofile(L, path);// "C:/dev/GIT/GUInity/opengl_testing/avg.lua");
	luaL_dofile(L, "C:/dev/GIT/GUInity/opengl_testing/avg.lua");
}

LuaBinder::~LuaBinder()
{
	///* cleanup Lua */
	lua_close(L);
}
