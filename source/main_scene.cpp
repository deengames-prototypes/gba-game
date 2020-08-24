#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>

// Images
#include "images/palette.h"

#include "models/entity.h"
#include "models/map_grid.h"
#include "consts.h"
#include "main_scene.h"

std::vector<Background *> MainScene::backgrounds() {
    return {};
}

std::vector<Sprite *> MainScene::sprites() {
    std::vector<Sprite *> toReturn;
    
    toReturn.push_back(player->getSprite().get());

    for (int i = 0; i < walls.size(); i++)
    {
        toReturn.push_back(walls.at(i)->getSprite().get());
    }

    for (int i = 0; i < monsters.size(); i++)
    {
        toReturn.push_back(monsters.at(i)->getSprite().get());
    }

    return toReturn;
}

void MainScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(palettePal, sizeof(palettePal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    player = std::unique_ptr<Entity>(new Entity(playerX, playerY, TileType::Player));
    
    currentMap = std::unique_ptr<MapGrid>(new MapGrid(TILES_WIDE, TILES_HIGH));

    for (int y = 0; y < currentMap->height(); y++)
    {
        for (int x = 0; x < currentMap->width(); x++)
        {
            TileType data = currentMap->get(x, y);
            if (data == TileType::Wall)
            {
                walls.push_back(makeEntityAt(x, y, TileType::Wall));
            }
            else if (data == TileType::TriEye)
            {
                monsters.push_back(makeEntityAt(x, y, TileType::TriEye));
            }
        }
    }
}

std::unique_ptr<Entity> MainScene::makeEntityAt(int x, int y, TileType type)
{
    return std::unique_ptr<Entity>(new Entity(x, y, type));
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
            player->moveTo(targetX, targetY);
            playerX = targetX;
            playerY = targetY;
            justMoved = true;
            TextStream::instance().setText(std::string("moved!"), 3, 3);
            onPlayerMoved();
        }
    }
}
