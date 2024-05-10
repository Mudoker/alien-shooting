#include "../../header/game/game_controller.h"
#include "headers/game_struct.h"
#include "../../header/global.h"
#include "../../assets/games/spaceship/blader.h"
#include "../../header/framebf.h"

void init_spaceship(GameController *game_controller) {
    Spaceship your_spaceship;
    
    your_spaceship.position.x = (SCREEN_WIDTH - your_spaceship.size.width) / 2;
    your_spaceship.position.y = SCREEN_HEIGHT - your_spaceship.size.height;
    your_spaceship.size.width = 124;
    your_spaceship.size.height = 128;
    your_spaceship.sprite = epd_bitmap_spaceship_allArray[0];

    game_controller->spaceship = your_spaceship;
    //draw_image(your_spaceship.position.x, your_spaceship.position.y, your_spaceship.size.width, your_spaceship.size.height, your_spaceship.sprite);
}