#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "models/tile_data.h"
#include "consts.h"


static TileData getTileData(TileType type) {
    switch (type)
    {
    case TileType::Player:
        return TileData(playerTiles, sizeof(playerTiles), 0, 1);

    case TileType::Wall:
        return TileData(world1Tiles, sizeof(world1Tiles), 0, 2);
    
    case TileType::TriEye:
        return TileData(world1Tiles, sizeof(world1Tiles), 1, 2);
    
    default:
        break;
    }
};

std::unique_ptr<Sprite> TileData::buildSprite(int x, int y, TileType type) {
    TileData data = getTileData(type);
    SpriteBuilder<Sprite> builder;

    auto entity = builder
        .withData(data.imageData, data.imageSize)
        .withSize(SIZE_16_16)
        .withAnimated(data.numFrames, 3)
        .withLocation(x * TILE_SIZE, y * TILE_SIZE)
        .buildPtr();
    
    // Set to frame 0
    entity->stopAnimating();
    entity->animateToFrame(data.frameIndex);

    return entity;
}
