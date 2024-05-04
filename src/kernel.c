#include "../header/image.h"
#include "../header/game/game.h"

int main() {
  uart_init(); // Initialize UART
  imageCli();
  //gameCli();
  return 0;
}