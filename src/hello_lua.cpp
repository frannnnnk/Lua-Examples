
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern "C" 
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "gtest/gtest.h"

TEST(HELLO_LUA, LUA_CREATE) 
{
	lua_State * L = luaL_newstate();
	EXPECT_TRUE(L != NULL);
	lua_close(L);
}

TEST(HELLO_LUA, LUA_PUSH_PARAMETERS)
{
	lua_State * L = luaL_newstate();
	ASSERT_TRUE(L != NULL);

	lua_pushstring(L, "Hello,world!");
	ASSERT_TRUE(lua_isstring(L, 1));

	int depth = lua_gettop(L);
	ASSERT_TRUE(depth == 1);

	int ret = luaL_loadfile(L, "../lua_scripts/hello.lua");
	ASSERT_TRUE(ret == 0);

	ret = lua_pcall(L, 0, 0, 0);
	ASSERT_TRUE(ret == 0);

	lua_getglobal(L, "str");
	ASSERT_TRUE(lua_isstring(L, -1));

	const char * str = lua_tostring(L, -1);
	ASSERT_TRUE(str != NULL);

	depth = lua_gettop(L);
	ASSERT_TRUE(depth == 2);

	lua_close(L);
}

TEST(HELLO_LUA, LUA_CALL_FUNCTIONS)
{
	lua_State * L = luaL_newstate();
	ASSERT_TRUE(L != NULL);

	int ret = luaL_loadfile(L, "../lua_scripts/hello.lua");
	ASSERT_TRUE(ret == 0);

	ret = lua_pcall(L, 0, 0, 0);
	ASSERT_TRUE(ret == 0);

	lua_getglobal(L, "add");
	ASSERT_TRUE(lua_isfunction(L, -1));

	lua_pushnumber(L, 1);
	lua_pushnumber(L, 2);
	ret = lua_pcall(L, 2, 1, 0);
	ASSERT_TRUE(ret == 0);

	ret = lua_tonumber(L, -1);
	ASSERT_TRUE(ret == 3);
	lua_close(L);
}

TEST(HELLO_LUA, LUA_GET_FROM_TABLE)
{
	const char * script = "background = {r = 0.30, g = 0.10, b = 0}";
	lua_State * L = luaL_newstate();
	ASSERT_TRUE(L != NULL);

	ASSERT_FALSE(luaL_loadstring(L, script) || lua_pcall(L, 0, 0, 0));

	lua_getglobal(L, "background");
	ASSERT_TRUE(lua_istable(L, -1));

	lua_getfield(L, 1, "r");
	ASSERT_TRUE(lua_isnumber(L, -1));
	int r = lua_tonumber(L, -1) * 255;
	lua_pop(L, 1);

	lua_getfield(L, 1, "g");
	ASSERT_TRUE(lua_isnumber(L, -1));
	int g = lua_tonumber(L, -1) * 255;
	lua_pop(L, 1);	

	lua_getfield(L, 1, "b");
	ASSERT_TRUE(lua_isnumber(L, -1));
	int b = lua_tonumber(L, -1) * 255;
	lua_pop(L, 1);	

	lua_close(L);
}

TEST(HELLO_LUA, LUA_CONSTRUCT_TABLE)
{
	lua_State * L = luaL_newstate();
	ASSERT_TRUE(L != NULL);

	lua_newtable(L);
	ASSERT_TRUE(lua_istable(L, 1));

	lua_pushnumber(L, 1);
	lua_setfield(L, -2, "r");
	ASSERT_TRUE(lua_istable(L, 1));

	lua_pushnumber(L, 2);
	lua_setfield(L, -2, "g");
	ASSERT_TRUE(lua_istable(L, 1));

	lua_pushnumber(L, 3);
	lua_setfield(L, -2, "b");
	ASSERT_TRUE(lua_istable(L, 1));
	
	lua_close(L);
}

int main(int argc, char * argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

