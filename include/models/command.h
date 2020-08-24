#ifndef GBA_GAME_COMMAND_H
#define GBA_GAME_COMMAND_H

#include "models/entity.h"

// Command design pattern
// didn't make sense to subclass Entity, so here we are

class Command
{
public:
    virtual void tick(Entity* entity, MainScene* scene, MapGrid* mapGrid, u16 keys) {};
    static std::unique_ptr<Command> getTileCommand(TileType type);
};



#endif // GBA_GAME_COMMAND_H