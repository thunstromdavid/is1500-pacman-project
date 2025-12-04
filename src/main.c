#include "graphics.h"
#include "gamemap.h"
#include "player.h"
#include "game.h"
#include "common.h"
#include "timer.h"
extern void print(const char*);
extern void print_dec(unsigned int);

int main() {
    vga_init();
    game_init();

    while(1) {
        game_update();
    }
}