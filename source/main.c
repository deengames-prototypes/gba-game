#include "Intellisense.h" //capitalize headers?
#include "tonc.h"

int main( void )
{
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2; // set to mode 3

    u8 x=0, y=0, t=0;
    for ( x = 0; x < SCREEN_WIDTH; ++x ) {
        for ( y = 0; y < SCREEN_HEIGHT; ++y ) {
            //plot a pixel
            m3_plot(x, y, RGB15(Mod(x, 31), Mod(y, 31), Mod(t, 31)));
        }
    } while (1);
    return 0;
}