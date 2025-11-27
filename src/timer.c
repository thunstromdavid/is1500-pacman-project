#include "game.h"

// Here we have used code from the labs

int CLOCK_SPEED = 30000000; 
volatile int* timer = (volatile int*) 0x04000020;

void timer_init(int fps){
    int update = CLOCK_SPEED / fps;

    timer[2] = update & 0xFFFF; 
    timer[3] = update >> 16; 
    timer[1] = (3 << 1); 
}
int check_timer(void){
    if (timer[0] & 1) {
            timer[0] &= ~1;
                game_update();
        }
}