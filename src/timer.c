#include "game.h"
// Here we have used code from the labs

int CLOCK_SPEED = 3000000; 
volatile int* timer = (volatile int*) 0x04000020;

extern void enable_interrupt(void);


void timer_init(int fps){
    int update = CLOCK_SPEED / fps;

    timer[2] = update & 0xFFFF; 
    timer[3] = update >> 16; 
    timer[1] = 7; 
    enable_interrupt();
}


void interrupt_handler(int mepc, int mcause){
    // Check if timer triggered (bit 0 of timer status)
    if (timer[0] & 1) {
        timer[0] &= ~1; // Clear timer interrupt
        game_update();
    }
}

