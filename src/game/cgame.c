
#include "../../header/game/cgame.h"
#include "../../assets/games/alient/alient_1.h"
#include "../../assets/games/background.h"
#include "../../assets/games/bullet/bullet_lv1.h"
#include "../../assets/games/health_logo.h"
#include "../../assets/games/spaceship/blader.h"
#include "../../assets/games/welcome_screen/welcome.h"

#define BUlLET_WIDTH 17
#define BULLET_HEIGHT 52

void calculate_bullet_positions(GameController *game_controller,
                                int positions[][2], int *num_positions);

void init_frame(int offset_x, int offset_y) {
  // Initialize buffer
  framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT,
               offset_x, offset_y);
}

void init_controller(GameController *game_controller) {
  game_controller->screen = &((Display){.init_frame = &init_frame});
  game_controller->screen->init_frame(0, 0);
  game_controller->page = IN_GAME;
  game_controller->bullet_on_screen_count = 0;

  int positions[5][2]; // Maximum of MAX_BULLETS positions
  int num_positions;

  init_stages(game_controller);
  init_spaceship(game_controller, epd_blader[0], 124, 128,
                 (SCREEN_WIDTH - 124) / 2, SCREEN_HEIGHT - 128);

  calculate_bullet_positions(game_controller, positions, &num_positions);

  for (int i = 0; i < num_positions; i++) {
    init_bullet(game_controller, epd_bullet_lv1[0], BUlLET_WIDTH, BULLET_HEIGHT,
                positions[i][0], positions[i][1], i);
  }
  init_alien(game_controller, epd_bitmap_alient_1_resize, 130, 109,
             (SCREEN_WIDTH - 130) / 2, 10);
}

// Initialize the spaceship object
void init_spaceship(GameController *game_controller,
                    const unsigned long *sprite, int width, int height, int x,
                    int y) {
  Spaceship spaceship;
  spaceship.name = "Blader";
  spaceship.size.width = width;
  spaceship.size.height = height;
  spaceship.bullet_bonus = 4;
  spaceship.position.x = x;
  spaceship.position.y = y;
  spaceship.health = 100;

  spaceship.sprite = sprite;

  game_controller->spaceship = spaceship;
}

void init_bullet(GameController *game_controller, const unsigned long *sprite,
                 int width, int height, int x, int y, int index) {
  Bullet bullet;
  bullet.name = "Bullet";
  bullet.size.width = width;
  bullet.size.height = height;

  bullet.position.x = x;
  bullet.position.y = y;

  bullet.sprite = sprite;

  game_controller->spaceship.bullet[index][0] = bullet;
  game_controller->bullet_on_screen_count = 1;
}

// Init stage
void init_stages(GameController *game_controller) {
  for (int i = 0; i < 9; i++) {
    Stage stage;
    stage.level = i + 1;
    strcpy(stage.name, "STAGE ");
    strcat(stage.name, int_to_string(i + 1));
    game_controller->stages[i] = stage;
  }
  game_controller->stage_level = 1;
}

void init_alien(GameController *game_controller, const unsigned long *sprite,
                int width, int height, int x, int y) {
  Alien alien;
  alien.name = "Alien";
  alien.size.width = width;
  alien.size.height = height;

  alien.position.x = x;
  alien.position.y = y;
  alien.health = 100;

  alien.sprite = sprite;

  game_controller->alien = alien;
}

void deinit_alien(GameController *game_controller) {
  game_controller->alien.name = NULL;
}
// Draw spaceship
void draw_spaceship(GameController *game_controller) {
  Spaceship spaceship = game_controller->spaceship;
  draw_image(spaceship.position.x, spaceship.position.y, spaceship.size.width,
             spaceship.size.height, spaceship.sprite);
}

// Draw the background
void draw_background() {
  draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_background);
}

