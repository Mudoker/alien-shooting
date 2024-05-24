
#include "../../header/game/cgame.h"

void init_frame(int offset_x, int offset_y) {
  // Initialize buffer
  framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT,
               offset_x, offset_y);
}

// Initialize the spaceship object
void init_spaceship(GameController *game_controller,
                    const unsigned long *sprite, int width, int height, int x,
                    int y) {
  Spaceship spaceship;
  spaceship.name = "Blader";
  spaceship.size.width = width;
  spaceship.size.height = height;

  spaceship.position.x = x;
  spaceship.position.y = y;

  spaceship.sprite = sprite;

  game_controller->spaceship = spaceship;
}

// Draw the spaceship object
void draw_spaceship(Spaceship *spaceship) {
  draw_image(spaceship->position.x, spaceship->position.y,
             spaceship->size.width, spaceship->size.height, spaceship->sprite);
}

// Draw the background
void draw_background(const unsigned long *sprite) {
  draw_image(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, sprite);
}
