#include "models/entity.h"
#include "models/tile_data.h"
#include "consts.h"

Entity::Entity(int tileX, int tileY, TileType type) {
    this->tileX = tileX;
    this->tileY = tileY;
    this->type = type;
    this->sprite = TileData::buildSprite(tileX, tileY, type);
}

void Entity::moveTo(int tileX, int tileY) {
    this->tileX = tileX;
    this->tileY = tileY;
    sprite->moveTo(tileX * TILE_SIZE, tileY * TILE_SIZE);
}