#include "input.h"
#include "player.h"
#include "common.h"


int get_sw(void) {
  volatile int* p = (volatile int*) 0x04000010;
  return *p & 0x7;
}

void handle_input(player_t *p) {
    switch(get_sw()) {
        case DIR_UP:
            p->req_dir = DIR_UP;
        break;

        case DIR_DOWN:
            p->req_dir = DIR_DOWN;
        break;

        case DIR_LEFT:
            p->req_dir = DIR_LEFT;
        break;

        case DIR_RIGHT:
            p->req_dir = DIR_RIGHT;
        break;
    }
}