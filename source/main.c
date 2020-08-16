#include "Intellisense.h" //capitalize headers?

//ARM defines
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

//MMAP - stolen from GBATEK
#define IO_MMAP   ( 0x04000000 )
#define VRAM_MMAP ( 0x06000000 )

//REGISTERS/VMEM - stolen from GBATEK
#define LCD_CTRL_REG *( (volatile uint16 *)(IO_MMAP) )
#define vmem *( (volatile uint16 *)(VRAM_MMAP) )

//GBA mode 3
#define M3_SCREEN_WIDTH  ( 240 )
#define M3_SCREEN_HEIGHT ( 160 )
typedef uint16 color; // gba apparently uses rgb15
const uint16 MODE_3 = 0x0403;

//static inline function vs macro functions
static inline uint16 m3_get_color(uint32 r, uint32 g, uint32 b)
{ return (uint16)( r | ( g << 5 ) | ( b << 10 ) ) ; }
static inline void _plot_pixel(uint8 _x, uint8 _y, uint16 _color)
{ (vmem)[(uint16 *) ((_y)*M3_SCREEN_WIDTH + _x)] = &(_color); }

int main( void )
{
    LCD_CTRL_REG = &MODE_3; // set to mode 3
    uint8 x=0, y=0, t=0;
    for ( x = 0; x < M3_SCREEN_WIDTH; ++x ) {
        for ( y = 0; y < M3_SCREEN_HEIGHT; ++y ) {
            //plot a pixel
            uint16 color = m3_get_color( ((x&y)+t*5)&0x1F,
                                         ((x&y)+t*3)&0x1F,
                                         ((x&y)+t)&0x1F);
            _plot_pixel( x, y, color);
        }
    } while (1);
    return 0;
}