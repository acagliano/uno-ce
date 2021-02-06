//--------------------------------------
// Program Name: Star Trek Multplayer
// Author: Anthony Cagliano
// License:
// Description:
//--------------------------------------

/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <intce.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Other available headers */
// stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h, debug.h
#include <fileioc.h>
#include <graphx.h>
#include <keypadc.h>

// Game Data Types (Structure Definitions)
#include "flags.h"
#include "network/controlcodes.h"
#include "network/network.h"

// USB Libraries
#include <usbdrvce.h>

#define DEBUG
#undef NDEBUG
#include <debug.h>
#include "uno.h"
#include "gfx/graphics.h"
#include "components.h"

net_flags_t netflags = {0};
bool exit_game=false;

uint8_t getKey(void);   // from asm/getkey.asm

void MainMenu(void);
char menu_opts[][15]={
    "Online Play",
    "Solo Play",
    "Quit Game"
};

enum _menu_opts {
    ONLINE_PLAY,
    SOLO_PLAY,
    QUIT
};

void MainMenu(void) {
    uint24_t menu_x=45;
    uint8_t menu_y=100;
    uint8_t menu_range[2]={0,2};
    uint8_t menu_h;
    bool first_loop=true;
    sk_key_t key=0;
    uint8_t opt, i;
    if(!netflags.network_up) menu_range[0]=1;
    menu_h=(menu_range[1]-menu_range[0]+1)*20;
    opt = menu_range[0];
    gfx_DrawCanvas();
    render_Banner();
    if(netflags.network_up) gfx_SetColor(3);
    else gfx_SetColor(128);
    gfx_FillRectangle(menu_x-35, menu_y-10, 24, 24);
    gfx_RLETSprite(ntwk_icon, menu_x-35, menu_y-10);
    while(1){
        key=getKey();
        if(key==sk_Up) opt-=(opt>menu_range[0]);
        if(key==sk_Down) opt+=(opt<menu_range[1]);
        if(key==sk_Clear) {opt=menu_range[1]; break;}
        if(key==sk_Enter) break;
        if(key || first_loop){
            uint8_t color=gfx_SetTextFGColor(0);
            uint8_t ct=0;
            gfx_BorderedWindowTitle("Main Menu", menu_x, menu_y, 100, menu_h, 96, 239);
            for(i=menu_range[0]; i<=menu_range[1]; i++){
                if(opt==i) {
                    gfx_SetColor(192);
                    gfx_FillRectangle(menu_x, ct*20+menu_y, 100, 20);
                }
                gfx_PrintStringXY(menu_opts[i], menu_x+5, ct*20+menu_y+6);
                ct++;
            }
            gfx_SetTextFGColor(color);
            gfx_BlitBuffer();
        }
            
    }
    if(opt == ONLINE_PLAY) uno_onlineplay();
    if(opt == SOLO_PLAY) uno_soloplay();
    if(opt == QUIT) {exit_game = true;}
    
}


int main(void) {
    gfx_Begin();
    srandom(rtc_Time());
   
    ntwk_init();
    
    gfx_SetDefaultPalette(gfx_8bpp);
    gfx_SetDrawBuffer();
    gfx_SetTextTransparentColor(1);
    gfx_SetTextBGColor(1);
    do {
        MainMenu();
    } while(!exit_game);
    //cache_purge();
    gfx_End();
    usb_Cleanup();
    pgrm_CleanUp();
    return 0;
}

