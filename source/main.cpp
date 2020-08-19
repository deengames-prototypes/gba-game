#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/palette/palette_manager.h>
#include <libgba-sprite-engine/allocator.h>

#include "main_scene.h"

int main( void )
{
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    auto startScene = new MainScene(engine);
    engine->setScene(startScene);

    while (true) {
        engine->update();
    }

    return 0;
}