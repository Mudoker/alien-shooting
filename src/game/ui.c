#include "../../header/game/ui.h"
#include "../../header/game/game.h"

void draw_button(int x, int y, char *text, int selected) {
    drawRectARGB32(x, y, x + BUTTON_WIDTH, y + BUTTON_HEIGHT, 0x00AA0000, 1);
}


void draw_center_button(int y, char *text, int selected) {
    draw_button((GAME_WIDTH - BUTTON_WIDTH) / 2, y, text, selected);
}
