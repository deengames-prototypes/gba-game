#ifndef MONSTER_AI_H
#define MONSTER_AI_H

#include <string>

#include "models/entity.h"
#include "models/tile_type.h"

// TODO: probably makes sense to have different classes for different AIs.
class MonsterAI
{
    public:
        static std::string moveRandomly(TileType* mapData, Entity monster);
};

#endif