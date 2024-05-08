#include "../../header/game/game.h"

void gameCli() {
    framebf_init(GAME_WIDTH, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT, 0, 0);
    draw_center_button(100, "Start", 1);
    draw_center_button(540, "Exit", 0);
}

