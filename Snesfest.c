#include <snes.h>
#include "cdata.c"
#include "entity.c"

//VARIABLES

u8 freeEntityID = 0;

u8 newEntityID(){return freeEntityID++;}

typedef struct 
{
	Entity entity;

	s16 dx;
	s16 dy;

	s16 speed;
	s16 jumpForce;
	s16 gravity;
	u8 grounded;

} Player;

Player player0;
Player player1;

s16 maxDY = 8;

u16 getCollisionTile(u16 x, u16 y) {
	
	return 0;

	//u16* tile = ((u16*)&c0) + ((y>>3)*32 + (x>>3));
	//return (*tile);
}

void initPlayers(){

	player0.dx = 0;
	player0.dy = 0;
	player0.speed = 4;
	player0.gravity = 1;
	player0.jumpForce = -12;
	player0.entity = defaultEntity();
	player0.entity.id = newEntityID();
	player0.entity.priority = 3;
	player0.entity.x = 180;
	player0.entity.y = 135;
	setEntityState(&player0.entity,OBJ_LARGE, OBJ_SHOW);

	player1.dx = 0;
	player1.dy = 0;
	player1.speed = 4;
	player1.gravity = 1;
	player1.jumpForce = -10;
	player1.entity = defaultEntity();
	player1.entity.id = newEntityID();
	player1.entity.priority = 3;
	player1.entity.x = 20;
	player1.entity.y = 135;
	player1.entity.palletOffset = 1;
	player1.entity.flipX = 1;
	setEntityState(&player1.entity, OBJ_LARGE, OBJ_SHOW);
}



void init(){

	consoleInit();

	// Put screen off and Wait VBlank to allow us to update VRAM
    setBrightness(0);
    WaitForVBlank();
    
	//Objects
	oamInitGfxSet(&d_obj_tiles, d_obj_tiles_size, &d_pal, d_pal_size, 0, 0x2000, OBJ_SIZE16_L32);

	//Background
	bgInitTileSet(1,d_bg_tiles, d_pal,0, d_bg_tiles_size, d_pal_size, BG_16COLORS, 0x1000);
	bgInitMapSet(1, &d_map_bg1, d_map_bg1_size, SC_32x32, 0x4000);

	//Text
	//consoleInitText(0, 0, &snesfont);
	//consoleSetTextCol(RGB5(0,0,0), RGB5(31,31,31));
	//ENTITIES
	
	initPlayers();

	//
	setMode(BG_MODE1, 0);
	setScreenOn();
}

void updatePlayer(Player* _player){

	if(_player->dx != 0)
		_player->entity.flipX = _player->dx >0;

	s16 dy = _player->dy;
	dy += _player->gravity;
	if(dy > maxDY)
		dy = maxDY;
	_player->dy = dy;

	u8 x = _player->entity.x + _player->dx;
	u8 y = _player->entity.y + _player->dy;

	u16 colData =  y > 150; //getCollisionTile(x+ 16, y +32); //center bottom

	if(colData){
		y = y & 0xF8;
		_player->dy =0;
		_player->grounded = 1;
	}else{
		_player->grounded = 0;
	}

	_player->entity.x =x;
	_player->entity.y =y;

	updateEntity(&_player->entity);
}

void update(){

	//consoleDrawText(0,3, "Frame: %d", snes_vblank_count);
	//consoleDebugEntity(0,4, &player0);
	//consoleDebugEntity(0,5, &player1);

	updatePlayer(&player0);
	updatePlayer(&player1);	
}


void processPlayerInput(u16 _pad, Player* _player){

	if(_pad & KEY_RIGHT)
		_player->dx  = _player->speed;
	else if(_pad & KEY_LEFT)
		_player->dx = -_player->speed;
	else 
	 	_player->dx = 0;

	if((_pad & KEY_UP) && _player->grounded)
		_player->dy = _player->jumpForce;
}

void processInput(){

	processPlayerInput(padsCurrent(0), &player0);
	processPlayerInput(padsCurrent(1), &player1);
}

int main(void) {	
	
	init();
	
	while(1){
		processInput();
		update();
		WaitForVBlank();
	}
	return 0;
}
