#ifndef ENTITY_DEF
#define ENTITY_DEF

#include <snes.h>

typedef struct
{
	u8 id;

	u16 x;
	u16 y;

    s8 speed;
	u8 health;

    //gfx
	u8 gfxOffset;
	u8 palette;
	u8 priority;
    bool flipX;

} Entity;


void initEntity(Entity* _entity){
    _entity->id = 0;
    _entity->x = 0;
    _entity->y = 0;
    _entity->speed = 1;
    _entity->health = 1;
    _entity->gfxOffset = 0;
    _entity->palette = 0;
    _entity->priority = 0;
    _entity->flipX =0;
}

void updateEntity(Entity* _entity, u16 _camX, u16 _camY){

    u16 x = _entity->x - _camX;
    u16 y = _entity->y - _camY;

    if(x>255)
        x =255;

    if(y>223)
        y = 223;

	oamSet(_entity->id*4,(u8)x, (u8)y, _entity->priority,_entity->flipX,0,_entity->gfxOffset, _entity->palette);
}

void setEntityState(Entity* _entity, u8  _size, u8 _hide){
    oamSetEx(_entity->id*4, _size, _hide);
}

void consoleDebugEntity(u8 x, u8 y, Entity* _entity){
 consoleDrawText(x,y, "%d x:%d y:%d gfx:%d pal:%d p:%d  ",
 (int)_entity->id, (int) _entity->x, (int)_entity->y, (int)_entity->gfxOffset, (int)_entity->palette, (int)_entity->priority);
}


#endif /* !ENTITY_DEF */