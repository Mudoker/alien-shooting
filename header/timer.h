#ifndef TIMER_H
#define TIMER_H

#include "gpio.h"

// Base MMIO address
#define MMIO_BASE 0x3F000000

// System timer base address
#define TIMER_BASE (MMIO_BASE + 0x3000)

// System timer registers
#define TIMER_CS (*(volatile unsigned int *)(TIMER_BASE + 0x00))
#define TIMER_CLO (*(volatile unsigned int *)(TIMER_BASE + 0x04))
#define TIMER_CHI (*(volatile unsigned int *)(TIMER_BASE + 0x08))
#define TIMER_C0 (*(volatile unsigned int *)(TIMER_BASE + 0x0C))
#define TIMER_C1 (*(volatile unsigned int *)(TIMER_BASE + 0x10))
#define TIMER_C2 (*(volatile unsigned int *)(TIMER_BASE + 0x14))
#define TIMER_C3 (*(volatile unsigned int *)(TIMER_BASE + 0x18))

// Timer control bits
#define TIMER_CS_MATCH_1 (1 << 1)
#define TIMER_CS_MATCH_3 (1 << 3)
#define TIMER_CLOCK_HZ 1000000

// Timer initialization
void init_sys_timer1();
void init_sys_timer3();

// Timer IRQ handlers
void handle_sys_timer1();
void handle_sys_timer3();

// Timer functions
void wait_msec(unsigned int n);
void set_wait_timer(int set, unsigned int msVal);

#endif
