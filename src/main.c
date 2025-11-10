#include <stdlib.h>
#include "graphics.h"
#include "gamemap.h"
#include "player.h"

int main() {
    vga_init();

    set_gamemap();

    while (1) {
        player_render();
    }
}