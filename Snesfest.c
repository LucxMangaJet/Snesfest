#include <snes.h>
#include "entity.c"

//DATA
extern u8 snesfont;
extern u8 m0, m0_end, p0, p0_end, t0, t0_end;
extern u8 c0, c0_end;
extern u8 char_pic, char_pic_end, char_pal, char_pal_end;

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
	u16* tile = ((u16*)&c0) + ((y>>3)*32 + (x>>3));

	return (*tile);
}


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

	//
	setMode(BG_MODE0, 0);
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

	u16 colData = getCollisionTile(x+ 16, y +32); //center bottom

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