// Draw health bar
void draw_health_bar(GameController *game_controller) {
  float healthPercentage = (float)game_controller->spaceship.health / 100.0;
  draw_capsuleARGB32(59, SCREEN_HEIGHT - 45, 250, 10, 0x00FF0000, 1,
                     healthPercentage);
  draw_image_object(20, SCREEN_HEIGHT - 60, 40, 40, epd_bitmap_health_bar_icon,
                    epd_bitmap_background);
}

void draw_welcome_screen() {
  draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_welcome);
}

// Draw alien
void draw_alien(GameController *game_controller) {
  draw_image(game_controller->alien.position.x,
             game_controller->alien.position.y,
             game_controller->alien.size.width,
             game_controller->alien.size.height, game_controller->alien.sprite);
}

void move_spaceship(GameController *game_controller, int key, int step) {
  Spaceship *spaceship = &game_controller->spaceship;
  clear_image(spaceship->position.x, spaceship->position.y,
              spaceship->size.width, spaceship->size.height,
              epd_bitmap_background);
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
  draw_spaceship(game_controller);
}

void move_bullet(GameController *game_controller, int index, int step) {
  // Get all bullets at all indexes based on the bonus
  for (int i = 0; i < game_controller->spaceship.bullet_bonus + 1; i++) {
    Bullet *bullet = &game_controller->spaceship.bullet[index][i];
    Alien *alien = &game_controller->alien;

    if (bullet->name != NULL) {
      clear_image(bullet->position.x, bullet->position.y, bullet->size.width,
                  bullet->size.height, epd_bitmap_background);
      // Calculate potential new position
      bullet->position.y = bullet->position.y - step;

      draw_image(bullet->position.x, bullet->position.y, bullet->size.width,
                 bullet->size.height, bullet->sprite);

      if (bullet->position.y <= -bullet->size.height) {
        bullet->name = NULL;
      }

      if (alien->name != NULL) {
        if (bullet->position.x >= alien->position.x &&
            bullet->position.x <= alien->position.x + alien->size.width &&
            bullet->position.y >= alien->position.y &&
            bullet->position.y <= alien->position.y + alien->size.height) {
          // Clear the bullet
          deal_damage(game_controller);
          clear_image(bullet->position.x, bullet->position.y,
                      bullet->size.width, bullet->size.height,
                      epd_bitmap_background);
          bullet->name = NULL;
        }
      }
    }
  }
}
// Clear the alien
// clear_image(alien->position.x, alien->position.y, alien->size.width,
// alien->size.height, epd_bitmap_background); alien->name = NULL;

void add_bullet(GameController *game_controller) {
  int num_positions;
  int positions[MAX_BULLETS][2]; // Maximum of MAX_BULLETS positions

  // Calculate bullet positions
  calculate_bullet_positions(game_controller, positions, &num_positions);

  // Add new bullets to the screen
  for (int i = 0; i < num_positions; i++) {
    if (game_controller->bullet_on_screen_count < MAX_BULLETS) {
      Bullet bullet;
      bullet.name = "Bullet";
      bullet.size.width = BUlLET_WIDTH;
      bullet.size.height = BULLET_HEIGHT;
      bullet.position.x = positions[i][0];
      bullet.position.y = positions[i][1];
      bullet.sprite = epd_bullet_lv1[0];

      // Add bullet to the spaceship's bullet array
      game_controller->spaceship
          .bullet[game_controller->bullet_on_screen_count][0] = bullet;
      game_controller->bullet_on_screen_count++;
    }
  }
}

// Receive damage from enemies
void receive_damage(GameController *game_controller) {
  game_controller->spaceship.health -= 10;
  clear_image(59, SCREEN_HEIGHT - 45, 250, 10, epd_bitmap_background);
  draw_health_bar(game_controller);
}

void deal_damage(GameController *game_controller) {
  game_controller->alien.health -= 10;
  uart_dec(game_controller->alien.health);
  if (game_controller->alien.health <= 0) {
    clear_image(game_controller->alien.position.x,
                game_controller->alien.position.y,
                game_controller->alien.size.width,
                game_controller->alien.size.height, epd_bitmap_background);
    game_controller->alien.name = NULL;
  }
}

