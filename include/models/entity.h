#ifndef GBA_GAME_ENTITY_H
#define GBA_GAME_ENTITY_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include "models/tile_type.h"

class Entity : public Sprite
{
    using Sprite::Sprite;

    public:
        int _tileX;
        int _tileY;
        TileType _type;
};



#endif // GBA_GAME_ENTITY_H
