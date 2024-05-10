#include "../../header/game/game_controller.h"
#include "headers/game_struct.h"
#include "../../header/global.h"
#include "../../assets/games/spaceship/blader.h"
#include "../../header/framebf.h"

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