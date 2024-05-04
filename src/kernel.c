#include "../header/image.h"

int main() {
  uart_init(); // Initialize UART
  load_image();
  return 0;
}