#ifndef GBA_GAME_MAIN_SCENE_H
#define GBA_GAME_MAIN_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include "models/map_grid.h"

class MainScene : public Scene {
private:
    std::unique_ptr<Sprite> makeWallAt(int x, int y);
    std::unique_ptr<Sprite> makeMonsterAt(TileType monster, int x, int y);
    void onPlayerMoved();
    
    const int TILE_SIZE = 16;
    // TODO: move calculations somewhere for width/height/etc.
    const int TILES_WIDE = 15;
    const int TILES_HIGH = 10;

    // TODO: extract out a class/lambda something like justPressed(key, lambda)
    bool justMoved = false;

    std::unique_ptr<Sprite> player;
    std::vector<std::unique_ptr<Sprite>> walls;
    std::vector<std::unique_ptr<Sprite>> monsters;
    std::unique_ptr<MapGrid> currentMap;

    // TODO: move this into a "model" class. With C++ tests?
    int playerX = 4;
    int playerY = 3;
public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    MainScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_GAME_MAIN_SCENE_H
