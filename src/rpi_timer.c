#include "../header/rpi_timer.h"

unsigned int timer1_cmp = 0;
unsigned int timer1_period = TIMER_CLOCK / 2;
unsigned int timer3_cmp = 0;
unsigned int timer3_period = TIMER_CLOCK / 2;

void init_timer1() {
    // Set GPIO3 as output
    GPFSEL0 |= 1 << 9;

    timer1_cmp = TIMER_CLO + timer1_period;
    TIMER_C1 = timer1_cmp;
    TIMER_CS |= TIMER_CS_M1;
}

void handle_timer1() {
    timer1_cmp += timer1_period;
    TIMER_C1 = timer1_cmp;
    TIMER_CS |= TIMER_CS_M1;

    // Turn GPIO3 on and off
    if (GPLEV0 & (1 << 3)) {
        GPCLR0 |= 1 << 3;
    } else {
        GPSET0 |= 1 << 3;
    }
}

void init_timer3() {
    timer3_cmp = TIMER_CLO + timer3_period;
    TIMER_C3 = timer3_cmp;
    TIMER_CS |= TIMER_CS_M3;
}

void handle_timer3() {
    timer3_cmp += timer3_period;
    TIMER_C3 = timer3_cmp;
    TIMER_CS |= TIMER_CS_M3;

    // if (mode == GAME) {
    //     countdown();
    // }
}