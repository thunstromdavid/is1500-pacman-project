// Authored by David Thunström
// Date 2025-11-11

#ifndef GAME
#define GAME

typedef enum{
    GAME_STATE_INIT,
    GAME_STATE_PAUSE,
    GAME_STATE_RUNNING,
    GAME_STATE_GAME_OVER
} game_state_t;

void game_init(void);
void game_update(void);

#endif 