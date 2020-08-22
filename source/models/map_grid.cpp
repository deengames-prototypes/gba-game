#include "tile_type.h"
#include "map_grid.h"

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
}

void MapGrid::set(int x, int y, TileType data)
{
    _data[y * _width + x] = data;
}

TileType MapGrid::get(int x, int y)
{
    return _data[y * _width + x];
}