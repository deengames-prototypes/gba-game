#include "models/type_type.h"
#include "models/map_grid.h"

void MapGrid::MapGrid(int width, int height)
{
    this.width = width;
    this.height = height;
    data = TileType[width * height];
}

void MapGrid::set(int x, int y, TileType data)
{
    data[y * this.width + x] = data;
}

TileType MapGrid::get(int x, int y)
{
    return this.data[y * this.width + x];
}