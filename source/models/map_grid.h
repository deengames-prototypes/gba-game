#ifndef MAP_GRID
#define MAP_GRID

#include "tile_type.h"

class MapGrid
{
    public:
        MapGrid(int width, int height);
        // TODO: size should be read-only 
        int _width;
        int _height;

        void set(int x, int y, TileType data);
        TileType get(int x, int y);
    private:
        TileType* _data; // 1D array
};

#endif