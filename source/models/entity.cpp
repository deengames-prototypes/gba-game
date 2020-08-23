#include "models/entity.h"
#include "models/tile_data.h"
#include "consts.h"

Entity::Entity(int x, int y, TileType type) {
    this->x = x;
    this->y = y;
    this->type = type;
    this->sprite = TileData::build_sprite(x, y, type);
}

void Entity::moveTo(int x, int y) {
    this->x = x;
    this->y = y;
    sprite->moveTo(x * TILE_SIZE, y * TILE_SIZE);
}