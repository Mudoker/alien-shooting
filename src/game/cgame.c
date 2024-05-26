
#include "../../header/game/cgame.h"
#include "../../assets/games/bullet/bullet_lv1.h"
#include "../../assets/games/spaceship/blader.h"
#include "../../assets/games/health_logo.h"
#include "../../assets/games/welcome_screen/welcome.h"
#include "../../assets/games/background.h"
#include "../../assets/games/alient/alient_1.h"

void init_frame(int offset_x, int offset_y) {
  // Initialize buffer
  framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT,
               offset_x, offset_y);
}

void init_controller(GameController *game_controller) {
  game_controller->screen = &((Display){.init_frame = &init_frame});
  game_controller->screen->init_frame(0, 0);
  game_controller->page = WELCOME;
  game_controller->bullet_on_screen_count = 0;

  init_stages(game_controller);
  init_spaceship(game_controller, epd_blader[0], 124, 128,
                 (SCREEN_WIDTH - 124) / 2, SCREEN_HEIGHT - 128);
  init_bullet(game_controller, epd_bullet_lv1[0], 12, 48,
              game_controller->spaceship.position.x + 124 / 2 - 6,
              game_controller->spaceship.position.y - 20);
  init_alien(game_controller, epd_bitmap_alient_1_resize, 130, 109, (SCREEN_WIDTH - 130) / 2, 10);
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
  spaceship.health = 100;

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

  bullet.sprite = sprite;

  game_controller->spaceship.bullet[0] = bullet;
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
  draw_image(spaceship.position.x, spaceship.position.y,
             spaceship.size.width, spaceship.size.height, spaceship.sprite);
}

// Draw the background
void draw_background()
{
    draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_background);
}

// Draw health bar
void draw_health_bar(GameController *game_controller)
{
    float healthPercentage = (float) game_controller->spaceship.health / 100.0;
    draw_capsuleARGB32(59, SCREEN_HEIGHT - 45, 250, 10, 0x00FF0000, 1, healthPercentage);
    draw_image_object(20, SCREEN_HEIGHT - 60, 40, 40, epd_bitmap_health_bar_icon, epd_bitmap_background);
}

void draw_welcome_screen() {
  draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_welcome);
}

// Draw alien
void draw_alien(GameController *game_controller) {
  draw_image(game_controller->alien.position.x, game_controller->alien.position.y,
             game_controller->alien.size.width, game_controller->alien.size.height, game_controller->alien.sprite);
}

void move_spaceship(GameController *game_controller, int key, int step) {
  Spaceship *spaceship = &game_controller->spaceship;
  clear_image(spaceship->position.x, spaceship->position.y, spaceship->size.width, spaceship->size.height, epd_bitmap_background);
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

// ALways go vertically up
void move_bullet(GameController *game_controller, int index, int step) {
  Bullet *bullet = &game_controller->spaceship.bullet[index];
  Alien *alien = &game_controller->alien;

  clear_image(bullet->position.x, bullet->position.y, bullet->size.width, bullet->size.height, epd_bitmap_background);
  // Calculate potential new position
  bullet->position.y = bullet->position.y - step;


  draw_image(bullet->position.x, bullet->position.y, bullet->size.width, bullet->size.height, bullet->sprite);

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
          clear_image(bullet->position.x, bullet->position.y, bullet->size.width, bullet->size.height, epd_bitmap_background);
          bullet->name = NULL;
            }
  }

        // Clear the alien
        // clear_image(alien->position.x, alien->position.y, alien->size.width, alien->size.height, epd_bitmap_background);
        // alien->name = NULL;
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

    bullet.sprite = epd_bullet_lv1[0];

    game_controller->spaceship.bullet[bullet_count] = bullet;
    game_controller->bullet_on_screen_count++;
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
    clear_image(game_controller->alien.position.x, game_controller->alien.position.y, game_controller->alien.size.width, game_controller->alien.size.height, epd_bitmap_background);
    game_controller->alien.name = NULL;
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
  //         bullets[i].position.y <= alien->position.y + alien->size.height) {
  //       // Clear the bullet
  //       deal_damage(game_controller);
  //       clear_image(bullets[i].position.x, bullets[i].position.y, bullets[i].size.width, bullets[i].size.height, epd_bitmap_background);
  //       bullets[i].name = NULL;

  //       // Clear the alien
  //       // clear_image(alien->position.x, alien->position.y, alien->size.width, alien->size.height, epd_bitmap_background);
  //       // alien->name = NULL;
  //     }
  //   }
  // }
}
