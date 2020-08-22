#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>

// Images
#include "images/world1.h"
#include "images/world2.h"
#include "images/player.h"
#include "images/palette.h"

#include "main_scene.h"

std::vector<Background *> MainScene::backgrounds() {
    return {};
}

std::vector<Sprite *> MainScene::sprites() {
    std::vector<Sprite *> toReturn;
    
    toReturn.push_back(player.get());
    toReturn.push_back(iceWall.get());
    for (int i = 0; i < walls.size(); i++)
    {
        toReturn.push_back(walls.at(i).get());
    }

    return toReturn;
}

void MainScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(palettePal, sizeof(palettePal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<Sprite> builder;

    player = builder
            .withData(playerTiles, sizeof(playerTiles))
            .withSize(SIZE_16_16)
            .withLocation(playerX * TILE_SIZE, playerY * TILE_SIZE)
            .buildPtr();
    
    iceWall = builder.withData(world2Tiles, sizeof(world2Tiles))
    .withSize(SIZE_16_16).withLocation(6 * TILE_SIZE, 4 * TILE_SIZE).buildPtr();

    for (int x = 0; x < TILES_WIDE; x++)
    {
        walls.push_back(makeWallAt(x, 0));
        walls.push_back(makeWallAt(x, TILES_HIGH - 1));
    }

    for (int y = 0; y < TILES_HIGH - 1; y++)
    {
        // duplicates in corners :/
        walls.push_back(makeWallAt(0, y));
        walls.push_back(makeWallAt(TILES_WIDE - 1, y));
    }
}

std::unique_ptr<Sprite> MainScene::makeWallAt(int x, int y)
{
    SpriteBuilder<Sprite> builder;
    std::unique_ptr<Sprite> wall = builder
        .withData(world1Tiles, sizeof(world1Tiles))
        .withSize(SIZE_16_16)
        .withLocation(x * TILE_SIZE, y * TILE_SIZE)
        .buildPtr();

    return wall;
}

void MainScene::tick(u16 keys) {
    if (keys == 0)
    {
        // Nothing pressed ...
        justMoved = false;
        return;
    }

    int targetX = playerX;
    int targetY = playerY;

    if (!justMoved)
    {
        if ((keys & UP_ARROW) == UP_ARROW)
        {
            targetY -= 1;
            if (targetY < 0)
            {
                targetY = TILES_HIGH - 1;
            }
        }
        else if ((keys & DOWN_ARROW) == DOWN_ARROW)
        {
            targetY = (targetY + 1) % TILES_HIGH;
        }
        else if ((keys & LEFT_ARROW) == LEFT_ARROW)
        {
            targetX -= 1;
            if (targetX < 0)
            {
                targetX = TILES_WIDE - 1;
            }
        }
        else if ((keys & RIGHT_ARROW) == RIGHT_ARROW)
        {
            targetX = (targetX + 1) % TILES_WIDE;
        }

        // TODO: store model info properly
        bool canMove = true;
        // for(const auto& wall : walls)
        // {
        //     if (player->collidesWith(*wall.get()))
        //     {
        //         TextStream::instance().setText(std::string("can't!!!"), 5, 5);
        //         canMove = false;
        //         break;
        //     }
        // }

        canMove = (targetX != 0 && targetY != 0 && targetX != TILES_WIDE - 1 && targetY != TILES_HIGH - 1);
        
        if (canMove)
        {
            player->moveTo(targetX * TILE_SIZE, targetY * TILE_SIZE);
            playerX = targetX;
            playerY = targetY;
            justMoved = true;
            TextStream::instance().setText(std::string("moved!"), 5, 5);
        }
    }
}
