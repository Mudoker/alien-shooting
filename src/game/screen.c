#include "../../header/game/screen.h"

void in_game_screen(GameController *game_controller) {
    // Initialize the spaceship object
    init_spaceship(game_controller);

    while (1) {
        char c = uart_getc();
        switch (c) {
            case 'w':
                move_spaceship(game_controller, 0, -1);
                break;
            case 's':
                move_spaceship(game_controller, 0, 1);
                break;
            case 'a':
                move_spaceship(game_controller, -1, 0);
                break;
            case 'd':
                move_spaceship(game_controller, 1, 0);
                break;
            default:
                break;
        }
    }
}