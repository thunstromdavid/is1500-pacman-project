// Authored by David Thunström
// Date 2025-12-05

#ifndef TIMER
#define TIMER

#define CLOCK_SPEED 30000000
#define NUMB_TICKS 1000

void timer_init(int fps);
void handle_interrupt(void);
int get_tick_count(void);
int get_time_seconds(void);
void reset_timer(void);

#endif