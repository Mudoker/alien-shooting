#include "../../header/game/ui.h"
// #include "../../header/game/game.h"

void draw_button(int x, int y, int w, int h, char *text, int selected) {
    if (selected == 0) {
        // If not selected, draw a gray button
        draw_rectARGB32(x, y, x + w, y + h, 0x00AAAAAA, 1);
    } else {
        draw_rectARGB32(x, y, x + w, y + h, 0x00AA0000, 1);
    }
    draw_stringARGB32(x + w / 2 - 4 * len(text), y + h / 2 - 4, text, 0xFFFFFFFF);
}

