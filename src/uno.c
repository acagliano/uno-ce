#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include "network/controlcodes.h"
#include "network/network.h"
#include "asm/functions.h"
#include "uno.h"
#include "components.h"

#include "gfx/graphics.h"

uint8_t num_len(uint24_t num){
    uint8_t len=0;
    do {
        len++;
        num/=10;
    } while(num>10);
    return num;
}

gfx_rletsprite_t* cardgfx[] = {
    zero_data, one_data, two_data,
    three_data, four_data, five_data,
    six_data, seven_data, eight_data,
    nine_data, skip_data, reverse_data,
    wild_data, draw_two_data, wild_plus_four_data
};

char* servername="remote.titrek.us:51000";
gamedata_t game={0};

void uno_soloplay(void){

}

char alert[100]={'\0'};
char alert_up=0;

void uno_onlineplay(void){
    bool prefer_ssl=false;
    bool loop_game=true;
    sk_key_t key=0;
    ntwk_send(CONNECT, PS_VAL(prefer_ssl), PS_STR(servername));
    do{
        key = getKey();
        if(key==sk_Clear) {ntwk_send_nodata(DISCONNECT); break;}
        if(game.status){
        
        }
        else boot_WaitShort();
        ntwk_process();
    } while(loop_game);

}

void uno_RenderLobby(void){
    gfx_DrawCanvas();
    render_Banner();
    if(game.game_available)
        gfx_PrintStringXY("Game Available", 10, 100);
    else gfx_PrintStringXY("No Game Available", 10, 100);
    gfx_SetTextXY(10, 110);
    gfx_PrintString("Players in Lobby: ");
    gfx_PrintUInt(game.lobby_count, 2);
    gfx_BlitBuffer();
}

void uno_RenderHand(void){
    static uint24_t card_selected=0;
    uint24_t hand_size=(sizeof(game.hand)/sizeof(card_t));
    uint24_t range_start = card_selected/7*7;
    uint24_t range_end = (card_selected/7+1)*7;
    uint24_t x=60, i;
    uint8_t y=180;
    gfx_FillRectangleColor(0,175, 320, 240-175, 64);
    for(i=range_start; i<range_end; i++){
        card_t* card=&game.hand[i];
        if(card->value!=VAL_NULL){
            uint8_t bg=0;
            if(i==card_selected){
                gfx_SetColor(172);
                gfx_FillRectangle(x-2, y-2, 36, 60);
            }
            if(card->value > VAL_DRAW2) bg=0;
            else {
                if(card->color == COL_RED) bg=224;
                else if(card->color == COL_GREEN) bg=3;
                else if(card->color == COL_YELLOW) bg=231;
                else if(card->color == COL_BLUE) bg=24;
            }
            gfx_SetColor(bg);
            gfx_FillRectangle(x, y, 32, 48);
            gfx_RLETSprite(cardgfx[card->value], x, y);
            x+=36;
        }
    }
}

void uno_render_playerlist(void){
    uint24_t x=2;
    uint8_t i, y=33;
    for(i=0; i<game.board.player_ct; i++)
    {
        player_t* p=&game.board.playerinfo[i];
        gfx_PrintStringXY("Player", x+2, 10*i+y+2);
        gfx_PrintUInt(i, num_len(i));
        gfx_SetTextXY(40, 10*i+y+2);
        gfx_PrintUInt(p->card_count, num_len(p->card_count));
    }
}

void uno_render_deckandtop(void){
    uint8_t bg=0;
    uint8_t card_color=game.board.top.color;
    gfx_BorderedWindow(140, 70, 72, 52, 229, 64);
    gfx_RLETSprite(back_data, 142, 72);
    if(card_color == COL_RED) bg=224;
    else if(card_color == COL_GREEN) bg=3;
    else if(card_color == COL_YELLOW) bg=231;
    else if(card_color == COL_BLUE) bg=24;
    gfx_SetColor(bg);
    gfx_FillRectangle(174, 72, 32, 48);
    gfx_RLETSprite(cardgfx[game.board.top.value], 174, 72);
}

void uno_RenderBoard(void){
    uno_render_playerlist();
    uno_render_deckandtop();
}



void uno_ExecEffect(uint8_t effect){

}

void uno_SelectColor(void){
    ntwk_send(SELECT_COLOR, randInt(0,3));
}

void uno_alert(const char* string){
    strncpy(alert, string, 99);
    alert_up=200;
}

void uno_alert_render(void){
    if(alert_up--){
        uint8_t color=gfx_SetTextFGColor(96);
        gfx_BorderedWindow(100, 80, 120, 80, 64, 247);
        text_WrappedString(alert, 102, 82, 218);
        gfx_BlitRectangle(gfx_buffer, 98, 78, 124, 84);
    }
}

#define LINE_SPACING 10
uint8_t text_WrappedString(char *str, uint24_t left_margin, uint8_t top_margin, uint24_t right_margin){
    char *word = str;
    char *current = str;
    uint8_t lines = 1;

    gfx_SetTextXY(left_margin, top_margin);

    while(true) {
        uint8_t width = 0;
        for(; *current != ' ' && *current != 0; current++) {
            width += gfx_GetCharWidth(*current);
        }

        if(gfx_GetTextX() + width > right_margin) {
            gfx_SetTextXY(left_margin, gfx_GetTextY() + LINE_SPACING);
            lines++;
        }

        for(; word <= current; word++) {
            gfx_PrintChar(*word);
        }

        if(*current == 0) break;
        current++;
    }
    return lines;
}
