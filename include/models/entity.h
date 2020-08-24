#ifndef GBA_GAME_ENTITY_H
#define GBA_GAME_ENTITY_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include "models/tile_type.h"

// Not really a model, more like an MV (sprite + data)
class Entity
{
    protected:
        int tileX;
        int tileY;
        TileType type;
        std::shared_ptr<Sprite> sprite;
    public:
        Entity(int tileX, int tileY, TileType type);

        void moveTo(int tileX, int tileY);

        int getTileX() { return tileX; }
        int getTileY() { return tileY; }
        TileType getType() { return type; }
        std::shared_ptr<Sprite> getSprite() { return sprite; }
};



#endif // GBA_GAME_ENTITY_H
