#include <snes.h>

extern char snesfont;


extern char tex_background1_map;
extern char tex_background1_map_end;
extern char tex_background1_pic;
extern char tex_background1_pic_end;
extern char tex_background1_pal;

void init(){
	consoleInit();

	//Background
	//Copy tile to VRAM
	bgInitTileSet(0, &tex_background1_pic, &tex_background1_pal, 0, (&tex_background1_pic_end - tex_background1_pic), 8, BG_4COLORS0, 0x2000);

	//Copy Map to VRAM
	bgInitMapSet(0, &tex_background1_map, (&tex_background1_map_end - &tex_background1_map), SC_32x32, 0x0000);


	//Text
	//consoleInitText(2, 0, &snesfont);

	//consoleDrawText(5,8,"SNES FEST");

	//Init
	setMode(BG_MODE1, 0);
	bgSetDisable(1);
	bgSetDisable(2);

	setBrightness(0xF); 
}

void update(){

	WaitForVBlank();
}


int main(void) {	
	
	init();
	
	while(1)
		update();
	return 0;
}
