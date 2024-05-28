#ifndef RPI_TIMER_H
#define RPI_TIMER_H

#include "gpio.h"

// System timer control for both RPI3 and RPI4
#define TIMER_BASE MMIO_BASE + 0x3000
#define TIMER_CS (*(volatile unsigned int *)(TIMER_BASE + 0x00))
#define TIMER_CLO (*(volatile unsigned int *)(TIMER_BASE + 0x04))
#define TIMER_CHI (*(volatile unsigned int *)(TIMER_BASE + 0x08))
#define TIMER_C0 (*(volatile unsigned int *)(TIMER_BASE + 0x0C))
#define TIMER_C1 (*(volatile unsigned int *)(TIMER_BASE + 0x10))
#define TIMER_C2 (*(volatile unsigned int *)(TIMER_BASE + 0x14))
#define TIMER_C3 (*(volatile unsigned int *)(TIMER_BASE + 0x18))

#define TIMER_CS_M1    (1 << 1)
#define TIMER_CS_M3    (1 << 3)
#define TIMER_CLOCK    1000000

void init_timer1();
void init_timer3();
void handle_timer1();
void handle_timer3();

#endif