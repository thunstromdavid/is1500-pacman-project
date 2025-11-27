#include <stdlib.h>
#include "graphics.h"
#include "gamemap.h"
#include "player.h"
#include "game.h"
#include "common.h"
#include "timer.h"

int main() {
    volatile int* status = (volatile int*) 0x04000020;
    vga_init();

    game_init();

    while (1) {
        check_timer();
    }
}