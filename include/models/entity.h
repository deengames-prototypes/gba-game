#ifndef ENTITY_H
#define ENTITY_H

#include "models/tile_type.h"

class Entity
{
    public:
        Entity(TileType type, int tileX, int tileY);
        int _tileX;
        int _tileY;
        TileType _type;
};

#endif