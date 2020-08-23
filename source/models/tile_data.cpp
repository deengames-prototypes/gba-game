#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "models/tile_data.h"
#include "consts.h"

std::unique_ptr<Sprite> TileData::build_sprite(int x, int y, TileType type) {
    TileData data = tileDataMap.at(type);
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
