#include "input.h"
#include "player.h"
#include "common.h"

player_t player;

int get_sw(void) {
  volatile int* p = (volatile int*) 0x04000010;
  return *p & 0x7;
}

handle_input() {
    switch(get_sw) {
        case DIR_UP:
            player_update(&player, DIR_UP);
        break;

        case DIR_DOWN:
            player_update(&player, DIR_DOWN);
        break;

        case DIR_LEFT:
            player_update(&player, DIR_LEFT);
        break;

        case DIR_RIGHT:
            player_update(&player, DIR_RIGHT);
        break;
    }

}