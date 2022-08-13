#include <snes.h>
#include "cdata.c"
#include "entity.c"
#include "utils.c"

Entity player;
s16 i; //iterator

Entity enemies[64];
u8 enemies_count = 0;
u8 enemies_max = 8;

#define camX (player.x -112)
#define camY (player.y -96)


u8 isColliding_32x32(Entity* _entity, u16 _wx, u16 _wy){
	u8 ex = _entity->x;
	u8 ey = _entity->y;

	return (_wx >= ex) && (_wy >= ey) && (_wx <= ex + 32) && (_wy <= ey + 32);	
}

void initEnemy(Entity* _enemy, u8 _id){	
	initEntity(_enemy);
	_enemy->id = 64 + _id;
	_enemy->priority = 3;
	_enemy->speed = 4;
	_enemy->x = _id*32;
	_enemy->y = 0;
	_enemy->palette = 1;
	setEntityState(_enemy,OBJ_LARGE, OBJ_SHOW);
}


void initEnemies(){
	for (i = 0; i < enemies_max; i++){
		initEnemy(&enemies[i],i);
	}
	enemies_count = enemies_max;
}

void initPlayer(){
	initEntity(&player);
	player.id = newEntityID();
	player.priority = 3;
	player.health = 3;
	player.speed = 4;
	setEntityState(&player,OBJ_LARGE, OBJ_SHOW);
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
	
	initPlayer();
	initEnemies();
	
	//
	setMode(BG_MODE1, 0);
	bgSetDisable(1);
	bgSetDisable(2);
	setScreenOn();
}



void update(){

	for (i = 0; i < enemies_count; i++){
		updateEntity(&enemies[i], camX,camY);
	}

	updateEntity(&player, camX, camY);
	bgSetScroll(0,camX,camY);	
}


void processPlayerInput(u16 _pad){

	if(_pad & KEY_RIGHT){
		player.x  += player.speed;
		player.flipX = false;
	}
	else if(_pad & KEY_LEFT){
		player.x -= player.speed;
		player.flipX = true;
	}

	if(_pad & KEY_UP)
		player.y -= player.speed;
	else if(_pad & KEY_DOWN)
		player.y += player.speed;
}

void processInput(){

	processPlayerInput(padsCurrent(0));
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
