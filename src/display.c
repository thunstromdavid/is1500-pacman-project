// Authored by Mathias Jonasson and David Thunström
// Date 2025-12-02
#include "display.h"

char binary_value[] = {
  0b01000000,
  0b01111001,
  0b00100100,
  0b00110000,
  0b00011001,
  0b00010010,
  0b00000010,
  0b01111000,
  0b00000000,
  0b00011000,
};

void set_displays(int display_number, int value) {
  volatile int* p = (volatile int*) (0x04000050 + display_number * 0x10);
  *p = binary_value[value];
}

int math_pow(int base, int exp) {
    int result = 1;
    
    for (int i = 0; i < exp; i++) {
        result = result * base;
    }
    
    return result;
}

void set_score_on_display(int score) {
    for(int i = 0; i < 6; i++) {
        int divider = math_pow(10, i);
        int digit = (score / divider) % 10;
        set_displays(i, digit);
    }
}