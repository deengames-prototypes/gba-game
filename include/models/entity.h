#ifndef GBA_GAME_ENTITY_H
#define GBA_GAME_ENTITY_H

#include <libgba-sprite-engine/sprites/sprite.h>

class Entity : public Sprite
{
    public:
    Entity(const Entity& other) : Sprite(other) {}
    Entity(const void *imageData, int imageSize, int x, int y, SpriteSize size) : Sprite(imageData, imageSize, x, y, size) {}
};



#endif // GBA_GAME_ENTITY_H