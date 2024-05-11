#include "../../header/game/game_controller.h"
#include "../../assets/games/spaceship/blader.h"

// Initialize the spaceship object
void init_spaceship(GameController *game_controller) {
    Spaceship your_spaceship;
    your_spaceship.size.width = 124;
    your_spaceship.size.height = 128;
    your_spaceship.position.x = (SCREEN_WIDTH - your_spaceship.size.width) / 2;
    your_spaceship.position.y = SCREEN_HEIGHT - your_spaceship.size.height;

    your_spaceship.sprite = epd_bitmap_spaceship_allArray[0];

    game_controller->spaceship = your_spaceship;
    draw_spaceship(game_controller);
}

// Draw the spaceship on the screen
void draw_spaceship(GameController *game_controller) {
    draw_image(game_controller->spaceship.position.x, game_controller->spaceship.position.y, game_controller->spaceship.size.width, game_controller->spaceship.size.height, game_controller->spaceship.sprite);
}


void move_spaceship(GameController *game_controller, int x_dir, int y_dir) {
    Spaceship *spaceship = &game_controller->spaceship;
    clear_image(spaceship->position.x, spaceship->position.y, spaceship->size.width, spaceship->size.height);

    if (spaceship->position.x + x_dir * 5 >= 0 &&
        spaceship->position.x + x_dir * 5 <= SCREEN_WIDTH - spaceship->size.width) {
        spaceship->position.x += x_dir * 5;
    }

    if (spaceship->position.y + y_dir * 5 >= 0 &&
        spaceship->position.y + y_dir * 5 <= SCREEN_HEIGHT - spaceship->size.height) {
        spaceship->position.y += y_dir * 5;
    }

    draw_spaceship(game_controller);
}