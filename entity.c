#include <snes.h>

typedef struct
{
	u8 id;

	u16 x;
	u16 y;

	u16 gfxOffset;
	u8 palletOffset;
	u8 priority;

} Entity;

void updateEntity(Entity* _entity){
	oamSet(_entity->id,_entity->x,_entity->y,_entity->priority,0,0,_entity->gfxOffset, _entity->palletOffset);
}

void setEntityState(Entity* _entity, u8  _size, u8 _hide){
    oamSetEx(_entity->id, _size, _hide);
}