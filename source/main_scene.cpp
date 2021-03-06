#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>

// Images
#include "images/world1.h"
#include "images/world2.h"
#include "images/player.h"
#include "images/palette.h"

#include "models/entity.h"
#include "models/map_grid.h"
#include "main_scene.h"

std::vector<Background *> MainScene::backgrounds() {
    return {};
}

std::vector<Sprite *> MainScene::sprites() {
    std::vector<Sprite *> toReturn;
    
    toReturn.push_back(player.get());

    for (int i = 0; i < walls.size(); i++)
    {
        toReturn.push_back(walls.at(i).get());
    }

    for (int i = 0; i < monsters.size(); i++)
    {
        toReturn.push_back(monsters.at(i).get());
    }

    return toReturn;
}

void MainScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(palettePal, sizeof(palettePal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<Entity> builder;

    player = builder
            .withData(playerTiles, sizeof(playerTiles))
            .withSize(SIZE_16_16)
            .withLocation(playerX * TILE_SIZE, playerY * TILE_SIZE)
            .buildPtr();
    
    currentMap = std::unique_ptr<MapGrid>(new MapGrid(TILES_WIDE, TILES_HIGH));

    for (int y = 0; y < currentMap->height(); y++)
    {
        for (int x = 0; x < currentMap->width(); x++)
        {
            TileType data = currentMap->get(x, y);
            if (data == TileType::Wall)
            {
                walls.push_back(makeWallAt(x, y));
            }
            else if (data == TileType::TriEye)
            {
                monsters.push_back(makeMonsterAt(TileType::TriEye, x, y));
            }
        }
    }
}

std::unique_ptr<Entity> MainScene::makeWallAt(int x, int y)
{
    SpriteBuilder<Entity> builder;
    std::unique_ptr<Entity> wall = builder
        .withData(world1Tiles, sizeof(world1Tiles))
        .withSize(SIZE_16_16)
        .withAnimated(2, 3)
        .withLocation(x * TILE_SIZE, y * TILE_SIZE)
        .buildPtr();
    
    // Set to frame 0
    wall->stopAnimating();
    wall->animateToFrame(0);

    return wall;
}

std::unique_ptr<Entity> MainScene::makeMonsterAt(TileType monsterType, int x, int y)
{
    SpriteBuilder<Entity> builder;
    std::unique_ptr<Entity> monster = builder
        .withSize(SIZE_16_16)
        
        // TODO: dunno how to figure these out from TileType
        .withData(world1Tiles, sizeof(world1Tiles))
        .withAnimated(2, 3)

        .withLocation(x * TILE_SIZE, y * TILE_SIZE)
        .buildPtr();
    
    // Frame 1
    monster->stopAnimating();
    monster->animateToFrame(1);

    return monster;
}

void MainScene::onPlayerMoved()
{
    currentMap->moveMonsters();
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
        if ((keys & KEY_UP) == KEY_UP)
        {
            targetY -= 1;
            if (targetY < 0)
            {
                targetY = TILES_HIGH - 1;
            }
        }
        else if ((keys & KEY_DOWN) == KEY_DOWN)
        {
            targetY = (targetY + 1) % TILES_HIGH;
        }
        else if ((keys & KEY_LEFT) == KEY_LEFT)
        {
            targetX -= 1;
            if (targetX < 0)
            {
                targetX = TILES_WIDE - 1;
            }
        }
        else if ((keys & KEY_RIGHT) == KEY_RIGHT)
        {
            targetX = (targetX + 1) % TILES_WIDE;
        }

        bool canMove = currentMap->get(targetX, targetY) == TileType::Empty;

        if (canMove)
        {
            player->moveTo(targetX * TILE_SIZE, targetY * TILE_SIZE);
            playerX = targetX;
            playerY = targetY;
            justMoved = true;
            TextStream::instance().setText(std::string("moved!"), 3, 3);
            onPlayerMoved();
        }
    }
}
