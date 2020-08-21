#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "ff.h"
#include "lama.h"
#include "main_scene.h"

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
            // TODO: turn into 16x16 flat colour
            .withSize(SIZE_32_32)
            .withAnimated(1, 1)
            .withLocation(0, 0)
            .buildPtr();
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

        lama->moveTo(playerX * TILE_SIZE, playerY * TILE_SIZE);
    }
}
