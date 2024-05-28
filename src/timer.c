#include "../header/timer.h"

volatile unsigned long system_millis = 0;

// Function to get the current time in milliseconds
unsigned long get_time_ms() { return system_millis; }

void init_sys_timer1() {
  // Set GPIO3 as output
  GPFSEL0 |= (1 << 9);

  // Calculate timer period for 0.5 second
  unsigned int timer1_period = TIMER_CLOCK_HZ / 2;

  // Set timer compare register for system timer 1
  TIMER_C1 = TIMER_CLO + timer1_period;

  // Enable match 1 interrupt
  TIMER_CS |= TIMER_CS_MATCH_1;
}

void handle_sys_timer1() {
  TIMER_C1 += TIMER_CLOCK_HZ / 2;
  TIMER_CS |= TIMER_CS_MATCH_1;

  // Toggle GPIO3
  GPSET0 ^= (1 << 3);
}

void init_sys_timer3() {
  unsigned int timer3_period = TIMER_CLOCK_HZ / 2;
  unsigned int timer3_cmp = TIMER_CLO + timer3_period;
  TIMER_C3 = timer3_cmp;
  TIMER_CS |= TIMER_CS_MATCH_3;
}

void handle_sys_timer3() {
  unsigned int timer3_period = TIMER_CLOCK_HZ / 2;
  unsigned int timer3_cmp = TIMER_C3 + timer3_period;
  TIMER_C3 = timer3_cmp;
  TIMER_CS |= TIMER_CS_MATCH_3;

  // Additional logic can be added here if required
}

void wait_msec(unsigned int n) {
  unsigned long start_time = TIMER_CLO;
  unsigned long end_time = start_time + n * (TIMER_CLOCK_HZ / 1000);

  while (TIMER_CLO < end_time) {
    // Wait until the specified time has elapsed
  }
}

void set_wait_timer(int set, unsigned int msVal) {
  static unsigned long expiredTime = 0; // Static to retain value
  if (set) {                            // SET TIMER
    expiredTime = TIMER_CLO + msVal * (TIMER_CLOCK_HZ / 1000);
  } else { // WAIT FOR TIMER TO EXPIRE
    while (TIMER_CLO < expiredTime) {
      // Wait until the timer has expired
    }
  }
}
