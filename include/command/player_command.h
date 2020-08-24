#ifndef GBA_GAME_PLAYER_COMMAND_H
#define GBA_GAME_PLAYER_COMMAND_H

#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "models/command.h"
#include "main_scene.h"

class PlayerCommand : public Command
{
    private:
        bool justMoved;
    public:
        void tick(Entity* player, MainScene* scene, MapGrid* mapGrid, u16 keys) {
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

                bool canMove = mapGrid->isEmpty(targetX, targetY);

                if (canMove)
                {
                    player->moveTo(targetX, targetY);
                    justMoved = true;
                    TextStream::instance().setText(std::string("moved!"), 3, 3);
                    scene->onPlayerMoved();
                }
            }
        };
};



#endif // GBA_GAME_PLAYER_COMMAND_H