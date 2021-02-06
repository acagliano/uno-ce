#ifndef uno_h
#define uno_h

#include <stdbool.h>
#define OFFLINE 0
#define IN_LOBBY 1
#define WAITING 2
#define PLAYING 3

typedef struct _card {
    uint8_t value;
    uint8_t color;
} card_t;

typedef struct _player {
    uint8_t num;
    uint8_t card_count;
} player_t;

typedef struct _board {
    uint8_t player_ct;
    uint8_t turn;
    uint8_t direction;
    card_t top;
    player_t playerinfo[8];
} board_t;

typedef struct _gamedata {
    uint8_t status;
    bool game_available;
    bool my_turn;
    board_t board;
    uint8_t lobby_count;
    card_t* hand;
} gamedata_t;

extern char alert[100];
extern char alert_up;

enum CardValues {
    VAL_ZERO,
    VAL_ONE,
    VAL_TWO,
    VAL_THREE,
    VAL_FOUR,
    VAL_FIVE,
    VAL_SIX,
    VAL_ZEVEN,
    VAL_EIGHT,
    VAL_NINE,
    VAL_SKIP,
    VAL_REVERSE,
    VAL_WILD,
    VAL_DRAW2,
    VAL_WILDDRAW4,
    VAL_NULL = 0xff
};

enum CardColors {
    COL_BLUE,
    COL_GREEN,
    COL_RED,
    COL_YELLOW
};


void uno_onlineplay(void);
void uno_soloplay(void);

void uno_RenderLobby(void);
void uno_RenderHand(void);
void uno_ExecEffect(uint8_t effect);
void uno_SelectColor(void);

void uno_alert(const char* string);

uint8_t text_WrappedString(char *str, uint24_t left_margin, uint8_t top_margin, uint24_t right_margin);

extern gamedata_t game;
extern bool game_available;
extern uint8_t lobby_count;

#endif
