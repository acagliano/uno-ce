#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "network.h"
#include "controlcodes.h"
#include "uno.h"

typedef struct _lobby_players {
    uint8_t id;
    uint8_t status;
} lobby_players_t;

void conn_HandleInput(packet_t *in_buff, size_t buff_size) {
    uint8_t ctl = in_buff->control;
    uint8_t response = in_buff->data[0];    // for handlers needing only response codes
    uint8_t* data = &in_buff->data[0];      // for handlers needing arbitrary data
    
    switch(ctl){
        case LOBBY_INFO:
            {
                struct {
                    uint8_t lobby_count;
                    uint8_t game_available;
                } *packet = (void*)data;
                game.status=IN_LOBBY;
                game.game_available=packet->game_available;
                game.lobby_count=packet->lobby_count;
                uno_RenderLobby();
                break;
            }
        case REFRESH_HAND:
            {
                struct {
                    uint8_t card_count;
                    card_t card[1];
                } *packet = (void*)data;
                memset(game.hand, VAL_NULL, sizeof(game.hand));
                if((packet->card_count * sizeof(card_t)) > sizeof(game.hand))
                    game.hand=realloc(game.hand, packet->card_count * sizeof(card_t));
                memcpy(game.hand, packet->card, packet->card_count * sizeof(card_t));
                uno_RenderHand();
                break;
            }
        case REFRESH_BOARD:
            memcpy(&game.board, data, buff_size-1);
            uno_RenderBoard();
            break;
        case EFFECT:
            uno_ExecEffect(response);
        case START_TURN:
            game.my_turn=true;
            break;
        case END_TURN:
            game.my_turn=false;
            break;
        case MSG:
            uno_alert(data);
            break;
        case SELECT_COLOR:
            uno_SelectColor();
            break;
        case JOIN:
            switch(response){
                case SUCCESS:
                    uno_alert("You have joined the game!");
                    break;
                case NO_GAME_FOUND:
                    uno_alert("There is no game to join!");
                    break;
                case GAME_IN_PROGRESS:
                    uno_alert("There is a game in progress. Please wait!");
                    break;
                case PLAYER_LIMIT:
                    uno_alert("The game is at limit. Try again later.");
                    break;
            }
            break;
    }
}


