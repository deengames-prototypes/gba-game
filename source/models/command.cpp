#include "models/command.h"
#include "models/tile_type.h"
#include "command/player_command.h"
#include "command/trieye_command.h"

std::unique_ptr<Command> Command::getTileCommand(TileType type) {
    switch (type)
    {
    case TileType::Player:
        return std::unique_ptr<PlayerCommand>(new PlayerCommand());
    
    case TileType::TriEye:
        return std::unique_ptr<TriEyeCommand>(new TriEyeCommand());
    
    default:
        break;
    }
}