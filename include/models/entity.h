#ifndef GBA_GAME_ENTITY_H
#define GBA_GAME_ENTITY_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include "models/tile_type.h"
#include "models/command.h"

class Entity
{
    protected:
        int tileX;
        int tileY;
        TileType type;
        std::shared_ptr<Sprite> sprite;
        std::unique_ptr<Command> command;
    public:
        Entity(int tileX, int tileY, TileType type);

        void moveTo(int tileX, int tileY);
        void tick(MainScene* scene, MapGrid* mapGrid, u16 keys) {
            command->tick(this, scene, mapGrid, keys);
        }

        int getTileX() { return tileX; }
        int getTileY() { return tileY; }
        TileType getType() { return type; }
        std::shared_ptr<Sprite> getSprite() { return sprite; }
};



#endif // GBA_GAME_ENTITY_H
