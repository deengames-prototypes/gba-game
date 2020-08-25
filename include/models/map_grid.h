#ifndef MAP_GRID_H
#define MAP_GRID_H

#include <vector>
#include "models/entity.h"
#include "models/tile_type.h"

class MapGrid
{
    private:
        TileType* _data; // 1D array

        int _width;
        int _height;
    
    public:
        MapGrid(int width, int height);
        int width() { return _width; }
        int height() { return _height; }

        void set(int x, int y, TileType data);
        TileType get(int x, int y);

        void moveMonster(std::shared_ptr<Entity> monster);
        bool isWalkable(int x, int y);
};

#endif