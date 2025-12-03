// Optional printing functions may use ecall and can trap; avoid for now
// extern void print(const char *str);
// extern void print_dec(int val);
// Use 7-seg display for non-blocking output instead

// Baseline snapshot of user-accessible counters
static unsigned int cycle_base = 0;
static unsigned int instret_base = 0;

// Clear by taking a baseline snapshot using readable CSRs
void clear_counters() {
    asm volatile ("csrr %0, cycle" : "=r"(cycle_base));
    asm volatile ("csrr %0, instret" : "=r"(instret_base));
}

void read_and_print_counters() {
    unsigned int now_cycle = 0;
    unsigned int now_instret = 0;

    // Read user-accessible counters
    asm volatile ("csrr %0, cycle" : "=r"(now_cycle));
    asm volatile ("csrr %0, instret" : "=r"(now_instret));

    // Compute deltas since last clear
    unsigned int cycles = now_cycle - cycle_base;
    unsigned int instret = now_instret - instret_base;


}