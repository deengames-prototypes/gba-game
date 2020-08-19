#ifndef GBA_GAME_MAIN_SCENE_H
#define GBA_GAME_MAIN_SCENE_H

#include <libgba-sprite-engine/scene.h>

class MainScene : public Scene {
private:
    std::unique_ptr<Sprite> lama;
public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    MainScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_GAME_MAIN_SCENE_H
