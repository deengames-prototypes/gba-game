#ifndef MAP_GRID
#define MAP_GRID

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
};

#endif