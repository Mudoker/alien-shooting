#include "randomNum.h"

unsigned long lcg_seed = 1;  // Do not use zero, choose an appropriate initial seed
void init_seed() {
    register unsigned long current_counter;
    // Read the current counter value
    asm volatile("mrs %0, cntpct_el0" : "=r"(current_counter));
    // Set the seed with the current counter value
    lcg_seed = current_counter;
}

// LCG function to generate a pseudo-random number
unsigned long randomNum() {
    
    unsigned long a = 16807;  // Multiplier
    unsigned long m = 2147483647;  // Modulus (2^31 - 1)

    lcg_seed = (lcg_seed * a) % m;
    return lcg_seed;
}