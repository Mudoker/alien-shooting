
#include "../header/uart.h"
#include "../header/video.h"
#include "../header/game/game.h"
#include "../header/image.h"
#include "../header/text.h"
#include "../header/timer.h"
#include "../header/interrupt.h"

int main()
{
  uart_init(); // Initialize UART
  irq_init();  // Initialize interrupts
  init_timer1();

  // load_image();
  // load_inf();
  // load_image();
  // load_inf();
  // video_mode();
  gameCli();

  return 0;
}
