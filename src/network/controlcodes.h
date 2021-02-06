#ifndef controlcodes_h
#define controlcodes_h

enum ControlCodes {
    
    CONNECT,
    DISCONNECT,
    
    JOIN,
    DRAW,
    PLAY,
    CHALLENGE,
    SELECT_COLOR,
    REFRESH_HAND,
    REFRESH_BOARD,
    WINNER,
    MSG,
    START_TURN,
    EFFECT,
    END_TURN,
    LOBBY_INFO,
       
    // DEBUG: 0xf*
    BRIDGE_ERROR = 0xf0,
    PING = 0xfc,
};

//returned from some routines
enum _player_status {
    IN_LOBBY,
    WAITING,
    IN_GAME
};

enum _error_codes {
    SUCCESS,
    NO_GAME_FOUND,
    GAME_IN_PROGRESS,
    PLAYER_LIMIT
};


#endif
