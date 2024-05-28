#include "../header/timer.h"
#include "../header/uart.h"

volatile unsigned long system_millis = 0;
volatile int countdown = 60;

// Function to get the current time in milliseconds
unsigned long get_time_ms() { return system_millis; }

void init_system_timer() {
  // Set GPIO3 as output
  GPFSEL0 |= (1 << 9);

  // Calculate timer period for 1 second
  unsigned int timer1_period = TIMER_CLOCK_HZ;

  // Set timer compare register for system timer 1
  TIMER_C1 = TIMER_CLO + timer1_period;

  // Enable match 1 interrupt
  TIMER_CS |= TIMER_CS_MATCH_1;
}

void handle_system_timer() {
  // Clear the match 1 interrupt flag
  TIMER_CS |= TIMER_CS_MATCH_1;
  TIMER_C1 += TIMER_CLOCK_HZ; // Add one second to the compare value

  // Decrement countdown
  if (countdown > 0) {
    countdown--;
    uart_puts("Countdown: ");
    uart_dec(countdown);
    uart_puts("\n");
  } else {
    // uart_puts("Countdown complete!\n");

    // Stop interrupts
    return;
  }

  // Toggle GPIO3
  GPSET0 ^= (1 << 3);
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
