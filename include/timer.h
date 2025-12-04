#ifndef TIMER
#define TIMER

void timer_init(int fps);
int handle_interrupt(void);
int get_tick_count(void);
int get_time_seconds(void);
void reset_timer(void);

#endif