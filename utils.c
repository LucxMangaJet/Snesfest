#include <snes.h>
#include "entity.c"

#define MAP_PAL(x) (x << 10)

const u8 COLOR_5b = 0b11111000;
//0bbbbbgggggrrrrr
u16 makeColor(u8 r, u8 g, u8 b){
	u16 res = ((u16)b&COLOR_5b) <<7;
	res |= ((u16)g&COLOR_5b) <<2;
	res |= ((u16)r&COLOR_5b) >>3;
	return res;
}

#define COLOR(r,g,b) makeColor(r,g,b)


u8 freeEntityID = 0;

u8 newEntityID(){return freeEntityID++;}

typedef struct 
{
	Entity entity;

	s16 dx;
	s16 dy;

	s8 speed;
	u8 health;

} Player;