#include "game.h"
// Here we have used code from the labs

int CLOCK_SPEED = 30000000; 
volatile int* timer = (volatile int*) 0x04000020;

// Time tracking variables
static volatile int tick_count = 0;
static int ticks_per_second = 0;

extern void enable_interrupt(void);


void timer_init(int fps){
    int update = CLOCK_SPEED / fps;
    ticks_per_second = fps;
    tick_count = 0;

    timer[2] = update & 0xFFFF; 
    timer[3] = update >> 16; 
    timer[1] = 7; 
    enable_interrupt();
}


void handle_interrupt(void){
    // Check if timer triggered (bit 0 of timer status)
    if (timer[0] & 1) {
        timer[0] &= ~1; // Clear timer interrupt
        tick_count++;
        game_update();
    }
}

// Get elapsed time in ticks
int get_tick_count(void) {
    return tick_count;
}

// Get elapsed time in seconds
int get_time_seconds(void) {
    return tick_count / ticks_per_second;
}

// Reset timer
void reset_timer(void) {
    tick_count = 0;
}

