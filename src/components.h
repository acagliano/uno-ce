
#include <graphx.h>
#include <stdint.h>

const char* version="v1.2 beta";
#define CANVAS_COLOR 247

#define gfx_DrawCanvas() \
        gfx_FillScreen(CANVAS_COLOR);
        
#define gfx_FillRectangleColor(x, y, w, h, color) \
        gfx_SetColor(color); \
        gfx_FillRectangle((x), (y), (w), (h));

#define gfx_BorderedWindow(x, y, w, h, border_color, background_color) \
        gfx_SetColor(background_color); \
        gfx_FillRectangle((x), (y), (w), (h)); \
        gfx_SetColor(border_color); \
        gfx_Rectangle((x-1), (y-1), (w+2), (h+2)); \
        gfx_Rectangle((x-2), (y-2), (w+4), (h+4));
    
        
        
void render_Banner(void);
void gfx_BorderedWindowTitle(const char* title, uint24_t x, uint8_t y, uint24_t w, uint8_t h, uint8_t border, uint8_t background);
