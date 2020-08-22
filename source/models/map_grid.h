#ifndef MAP_GRID
#define MAP_GRID

#include "tile_type.h"

class MapGrid
{
    private:
        int width;
        int height;
        TileType data[];
    public:
        void set(int x, int y, TileType data);
        TileType get(int x, int y);
};

#endif