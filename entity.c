#ifndef ENTITY_DEF
#define ENTITY_DEF

#include <snes.h>

typedef struct
{
	u8 id;

	u8 x;
	u8 y;

	u8 gfxOffset;
	u8 palette;
	u8 priority;
    bool flipX;


} Entity;


Entity defaultEntity(){
    Entity e;
    e.id = 0;
    e.x = 0;
    e.y = 0;
    e.gfxOffset = 0;
    e.palette = 0;
    e.priority = 0;
    e.flipX =0;
    return e;
}

void updateEntity(Entity* _entity){
	oamSet(_entity->id*4,_entity->x,_entity->y,_entity->priority,_entity->flipX,0,_entity->gfxOffset, _entity->palette);
}

void setEntityState(Entity* _entity, u8  _size, u8 _hide){
    oamSetEx(_entity->id*4, _size, _hide);
}

void consoleDebugEntity(u8 x, u8 y, Entity* _entity){
 consoleDrawText(x,y, "%d x:%d y:%d gfx:%d pal:%d p:%d  ",
 (int)_entity->id, (int) _entity->x, (int)_entity->y, (int)_entity->gfxOffset, (int)_entity->palette, (int)_entity->priority);
}


#endif /* !ENTITY_DEF */