#include <snes.h>
#include "cdata.c"
#include "entity.c"
#include "utils.c"

Player player0;
Player player1;
s16 maxDY = 8;
s16 i; //iterator

u8 cloud_scroll =0;

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
	player0.entity.palette = 0;
	setEntityState(&player0.entity,OBJ_LARGE, OBJ_SHOW);

	player1.dx = 0;
	player1.dy = 0;
	player1.speed = 4;
	player1.gravity = 1;
	player1.jumpForce = -12;
	player1.entity = defaultEntity();
	player1.entity.id = newEntityID();
	player1.entity.priority = 3;
	player1.entity.x = 20;
	player1.entity.y = 135;
	player1.entity.gfxOffset = 4;
	player1.entity.flipX = 1;
	player1.entity.palette = 1;
	setEntityState(&player1.entity, OBJ_LARGE, OBJ_SHOW);
}

void init(){

	consoleInit();

	//Palette
    dmaCopyCGram(&d_pal, 0, SIZE(d_pal)); 

	//BG
	dmaCopyVram(&d_bg_tiles, 0x0000, SIZE(d_bg_tiles));

    bgSetGfxPtr(0, 0x0000);
    bgInitMapSet(0, &d_map_bg1, SIZE(d_map_bg1), SC_32x32, 0x4000);

	bgSetGfxPtr(1,0x0000);
	bgInitMapSet(1,&d_map_bg2, SIZE(d_map_bg2), SC_32x32, 0x5000);

	//objects
	dmaCopyVram(&d_obj_tiles,0x2000, SIZE(d_obj_tiles));
	oamInitGfxAttr(0x2000, OBJ_SIZE16_L32);
	
	initPlayers();

	//
	setMode(BG_MODE1, 0);
	bgSetDisable(2);
	setScreenOn();
}

void updatePlayer(Player* _player){

	if(_player->dx != 0)
		_player->entity.flipX = _player->dx <0;

	s16 dy = _player->dy;
	dy += _player->gravity;
	if(dy > maxDY)
		dy = maxDY;
	_player->dy = dy;

	u8 x = _player->entity.x + _player->dx;
	u8 y = _player->entity.y + _player->dy;

	u16 collision =  y > 190; //getCollisionTile(x+ 16, y +32); //center bottom

	if(collision){
		y = 190;//y & 0xF8;
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
	updatePlayer(&player0);
	updatePlayer(&player1);

	if(snes_vblank_count%30==0){
		cloud_scroll++;
		bgSetScroll(1,cloud_scroll,0);	
	}
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
