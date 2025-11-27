#include "input.h"
#include "player.h"
#include "common.h"


int get_sw(void) {
  volatile int* p = (volatile int*) 0x04000010;
  return *p & 0x7;
}

void handle_input(player_t *p) {
    switch(get_sw()) {
        case 0:
            p->base.req_dir = DIR_UP;
        break;

        case 1:
            p->base.req_dir = DIR_DOWN;
        break;

        case 2:
            p->base.req_dir = DIR_LEFT;
        break;

        case 3:
            p->base.req_dir = DIR_RIGHT;
        break;
    }
}