#ifndef GBA_GAME_ENTITY_H
#define GBA_GAME_ENTITY_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include "models/tile_type.h"

class Entity
{
    protected:
        int x;
        int y;
        TileType type;
        std::shared_ptr<Sprite> sprite;
    public:
        Entity(int x, int y, TileType type);

        void moveTo(int x, int y);

        int getX() { return x; }
        int getY() { return y; }
        TileType getType() { return type; }
        std::shared_ptr<Sprite> getSprite() { return sprite; }
};



#endif // GBA_GAME_ENTITY_H
