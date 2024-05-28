
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
  init_sys_timer1();

  // load_image();
  // load_inf();
  // load_image();
  // load_inf();
  // video_mode();
  gameCli();

  return 0;
}
