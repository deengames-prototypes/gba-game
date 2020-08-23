#ifndef MAP_GRID_H
#define MAP_GRID_H

#include <vector>
#include "models/tile_type.h"
#include "models/entity.h"

class MapGrid
{
    private:
        TileType* _data; // 1D array

        int _width;
        int _height;

        std::vector<Entity> _monsters;
    
    public:
        MapGrid(int width, int height);
        int width() { return _width; }
        int height() { return _height; }

        void set(int x, int y, TileType data);
        TileType get(int x, int y);

        void moveMonsters();
};

#endif