
#include "../header/game/game.h"
#include "../header/image.h"
#include "../header/interrupt.h"
#include "../header/text.h"
#include "../header/timer.h"
#include "../header/uart.h"
#include "../header/video.h"

int main() {
  uart_init();       // Initialize UART
  init_interrupts(); // Initialize interrupts

  while (1) {
    handle_irq_elx(); // Handle pending interrupts
  }

  return 0;
}
