#include "../../header/game/ui.h"
#include "../../header/game/game.h"

void draw_button(int x, int y, char *text, int selected) {
    draw_rectARGB32(x, y, x + BUTTON_WIDTH, y + BUTTON_HEIGHT, 0x00AA0000, 1);
}

