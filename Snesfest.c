#include <snes.h>
#include "cdata.c"
#include "entity.c"
#include "utils.c"

Player player;
s16 i; //iterator


#define camX (player.entity.x -112)
#define camY (player.entity.y -96)


u8 isColliding_32x32(Entity* _entity, u16 _wx, u16 _wy){
	u8 ex = _entity->x;
	u8 ey = _entity->y;

	return (_wx >= ex) && (_wy >= ey) && (_wx <= ex + 32) && (_wy <= ey + 32);	
}


void initPlayers(){

	player.health = 3;
	player.speed = 4;
	player.entity = defaultEntity();
	player.entity.id = newEntityID();
	player.entity.priority = 3;
	player.entity.x = 0;
	player.entity.y = 0;
	player.entity.palette = 0;
	setEntityState(&player.entity,OBJ_LARGE, OBJ_SHOW);
}

void init(){

	consoleInit();

	//Palette
    dmaCopyCGram(&d_pal, 0, SIZE(d_pal)); 

	//BG
	dmaCopyVram(&d_bg_tiles, 0x0000, SIZE(d_bg_tiles));

    bgSetGfxPtr(0, 0x0000);
    bgInitMapSet(0, &d_map_bg1, SIZE(d_map_bg1), SC_32x32, 0x4000);

	//objects
	dmaCopyVram(&d_obj_tiles,0x2000, SIZE(d_obj_tiles));
	oamInitGfxAttr(0x2000, OBJ_SIZE16_L32);
	
	initPlayers();

	//
	setMode(BG_MODE1, 0);
	bgSetDisable(1);
	bgSetDisable(2);
	setScreenOn();
}

void updatePlayer(Player* _player){

	if(_player->dx != 0)
		_player->entity.flipX = _player->dx <0;

	u8 x = _player->entity.x + _player->dx;
	u8 y = player.entity.y + _player->dy;

	player.entity.x = x;
	player.entity.y = y;

	updateEntity(&_player->entity, camX, camY);
}

void update(){
	updatePlayer(&player);

	bgSetScroll(1,camX,camY);	
}


void processPlayerInput(u16 _pad, Player* _player){

	if(_pad & KEY_RIGHT)
		_player->dx  = _player->speed;
	else if(_pad & KEY_LEFT)
		_player->dx = -_player->speed;
	else 
	 	_player->dx = 0;

	if(_pad & KEY_UP)
		_player->dy = -_player->speed;
	else if(_pad & KEY_DOWN)
		_player->dy = _player->speed;
	else 
		_player->dy = 0;
}

void processInput(){

	processPlayerInput(padsCurrent(0), &player);
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
