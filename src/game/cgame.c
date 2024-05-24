
#include "../../header/game/cgame.h"
#include "../../assets/games/spaceship/blader.h"

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

// Init stage
void init_stages(GameController *game_controller) {
  game_controller->stages[0].name = "Stage 1";
  game_controller->stages[0].level = STAGE_1;
  game_controller->stages[1].name = "Stage 2";
  game_controller->stages[1].level = STAGE_2;
  game_controller->stages[2].name = "Stage 3";
  game_controller->stages[2].level = STAGE_3;
  game_controller->stages[3].name = "Stage 4";
  game_controller->stages[3].level = STAGE_4;
  game_controller->stages[4].name = "Stage 5";
  game_controller->stages[4].level = STAGE_5;
  game_controller->stages[5].name = "Stage 6";
  game_controller->stages[5].level = STAGE_6;
  game_controller->stages[6].name = "Stage 7";
  game_controller->stages[6].level = STAGE_7;
  game_controller->stages[7].name = "Stage 8";
  game_controller->stages[7].level = STAGE_8;
  game_controller->stages[8].name = "Stage 9";
  game_controller->stages[8].level = STAGE_9;

  game_controller->stage_level = 1;
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

void init_controller(GameController *game_controller) {
  game_controller->screen = &((Display){.init_frame = &init_frame});
  game_controller->screen->init_frame(0, 0);
  game_controller->page = STAGE;

  init_stages(game_controller);
  init_spaceship(game_controller, epd_blader[0], 124, 128, 0, 0);
}
