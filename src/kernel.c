
#include "../header/uart.h"
#include "../header/video.h"
// #include "../header/game/data/data_process.h"
// #include "../header/text.h"
<<<<<<< HEAD
#include "../header/game/game.h"
=======
#include "../header/image.h"
>>>>>>> c2a9ef7bb1c0ac32cfb23b8345cd3dc1f21e8e50

int main()
{
  uart_init(); // Initialize UART
  load_image();
  // load_inf();
  // video_mode();
<<<<<<< HEAD
  gameCli();

=======
>>>>>>> c2a9ef7bb1c0ac32cfb23b8345cd3dc1f21e8e50
  return 0;
}

