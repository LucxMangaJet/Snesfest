#include <snes.h>

//DATA
extern u8 snesfont;
extern u8 m0, m0_end, p0, p0_end, t0, t0_end;
extern u8 char_pic, char_pic_end, char_pal, char_pal_end;

//VARIABLES

u16 posX = 32;
u16 posY = 96; 

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

	consoleDrawText(0,1,"t0 size %p", (&t0_end - &t0));
	consoleDrawText(0,2,"m0 size %p", (&m0_end - &m0));
	consoleDrawText(0,3,"p0 size %p", (&p0_end - &p0));

	//OEM

	oamInitGfxSet(&char_pic, (&char_pic_end-&char_pic), &char_pal, (&char_pal_end - &char_pal), 0, 0x4000, OBJ_SIZE16_L32);

	oamSet(0,posX,posY,3,0,0,0,0);
	oamSetEx(0, OBJ_SMALL, OBJ_SHOW);

	//
	setMode(BG_MODE0, 0);
	setScreenOn();
}

void update(){

	posX+=2;
	posY+=1;

	consoleDrawText(0,4,"x %i y %i",posX, posY);

	oamSet(0,posX,posY,0,0,0,0,0);
	WaitForVBlank();
}


int main(void) {	
	
	init();
	
	while(1)
		update();
	return 0;
}
