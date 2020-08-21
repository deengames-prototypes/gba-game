#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "ff.h"
#include "lama.h"
#include "main_scene.h"

const u16 UP_ARROW = 64;
const u16 DOWN_ARROW = 128;
const u16 LEFT_ARROW = 32;
const u16 RIGHT_ARROW = 16;

std::vector<Background *> MainScene::backgrounds() {
    return {};
}

std::vector<Sprite *> MainScene::sprites() {
    return {  lama.get() };
}

void MainScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<Sprite> builder;

    lama = builder
            .withData(lamaTiles, sizeof(lamaTiles))
            .withSize(SIZE_32_32)
            .withAnimated(6, 3)
            .withLocation(50, 50)
            .buildPtr();
}

void MainScene::tick(u16 keys) {
    std::string keysMessage = std::string("Keys: ") + std::to_string(keys);
    TextStream::instance().setText(keysMessage, 0, 0);

    int vx = 0;
    int vy = 0;

    if ((keys & UP_ARROW) == UP_ARROW)
    {
        vy = -1;   
    }
    else if ((keys & DOWN_ARROW) == DOWN_ARROW)
    {
        vy = 1;
    }
    
    if ((keys & LEFT_ARROW) == LEFT_ARROW)
    {
        vx = -1;   
    }
    else if ((keys & RIGHT_ARROW) == RIGHT_ARROW)
    {
        vx = 1;
    }

    lama->setVelocity(vx, vy);
}
