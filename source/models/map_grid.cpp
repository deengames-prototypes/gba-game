#include <string>
#include <vector>

#include "ai/monster_ai.h"
#include "models/entity.h"
#include "models/tile_type.h"
#include "models/map_grid.h"

MapGrid::MapGrid(int width, int height)
{
    _width = width;
    _height = height;
    _data = new TileType[_width * _height];

    // TODO: non-hard-coded data I suppose? Load from file, maybe?
    // TODO: extract out grid from actual "map" maybe?

    for (int y = 0; y < _height; y++)
    {
        for (int x = 0; x < _width; x++)
        {
            set(x, y, TileType::Empty);
        }
    }

    for (int x = 0; x < _width; x++)
    {
        set(x, 0, TileType::Wall);    
        set(x, _height - 1, TileType::Wall);    
    }

    for (int y = 0; y < _height; y++)
    {
        set(0, y, TileType::Wall);    
        set(_width - 1, y, TileType::Wall);    
    }

    for (int i = 0; i < _monsters.size(); i++)
    {
        auto monster = _monsters.at(i);
        set(monster._tileY, monster._tileY, monster._type);
    }
    set(2, 2, TileType::TriEye);
}

void MapGrid::moveMonsters()
{
    for (int i = 0; i < _monsters.size(); i++)
    {
        auto monster = _monsters.at(i);
        auto move = MonsterAI::moveRandomly(_data, monster);
        auto targetX = monster._tileX;
        auto targetY = monster._tileY;

        if (move.compare(std::string("x")) == 0)
        {
            targetX++;
        }
        else if (move.compare(std::string("-x")) == 0)
        {
            targetX--;
        }
        else if (move.compare(std::string("y")) == 0)
        {
            targetY++;
        }
        else if (move.compare(std::string("-y")) == 0)
        {
            targetY--;
        }

        if (targetX >= 0 && targetX < _width && targetY >= 0 && targetY < _height && targetX != monster._tileX && targetY != monster._tileY)
        {
            // TODO: poison-dropping monster ... ? :thinking:
            set(monster._tileX, monster._tileY, TileType::Empty);
            set(targetX, targetY, monster._type);
            monster._tileX = targetX;
            monster._tileY = targetY;
        }
    }
}

void MapGrid::set(int x, int y, TileType data)
{
    _data[y * _width + x] = data;
}

TileType MapGrid::get(int x, int y)
{
    return _data[y * _width + x];
}