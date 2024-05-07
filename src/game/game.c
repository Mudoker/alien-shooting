#include "../../header/game/game.h"

void gameCli() {
  framebf_init(GAME_WIDTH, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT, 0, 0);
  draw_center_button(100, "Start", 1);
  draw_center_button(400, "Exit", 0);
  // while (1) {
  //     char c = uart_getc();
  //     switch (c) {
  //         case 'w':
  //             break;
  //         case 's':
  //             break;
  //         case 'a':
  //             break;
  //         case 'd':
  //             break;
  //         default:
  //             break;
  //     }
  // }
}
