#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>

// Images
#include "images/world1.h"

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

    return toReturn;
}

void MainScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(world1Pal, sizeof(world1Pal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<Sprite> builder;

    player = builder
            .withData(world1Tiles, sizeof(world1Tiles))
            .withSize(SIZE_16_16)
            .withLocation(playerX * TILE_SIZE, playerY * TILE_SIZE)
            .buildPtr();

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
        .withAnimated(2, 3)
        .withLocation(x * TILE_SIZE, y * TILE_SIZE)
        .buildPtr();

    wall->stopAnimating();
    wall->animateToFrame(1);
    return wall;
}

void MainScene::tick(u16 keys) {
    std::string keysMessage = std::string("Keys: ") + std::to_string(keys);
    TextStream::instance().setText(keysMessage, 0, 0);

    if (justMoved && keys == 0)
    {
        // Nothing pressed ...
        justMoved = false;
    }

    if (!justMoved)
    {
        if ((keys & UP_ARROW) == UP_ARROW)
        {
            playerY -= 1;
            if (playerY < 0)
            {
                playerY = TILES_HIGH - 1;
            }
            justMoved = true;
        }
        else if ((keys & DOWN_ARROW) == DOWN_ARROW)
        {
            playerY = (playerY + 1) % TILES_HIGH;
            justMoved = true;
        }
        else if ((keys & LEFT_ARROW) == LEFT_ARROW)
        {
            playerX -= 1;
            if (playerX < 0)
            {
                playerX = TILES_WIDE - 1;
            }
            justMoved = true;
        }
        else if ((keys & RIGHT_ARROW) == RIGHT_ARROW)
        {
            playerX = (playerX + 1) % TILES_WIDE;
            justMoved = true;
        }

        player->moveTo(playerX * TILE_SIZE, playerY * TILE_SIZE);
    }
}
