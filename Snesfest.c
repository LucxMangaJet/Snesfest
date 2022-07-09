#include <snes.h>
#include "entity.c"

//DATA
extern u8 snesfont;
extern u8 m0, m0_end, p0, p0_end, t0, t0_end;
extern u8 char_pic, char_pic_end, char_pal, char_pal_end;

//VARIABLES

Entity player;


void init(){

	consoleInit();


	//Background
	//Copy tile to VRAM
	bgInitTileSet(1, &t0, &p0, 0, (&t0_end - &t0), 8, BG_4COLORS0, 0x6000);

	// Copy Map to VRAM
	bgInitMapSet(1, &m0, (&m0_end - &m0),SC_32x32, 0x1000);
	//Text
	consoleInitText(0, 0, &snesfont);
	consoleSetTextCol(RGB5(0,0,0), RGB5(31,31,31));

	//ENTITIES
	oamInitGfxSet(&char_pic, (&char_pic_end-&char_pic), &char_pal, (&char_pal_end - &char_pal), 0, 0x4000, OBJ_SIZE16_L32);
	
	player.id =0;
	player.priority = 3;
	player.x = 92;
	
	setEntityState(&player,OBJ_SMALL, OBJ_SHOW);

	//
	setMode(BG_MODE0, 0);
	setScreenOn();
}

void update(){

	consoleDrawText(0,3, "Frame: %d", snes_vblank_count);
	consoleDrawText(0,4,"x %i y %i       ",player.x, player.y);

	updateEntity(&player);
	WaitForVBlank();
}

void processInput(){

	u16 pad0 = padsCurrent(0);

	if(pad0 & KEY_RIGHT)
		player.x ++;
	if(pad0 & KEY_LEFT)
		player.x--;
	if(pad0 & KEY_UP)
		player.y--;
	if(pad0 & KEY_DOWN)
		player.y++;

}


int main(void) {	
	
	init();
	
	while(1){
		processInput();
		update();
	}
	return 0;
}
