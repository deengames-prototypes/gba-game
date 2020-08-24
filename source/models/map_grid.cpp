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
        set(monster.getTileX(), monster.getTileY(), monster.getType());
    }
    set(2, 2, TileType::TriEye);
}

void MapGrid::moveMonsters()
{
    for (int i = 0; i < _monsters.size(); i++)
    {
        auto monster = _monsters.at(i);
        auto move = MonsterAI::moveRandomly(_data, monster);
        auto targetX = monster.getTileX();
        auto targetY = monster.getTileY();

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

        if (targetX >= 0 && targetX < _width && targetY >= 0 && targetY < _height && targetX != monster.getTileX() && targetY != monster.getTileY())
        {
            // TODO: poison-dropping monster ... ? :thinking:
            set(monster.getTileX(), monster.getTileY(), TileType::Empty);
            set(targetX, targetY, monster.getType());
            monster.moveTo(targetX, targetY);
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

bool MapGrid::isEmpty(int x, int y)
{
    return get(x, y) == TileType::Empty && x >= 0 && y >= 0 && x <= _width && y <= _height;
}