void calculate_bullet_positions(GameController *game_controller,
                                int positions[][2], int *num_positions) {
  int bonus = game_controller->spaceship.bullet_bonus;
  int spaceship_center_x = game_controller->spaceship.position.x +
                           game_controller->spaceship.size.width / 2 - 6;
  int spaceship_center_y = game_controller->spaceship.position.y +
                           game_controller->spaceship.size.height / 2 - 120;

  if (bonus > 4) {
    *num_positions = 0;
    return;
  }

  *num_positions = bonus + 1;

  if (*num_positions == 1) {
    // Special pattern for one bullet
    positions[0][0] = spaceship_center_x;
    positions[0][1] = spaceship_center_y + 24;
  } else if (*num_positions == 2) {
    // Special pattern for two bullets
    int spacing = 24;
    positions[0][0] = spaceship_center_x - spacing / 2;
    positions[0][1] = spaceship_center_y + 24;
    positions[1][0] = spaceship_center_x + spacing / 2;
    positions[1][1] = spaceship_center_y + 24;
  } else if (*num_positions == 3) {
    // Special pattern for three bullets
    positions[0][0] = spaceship_center_x - 24;
    positions[0][1] = spaceship_center_y + 6;
    positions[1][0] = spaceship_center_x;
    positions[1][1] = spaceship_center_y - 24;
    positions[2][0] = spaceship_center_x + 24;
    positions[2][1] = spaceship_center_y + 6;
  } else if (*num_positions == 4) {
    // Special pattern for four bullets
    positions[0][0] = spaceship_center_x - 36;
    positions[0][1] = spaceship_center_y + 6;
    positions[1][0] = spaceship_center_x - 12;
    positions[1][1] = spaceship_center_y - 24;
    positions[2][0] = spaceship_center_x + 12;
    positions[2][1] = spaceship_center_y - 24;
    positions[3][0] = spaceship_center_x + 36;
    positions[3][1] = spaceship_center_y + 6;
  } else if (*num_positions == 5) {
    // Special pattern for five bullets
    positions[0][0] = spaceship_center_x - 48;
    positions[0][1] = spaceship_center_y + 12;
    positions[1][0] = spaceship_center_x - 24;
    positions[1][1] = spaceship_center_y - 12;
    positions[2][0] = spaceship_center_x;
    positions[2][1] = spaceship_center_y - 24;
    positions[3][0] = spaceship_center_x + 24;
    positions[3][1] = spaceship_center_y - 12;
    positions[4][0] = spaceship_center_x + 48;
    positions[4][1] = spaceship_center_y + 12;
  } else {
    *num_positions = 0;
  }
}

// Collision detection (should check at the alien)
void collision_detection(GameController *game_controller) {
  // Alien *alien = &game_controller->alien;
  // if (alien->name == NULL) {
  //   return;
  // }
  // Spaceship *spaceship = &game_controller->spaceship;
  // Bullet *bullets = spaceship->bullet;

  // for (int i = 0; i < MAX_BULLETS; i++) {
  //   if (bullets[i].name != NULL) {
  //     if (bullets[i].position.x >= alien->position.x &&
  //         bullets[i].position.x <= alien->position.x + alien->size.width &&
  //         bullets[i].position.y >= alien->position.y &&
  //         bullets[i].position.y <= alien->position.y + alien->size.height)
  //         {
  //       // Clear the bullet
  //       deal_damage(game_controller);
  //       clear_image(bullets[i].position.x, bullets[i].position.y,
  //       bullets[i].size.width, bullets[i].size.height,
  //       epd_bitmap_background); bullets[i].name = NULL;

  //       // Clear the alien
  //       // clear_image(alien->position.x, alien->position.y,
  //       alien->size.width, alien->size.height, epd_bitmap_background);
  //       // alien->name = NULL;
  //     }
  //   }
  // }
}
