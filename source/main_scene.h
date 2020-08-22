#ifndef GBA_GAME_MAIN_SCENE_H
#define GBA_GAME_MAIN_SCENE_H

#include <libgba-sprite-engine/scene.h>

class MainScene : public Scene {
private:
    std::unique_ptr<Sprite> makeWallAt(int x, int y);

    const int TILE_SIZE = 16;
    // TODO: move calculations somewhere for width/height/etc.
    const int TILES_WIDE = 15;
    const int TILES_HIGH = 10;

    // Direction bitflags
    const u16 UP_ARROW = 64;
    const u16 DOWN_ARROW = 128;
    const u16 LEFT_ARROW = 32;
    const u16 RIGHT_ARROW = 16;

    // TODO: extract out a class/lambda something like justPressed(key, lambda)
    bool justMoved = false;

    std::unique_ptr<Sprite> player;
    std::vector<std::unique_ptr<Sprite>> walls;

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
