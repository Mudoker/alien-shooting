
#include "../../header/game/cgame.h"
#include "../../assets/games/bullet/bullet_lv1.h"
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
  spaceship.previous_position = spaceship.position;

  spaceship.sprite = sprite;

  game_controller->spaceship = spaceship;
}

void init_bullet(GameController *game_controller, const unsigned long *sprite,
                 int width, int height, int x, int y) {
  Bullet bullet;
  bullet.name = "Bullet";
  bullet.size.width = width;
  bullet.size.height = height;

  bullet.position.x = x;
  bullet.position.y = y;
  bullet.previous_position = bullet.position;

  bullet.sprite = sprite;

  game_controller->spaceship.bullet[0] = bullet;
  game_controller->bullet_on_screen_count = 1;
}

void draw_spaceship(Spaceship *spaceship) {
  draw_image(spaceship->position.x, spaceship->position.y,
             spaceship->size.width, spaceship->size.height, spaceship->sprite);
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

void restore_background(int x, int y, int w, int h,
                        const unsigned long *background) {
  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      // Ensure we don't go out of the bounds of the screen
      if (x + i >= 0 && x + i < SCREEN_WIDTH && y + j >= 0 &&
          y + j < SCREEN_HEIGHT) {
        unsigned long pixel = background[(y + j) * SCREEN_WIDTH + (x + i)];
        draw_pixelARGB32(x + i, y + j, pixel);
      }
    }
  }
}

void render_sprite(int current_x, int current_y, int previous_x, int previous_y,
                   int width, int height, const unsigned long *sprite,
                   const unsigned long *background) {
  // Restore the background at the previous position
  restore_background(previous_x, previous_y, width, height, background);

  // Draw the spaceship at the new position
  draw_image(current_x, current_y, width, height, sprite);
}

// Draw the background
void draw_background(const unsigned long *sprite) {
  draw_image(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, sprite);
}

void move_spaceship(GameController *game_controller, int key, int step,
                    const unsigned long *epd_bitmap_background) {
  Spaceship *spaceship = &game_controller->spaceship;

  // Calculate potential new position
  int newX = spaceship->position.x;
  int newY = spaceship->position.y;

  switch (key) {
  case KEY_RIGHT:
    newX += step;
    break;
  case KEY_LEFT:
    newX -= step;
    break;
  case KEY_UP:
    newY -= step;
    break;
  case KEY_DOWN:
    newY += step;
    break;
  default:
    break;
  }

  // Calculate boundary limits
  int maxX = SCREEN_WIDTH - spaceship->size.width;
  int maxY = SCREEN_HEIGHT - spaceship->size.height;

  // Clamp position to stay within boundaries
  spaceship->position.x = (newX < 0) ? 0 : (newX > maxX) ? maxX : newX;
  spaceship->position.y = (newY < 0) ? 0 : (newY > maxY) ? maxY : newY;

  // Draw the spaceship at the new position
  render_sprite(spaceship->position.x, spaceship->position.y,
                spaceship->previous_position.x, spaceship->previous_position.y,
                spaceship->size.width, spaceship->size.height,
                spaceship->sprite, epd_bitmap_background);

  // Update the previous position
  spaceship->previous_position = spaceship->position;
}

// ALways go vertically up
void move_bullet(Bullet *bullet, int step,
                 const unsigned long *epd_bitmap_background) {

  // Calculate potential new position
  int newY = bullet->position.y - step;

  // Clamp position to stay within boundaries
  bullet->position.y = newY;

  // Draw the bullet at the new position
  render_sprite(bullet->position.x, bullet->position.y,
                bullet->previous_position.x, bullet->previous_position.y,
                bullet->size.width, bullet->size.height, bullet->sprite,
                epd_bitmap_background);

  // Update the previous position
  bullet->previous_position = bullet->position;

  if (bullet->position.y <= -bullet->size.height) {
    bullet->name = NULL;
  }
}

void add_bullet(GameController *game_controller, int x, int y) {
  // Get the total number of bullets on the screen
  int bullet_count = game_controller->bullet_on_screen_count;

  // Add a new bullet to the screen
  if (bullet_count < MAX_BULLETS) {
    Bullet bullet;
    bullet.name = "Bullet";
    bullet.size.width = 12;
    bullet.size.height = 48;

    bullet.position.x = x;
    bullet.position.y = y;
    bullet.previous_position = bullet.position;

    bullet.sprite = epd_bullet_lv1[0];

    game_controller->spaceship.bullet[bullet_count] = bullet;
    game_controller->bullet_on_screen_count++;
  }
}

void init_controller(GameController *game_controller) {
  game_controller->screen = &((Display){.init_frame = &init_frame});
  game_controller->screen->init_frame(0, 0);
  game_controller->page = IN_GAME;
  game_controller->bullet_on_screen_count = 0;

  init_stages(game_controller);
  init_spaceship(game_controller, epd_blader[0], 124, 128,
                 (SCREEN_WIDTH - 124) / 2, SCREEN_HEIGHT - 128);
  init_bullet(game_controller, epd_bullet_lv1[0], 12, 48,
              game_controller->spaceship.position.x + 124 / 2 - 6,
              game_controller->spaceship.position.y - 20);
}
