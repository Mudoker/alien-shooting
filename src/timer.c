#include "../header/timer.h"
#include "../header/uart.h"

volatile unsigned long system_millis = 0;
volatile int countdown = COUNTDOWN;

// Function to get the current time in milliseconds
unsigned long get_time_ms() { return system_millis; }

void init_system_timer() {
  // Set GPIO3 as output
  GPFSEL0 |= (1 << 9);

  // Calculate timer period for 1 second
  unsigned int timer1_period = TIMER_CLOCK_HZ;

  // Load the period into the compare register
  TIMER_C1 = TIMER_CLO + timer1_period;

  // Enable match 1 interrupt
  TIMER_CS |= TIMER_CS_MATCH;
}

int handle_system_timer() {
  // Clear the match 1 interrupt flag
  TIMER_CS |= TIMER_CS_MATCH;

  // Increment the system timer
  TIMER_C1 += TIMER_CLOCK_HZ;

  // Decrement countdown
  if (countdown > 0) {
    countdown--;
    uart_puts(WHITE);
    uart_puts("COUNTDOWN: ");
    uart_dec(countdown);
    uart_puts("\n");

    if (countdown == 0) {
      return 0;
    }
  }

  // Toggle GPIO3
  GPSET0 ^= (1 << 3);

  return 1;
}

void wait_msec(unsigned int n) {
  register unsigned long f, t, r, expiredTime;
  // Get the current counter frequency (Hz)
  asm volatile("mrs %0, cntfrq_el0" : "=r"(f));
  // Read the current counter value
  asm volatile("mrs %0, cntpct_el0" : "=r"(t));
  // Calculate expire value for counter
  expiredTime = t + ((f / 1000) * n) / 1000;
  do {
    asm volatile("mrs %0, cntpct_el0" : "=r"(r));
  } while (r < expiredTime);
}

void set_wait_timer(int set, unsigned int msVal) {
  // Set the timer to expire in msVal milliseconds
  static unsigned long expiredTime = 0;

  // If set is true, set the timer
  if (set) {
    expiredTime = TIMER_CLO + msVal * (TIMER_CLOCK_HZ / 1000);
  } else {
    while (TIMER_CLO < expiredTime) {
      // Wait until the timer has expired
    }
  }
}
