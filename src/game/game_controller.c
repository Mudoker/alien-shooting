#include "../../header/game/game_controller.h"
#include "../../assets/games/spaceship/blader.h"
#include "../../assets/games/bullet/bullet_lv1.h"

// Initialize the spaceship object
void init_spaceship(GameController *game_controller) {
    Spaceship your_spaceship;

    // Spaceship's size 
    your_spaceship.size.width = 124;
    your_spaceship.size.height = 128;

    // Initial position of the spaceship
    your_spaceship.position.x = (SCREEN_WIDTH - your_spaceship.size.width) / 2;
    your_spaceship.position.y = SCREEN_HEIGHT - your_spaceship.size.height;

    // Image of the spaceship
    your_spaceship.sprite = epd_bitmap_spaceship_allArray[0];
    game_controller->spaceship = your_spaceship;

    draw_spaceship(game_controller);
}

void init_bullet(GameController *game_controller) {
    Bullet bullet;
    bullet.position.x = game_controller->spaceship.position.x + (game_controller->spaceship.size.width - 12) / 2;
    bullet.position.y = game_controller->spaceship.position.y - 48 - 20;
    bullet.sprite = epd_bitmap_bullet_allArray[0];
    game_controller->spaceship.bullet = bullet;
    draw_bullet(game_controller);
}
// Draw the spaceship on the screen
void draw_spaceship(GameController *game_controller) {
    draw_image(game_controller->spaceship.position.x, game_controller->spaceship.position.y, game_controller->spaceship.size.width, game_controller->spaceship.size.height, game_controller->spaceship.sprite);
}

// Draw the bullet on the screen
void draw_bullet(GameController *game_controller) {
    draw_image(game_controller->spaceship.bullet.position.x, game_controller->spaceship.bullet.position.y, 12, 48, game_controller->spaceship.bullet.sprite);
}

void move_spaceship(GameController *game_controller, int x_dir, int y_dir) {
    Spaceship *spaceship = &game_controller->spaceship;
    clear_image(spaceship->position.x, spaceship->position.y, spaceship->size.width, spaceship->size.height);

    if (spaceship->position.x + x_dir * STEP >= 0 &&
        spaceship->position.x + x_dir * STEP <= SCREEN_WIDTH - spaceship->size.width) {
        spaceship->position.x += x_dir * STEP;
    }

    if (spaceship->position.y + y_dir * STEP >= 0 &&
        spaceship->position.y + y_dir * STEP <= SCREEN_HEIGHT - spaceship->size.height) {
        spaceship->position.y += y_dir * STEP;
    }

    draw_spaceship(game_controller);
}

void move_bullet(GameController *game_controller, int x_dir, int y_dir) {
    Spaceship *spaceship = &game_controller->spaceship;
    Bullet *bullet = &spaceship->bullet;
    clear_image(bullet->position.x, bullet->position.y, 12, 48);

    if (bullet->position.x + x_dir * STEP >= 0 &&
        bullet->position.x + x_dir * STEP <= SCREEN_WIDTH - 12) {
        bullet->position.x += x_dir * STEP;
    }

    if (bullet->position.y + y_dir * STEP >= 0 &&
        bullet->position.y + y_dir * STEP <= SCREEN_HEIGHT - 48) {
        bullet->position.y += y_dir * STEP;
    }

    draw_bullet(game_controller);
    wait_msec(8000);
}