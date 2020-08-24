#include <stdlib.h> // rand
#include <string>

#include "ai/monster_ai.h"
#include "models/entity.h"
#include "models/tile_type.h"

std::string MonsterAI::moveRandomly(TileType* data, std::shared_ptr<Entity> monster)
{
    // If we "randomly" move into a wall or something, meh.
    // TODO: could check if target tile is empty; also, could check what's
    // available based on monster position.
    auto move = rand() % 4;
    if (move == 0)
    {
        return "-x";
    }
    else if (move == 1)
    {
        return "x";
    }
    else if (move == 2)
    {
        return "-y";
    }
    else if (move == 3)
    {
        return "y";
    }
};