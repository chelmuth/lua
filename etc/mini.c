/*
* min.c -- a minimal Lua interpreter
* loads stdin only with minimal error handling.
* no interaction, and no standard library, only a "print" function.
*/

#include <stdio.h>

#define lua_c

#include "lapi.c"
#include "lauxlib.c"
#include "lcode.c"
#include "ldebug.c"
#include "ldo.c"
#include "ldump.c"
#include "lfunc.c"
#include "lgc.c"
#include "llex.c"
#include "lmem.c"
#include "lobject.c"
#include "lopcodes.c"
#include "lparser.c"
#include "lstate.c"
#include "lstring.c"
#include "ltable.c"
#include "ltm.c"
#include "lundump.c"
#include "lvm.c"
#include "lzio.c"

#include "lua.h"
#include "lauxlib.h"


static int print(lua_State *L)
{
	int n=lua_gettop(L);
	int i;
	for (i=1; i<=n; i++) {
		if (i>1) printf("\t");
		if (lua_isstring(L,i))
			printf("%s",lua_tostring(L,i));
		else if (lua_isnil(L,i))
			printf("%s","nil");
		else if (lua_isboolean(L,i))
			printf("%s",lua_toboolean(L,i) ? "true" : "false");
		else
			printf("%s:%p",luaL_typename(L,i),lua_topointer(L,i));
	}
	printf("\n");
	return 0;
}


static char *exec_string =
	"i = 1 + 1\n"
	"print(\"your result is: \"..i)\n";


int main(void)
{
	lua_State *L = lua_open();

	lua_register(L,"print",print);

	if (luaL_dostring(L, exec_string) != 0)
		printf("%s\n", lua_tostring(L,-1));

	lua_close(L);
	return 0;
}
