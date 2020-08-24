#ifndef GBA_GAME_TRIEYE_COMMAND_H
#define GBA_GAME_TRIEYE_COMMAND_H

#include "models/command.h"

class TriEyeCommand : public Command
{
public:
    void tick(Entity* entity, MainScene* scene, MapGrid* mapGrid, u16 keys) {}
};



#endif // GBA_GAME_TRIEYE_COMMAND_H