
#include "../header/uart.h"
#include "../header/video.h"
// #include "../header/game/data/data_process.h"
#include "../header/text.h"
#include "../header/image.h"
#include "../header/game/game.h"

int main()
{
  uart_init(); // Initialize UART
  //load_image();
  //load_inf();
  //video_mode();
  gameCli();

  return 0;
}

