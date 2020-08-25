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
    std::vector<Sprite*> toReturn;
    
    if (!isGameOver)
    {
        toReturn.push_back(player->getSprite().get());
    }
    
    for (int i = 0; i < environment.size(); i++)
    {
        toReturn.push_back(environment.at(i)->getSprite().get());
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

    player = std::unique_ptr<Entity>(new Entity(START_POS_X, START_POS_Y, TileType::Player));
    
    currentMap = std::unique_ptr<MapGrid>(new MapGrid(TILES_WIDE, TILES_HIGH));

    for (int y = 0; y < currentMap->height(); y++)
    {
        for (int x = 0; x < currentMap->width(); x++)
        {
            TileType data = currentMap->get(x, y);
            if (data == TileType::Wall)
            {
                environment.push_back(makeEntityAt(x, y, TileType::Wall));
            }
            else if (data == TileType::Dirt)
            {
                environment.push_back(makeEntityAt(x, y, TileType::Dirt));
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
    for (int i = 0; i < monsters.size(); i++)
    {
        auto m = monsters.at(i);
        currentMap->moveMonster(m);

        if (m->getTileX() == player->getTileX() && m->getTileY() == player->getTileY())
        {
            isGameOver = true;
        }
    }
}

void MainScene::tick(u16 keys)
{
    if (isGameOver)
    {
        return;
    }

    if (keys == 0)
    {
        // Nothing pressed ...
        justMoved = false;
        return;
    }

    int targetX = player->getTileX();
    int targetY = player->getTileY();

    if (!justMoved)
    {
        if ((keys & KEY_UP) == KEY_UP)
        {
            targetY -= 1;
        }
        else if ((keys & KEY_DOWN) == KEY_DOWN)
        {
            targetY += 1;
        }
        else if ((keys & KEY_LEFT) == KEY_LEFT)
        {
            targetX -= 1;
        }
        else if ((keys & KEY_RIGHT) == KEY_RIGHT)
        {
            targetX += 1;
        }

        bool canMove = currentMap->isWalkable(targetX, targetY);

        if (canMove)
        {
            removeDirtAt(player->getTileX(), player->getTileY());
            player->moveTo(targetX, targetY);
            justMoved = true;
            onPlayerMoved();
        }
    }
}

void MainScene::removeDirtAt(int tx, int ty)
{
    currentMap->set(tx, ty, TileType::Empty);

    for (auto it = environment.begin(); it != environment.end(); it++)
    {
        auto e = *it;
        if (e->getType() == TileType::Dirt && e->getTileX() == tx && e->getTileY() == ty)
        {
            TextStream::instance().setText(std::string(std::string("ate dirt at ") + std::to_string(e->getTileX()) + std::string(", ") + std::to_string(e->getTileY())), 3, 3);
            environment.erase(it);
            it--;
            return;
        }
    }
}
