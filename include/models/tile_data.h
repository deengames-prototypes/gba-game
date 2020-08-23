#ifndef GBA_GAME_TILE_DATA_H
#define GBA_GAME_TILE_DATA_H

#include <map>

// Images
#include "images/world1.h"
#include "images/world2.h"
#include "images/player.h"

#include "models/tile_type.h"

class TileData
{
    public:
        TileData(const unsigned int* imageData, int frameIndex, int numFrames) {
            this->imageData = imageData;
            this->frameIndex = frameIndex;
            this->numFrames = numFrames;
        }
        static std::unique_ptr<Sprite> build_sprite(int x, int y, TileType type);
        const unsigned int* imageData;
        int frameIndex;
        int numFrames;
};

const std::map<TileType, TileData> tileDataMap = {
    { TileType::Player, TileData(playerTiles, 0, 1) },
    { TileType::Wall, TileData(world1Tiles, 0, 2) },
    { TileType::TriEye, TileData(world1Tiles, 1, 2) }
};

#endif // GBA_GAME_TILE_DATA_H