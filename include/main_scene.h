#ifndef GBA_GAME_MAIN_SCENE_H
#define GBA_GAME_MAIN_SCENE_H

#include <libgba-sprite-engine/scene.h>

#include "models/map_grid.h"
#include "models/entity.h"

class MainScene : public Scene {
private:
    std::unique_ptr<Entity> makeEntityAt(int x, int y, TileType monster);

    // TODO: extract out a class/lambda something like justPressed(key, lambda)
    bool justMoved = false;

    std::unique_ptr<Entity> player;
    std::vector<std::unique_ptr<Entity>> walls;
    std::vector<std::unique_ptr<Entity>> monsters;
    std::unique_ptr<MapGrid> currentMap;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    MainScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void onPlayerMoved();

    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_GAME_MAIN_SCENE_H
