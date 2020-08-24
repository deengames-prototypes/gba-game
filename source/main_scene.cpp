#include <libgba-sprite-engine/sprites/sprite_builder.h>
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

    player = std::unique_ptr<Entity>(new Entity(START_POS_X, START_POS_Y, TileType::Player));
    
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
    player->tick(this, currentMap, keys);
}
