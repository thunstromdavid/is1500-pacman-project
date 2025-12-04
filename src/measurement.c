#include "dtekv-lib.h"
#include "timer.h"


void clear_counters() {
    // Clear Cycle and Instruction counters
    asm volatile ("csrw mcycle, x0");
    asm volatile ("csrw minstret, x0");

    // Clear Hardware Performance Monitor (HPM) counters
    asm volatile ("csrw mhpmcounter3, x0");
    asm volatile ("csrw mhpmcounter4, x0");
    asm volatile ("csrw mhpmcounter5, x0");
    asm volatile ("csrw mhpmcounter8, x0");
    asm volatile ("csrw mhpmcounter9, x0");
}

void read_and_print_counters() {
    unsigned int val;

    int time = get_time_seconds();
    print_dec(time);

 
    asm volatile ("csrr %0, mcycle" : "=r"(val));
    print("\n--- Performance Metrics ---\n");
    print("Total Cycles (Time): ");
    print_dec(val);

    asm volatile ("csrr %0, minstret" : "=r"(val));
    print("\nInstructions Retired: ");
    print_dec(val);

    asm volatile ("csrr %0, mhpmcounter3" : "=r"(val));
    print("\nHPM Counter 3: ");
    print_dec(val);

    asm volatile ("csrr %0, mhpmcounter4" : "=r"(val));
    print("\nHPM Counter 4: ");
    print_dec(val);

    asm volatile ("csrr %0, mhpmcounter5" : "=r"(val));
    print("\nHPM Counter 5: ");
    print_dec(val);

    asm volatile ("csrr %0, mhpmcounter8" : "=r"(val));
    print("\nHPM Counter 8: ");
    print_dec(val);

    asm volatile ("csrr %0, mhpmcounter9" : "=r"(val));
    print("\nHPM Counter 9: ");
    print_dec(val);
    
    print("\n---------------------------\n");
}