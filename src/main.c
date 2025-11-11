#include <stdlib.h>
#include "graphics.h"
#include "gamemap.h"
#include "player.h"
#include "game.h"

int main() {
    vga_init();

    game_init();

    while (1) {
        game_update();
    }
}