#include <snes.h>

const u8 COLOR_5b = 0b11111000;

#define MAP_PAL(x) (x << 10)


//0rrrrrgggggbbbbb
u16 makeColor(u8 r, u8 g, u8 b){
	u16 res = ((u16)b&COLOR_5b) <<7;

	res |= ((u16)g&COLOR_5b) <<2;
	res |= ((u16)r&COLOR_5b) >>3;
	return res;
}

#define COLOR(r,g,b) makeColor(r,g,b)
