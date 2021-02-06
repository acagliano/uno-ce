#include "components.h"

void render_Banner(void){
    uint8_t color=gfx_SetTextFGColor(231);
    gfx_BorderedWindow(2, 2, 320-4, 34, 228, 64);
    gfx_SetTextScale(3, 3);
    gfx_PrintStringXY("UNO", 8, 8);
    gfx_SetTextScale(1, 1);
    gfx_PrintStringXY(version, 120, 8);
    gfx_PrintStringXY("by ACagliano", 120, 18);
    gfx_SetTextFGColor(color);
}
    
void gfx_BorderedWindowTitle(const char* title, uint24_t x, uint8_t y, uint24_t w, uint8_t h, uint8_t border, uint8_t background){
    uint8_t color=gfx_SetTextFGColor(255);
    uint24_t width=gfx_GetStringWidth(title);
    uint24_t str_start_x=(w/2)-(width/2);
    gfx_SetColor(border);
    gfx_FillRectangle(x-2, y-22, w+4, h+24);
    gfx_PrintStringXY(title, x+str_start_x, y-15);
    gfx_SetTextFGColor(color);
    gfx_SetColor(background);
    gfx_FillRectangle(x, y, w, h);
}
