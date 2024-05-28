#ifndef TIMER_H
#define TIMER_H

#include "gpio.h"
#include "global.h"

// Base MMIO address
#define MMIO_BASE 0x3F000000

// System timer base address
#define TIMER_BASE (MMIO_BASE + 0x3000)

// System timer registers
#define TIMER_CS (*(volatile unsigned int *)(TIMER_BASE + 0x00))
#define TIMER_CLO (*(volatile unsigned int *)(TIMER_BASE + 0x04))
#define TIMER_CHI (*(volatile unsigned int *)(TIMER_BASE + 0x08))
#define TIMER_C1 (*(volatile unsigned int *)(TIMER_BASE + 0x10))

// Timer control bits
#define TIMER_CS_MATCH (1 << 1)
#define TIMER_CLOCK_HZ 1000000

extern volatile int countdown;

// Timer initialization
void init_system_timer();

// Timer IRQ handlers
int handle_system_timer();

// Timer functions
void wait_msec(unsigned int n);
void set_wait_timer(int set, unsigned int msVal);

#endif
