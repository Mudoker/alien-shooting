
#include "../../header/game/cgame.h"

void init_frame(int offset_x, int offset_y) {
  // Initialize buffer
  framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT,
               offset_x, offset_y);
}
