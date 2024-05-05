
#include "../header/uart.h"
#include "../header/video.h"
// #include "../header/text.h"

int main()
{
  uart_init(); // Initialize UART
  // load_image();
  // load_inf();
  video_mode();
  return 0;
}
