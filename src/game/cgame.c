
#include "../../header/game/cgame.h"
#include "../../header/game/map.h"
#include "../../assets/games/alient/alient_1.h"
#include "../../assets/games/result_screens/lose_screen.h"
#include "../../assets/games/result_screens/win_final_screen.h"
#include "../../assets/games/result_screens/win_screen.h"
#include "../../assets/games/result_screens/stars/stars_1.h"
#include "../../assets/games/result_screens/stars/stars_3.h"
#include "../../assets/games/result_screens/stars/stars_5.h"
#include "../../assets/games/result_screens/digits/secs.h"
#include "../../assets/games/result_screens/digits/digits.h"

#include "../../assets/games/power_up/health.h"
#include "../../assets/games/power_up/shield.h"
#include "../utils/randomNum.h"
#include "../../assets/games/bullet/alien_bullet.h"
#include "../../assets/games/background.h"
#include "../../assets/games/bullet/bullet_lv1.h"
#include "../../assets/games/health_logo.h"
#include "../../assets/games/powers_up/badge/bonus_bullets.h"
#include "../../assets/games/spaceship/blader.h"
#include "../../assets/games/spaceship/ship_lev1.h"
#include "../../assets/games/spaceship/ship_lev3.h"
#include "../../assets/games/welcome_screen/welcome.h"

#include "../../assets/games/ship_selection_screen/ship_selection_title.h"
#include "../../assets/games/ship_selection_screen/ship_selection_button.h"
#include "../../assets/games/ship_selection_screen/arrow_left.h"
#include "../../assets/games/ship_selection_screen/arrow_right.h"

#define BUlLET_WIDTH 17
#define BULLET_HEIGHT 52

void init_frame(int offset_x, int offset_y)
{
  // Initialize buffer
  framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT,
               offset_x, offset_y);
}

void init_controller(GameController *game_controller)
{
  game_controller->screen = &((Display){.init_frame = &init_frame});
  game_controller->screen->init_frame(0, 0);
  game_controller->page = WELCOME;
  game_controller->bullet_on_screen_count = 0;

  int positions[5][2]; // Maximum of MAX_BULLETS positions
  int num_positions;

  init_stages(game_controller);
  init_spaceship(game_controller, epd_blader[0], 124, 128,
                 (SCREEN_WIDTH - 124) / 2, SCREEN_HEIGHT - 128);

  calculate_bullet_positions(game_controller, positions, &num_positions);

  for (int i = 0; i < num_positions; i++)
  {
    init_bullet(game_controller, epd_bullet_lv1[0], BUlLET_WIDTH, BULLET_HEIGHT,
                positions[i][0], positions[i][1], i);
  }
}

// Initialize the spaceship object
void init_spaceship(GameController *game_controller,
                    const unsigned long *sprite, int width, int height, int x,
                    int y)
{
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
                 int width, int height, int x, int y, int index)
{
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
void init_stages(GameController *game_controller)
{
  for (int i = 0; i < 9; i++)
  {
    char name[MAX_STR_LENGTH];
    strcpy(name, "STAGE ");
    strcat(name, int_to_string(i + 1));

    strcpy(game_controller->stages[i].name, name);

    game_controller->stages[i].level = i + 1;

    for (int j = 0; j < 3; j++)
    {
      game_controller->stages[i].waves[j].level = j + 1;
      game_controller->stages[i].waves[j].alien_count = 0; // Initialize alien count
    }
  }
  game_controller->stage_level = 1;
}

void init_alien(Alien *alien, const unsigned long *sprite, int width, int height, int x, int y)
{
  alien->name = "Alien";
  alien->size.width = width;
  alien->size.height = height;

  alien->position.x = x;
  alien->position.y = y;
  alien->direction = 1;
  alien->health = 100;
  alien->sprite = sprite;
}

// Init wave
void init_wave(GameController *gc)
{
  Wave *wave = &gc->stages[0].waves[gc->current_wave]; // Initialize the first wave of the given stage
  wave->level = gc->current_wave + 1;

  int count = 0;
  for (int j = 0; j < 3; j++)
  { // Rows of the map
    for (int k = 0; k < 5; k++)
    { // Columns of the map
      if (map_1[gc->current_wave][j][k] == 1)
      {
        init_alien(&wave->aliens[count], epd_bitmap_alient_1_resize, 130, 109, 130 * k, 109 * j);
        count++;
      }
    }
  }
  wave->alien_count = count;
}

Spaceship* init_current_ship_option() {
    static Spaceship spaceship; 
    
    spaceship.name = "Lev1";
    spaceship.size.width = 124;
    spaceship.size.height = 188;
    spaceship.bullet_bonus = 4;

    spaceship.position.x = (SCREEN_WIDTH - spaceship.size.width) / 2;
    spaceship.position.y = (SCREEN_HEIGHT - spaceship.size.height) / 2;
    spaceship.health = 100;

    spaceship.sprite = epd_bitmap_ship_l1_allArray[0];

    return &spaceship;
}

void draw_spaceship_option(Spaceship *spaceship, int order, int clear, Spaceship *current_ship_option)
{

  if (clear)
  {
    clear_image(current_ship_option->position.x, current_ship_option->position.y, current_ship_option->size.width, current_ship_option->size.height, epd_bitmap_background);
  }

  switch (order)
  {
  case 1:
    current_ship_option->size.width = 124;
    current_ship_option->size.height = 188;
    current_ship_option->sprite = epd_bitmap_ship_l1_allArray[0];
    break;
  case 2:
    current_ship_option->size.width = 124;
    current_ship_option->size.height = 128;
    current_ship_option->sprite = epd_blader[0];
    break;
  case 3:
    current_ship_option->size.width = 124;
    current_ship_option->size.height = 127;
    current_ship_option->sprite = epd_bitmap_ship_l3_allArray[0];
    break;
  default:
    return;
  }

  current_ship_option->position.x = (SCREEN_WIDTH - current_ship_option->size.width) / 2;
  current_ship_option->position.y = (SCREEN_HEIGHT - current_ship_option->size.height) / 2;
  draw_image(current_ship_option->position.x, current_ship_option->position.y, current_ship_option->size.width, current_ship_option->size.height, current_ship_option->sprite);
}

void draw_ship_selection_page()
{
  draw_image(0, 60, SCREEN_WIDTH, 186, epd_bitmap_ship_selection_title);
  draw_image(215, 650, 350, 103, epd_bitmap_ship_selection_button);
}

void draw_arrows(int order)
{
  const unsigned long *arrow_left = epd_bitmap_arrow_left;
  const unsigned long *arrow_right = epd_bitmap_arrow_right;

  switch (order)
  {
  case 1:
    clear_image(60, 400, 70, 72, epd_bitmap_background);
    draw_image(650, 400, 70, 72, arrow_right);
    break;
  case 2:
    draw_image(60, 400, 70, 72, arrow_left);
    draw_image(650, 400, 70, 72, arrow_right);
    break;
  case 3:
    draw_image(60, 400, 70, 72, arrow_left);
    clear_image(650, 400, 70, 72, epd_bitmap_background);
    break;
  default:
    break;
  }
}

// Draw spaceship
void draw_spaceship(GameController *game_controller)
{
  Spaceship spaceship = game_controller->spaceship;
  draw_image(spaceship.position.x, spaceship.position.y, spaceship.size.width,
             spaceship.size.height, spaceship.sprite);
}

// Draw the background
void draw_background()
{
  draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_background);
}

// Draw health bar
void draw_health_bar(GameController *game_controller)
{
  float healthPercentage = (float)game_controller->spaceship.health / 100.0;
  draw_capsuleARGB32(59, SCREEN_HEIGHT - 45, 250, 10, 0x00FF0000, 1, healthPercentage);
  draw_image_object(20, SCREEN_HEIGHT - 60, 40, 40, epd_bitmap_health_bar_icon, epd_bitmap_background);
}

void draw_welcome_screen()
{
  draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_welcome);
}

// Draw alien
void draw_alien(GameController *game_controller)
{
  for (int i = 0; i < game_controller->stages[0].waves[game_controller->current_wave].alien_count; i++)
  {
    Alien alien = game_controller->stages[0].waves[game_controller->current_wave].aliens[i];
    if (game_controller->stages[0].waves[game_controller->current_wave].aliens[i].name != NULL)
    {
      draw_image(alien.position.x, alien.position.y, alien.size.width, alien.size.height, alien.sprite);
    }
  }
}

void move_spaceship(GameController *game_controller, int key, int step)
{
  Spaceship *spaceship = &game_controller->spaceship;
  clear_image(spaceship->position.x, spaceship->position.y, spaceship->size.width, spaceship->size.height, epd_bitmap_background);
  // Calculate potential new position
  int newX = spaceship->position.x;
  int newY = spaceship->position.y;

  switch (key)
  {
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
  spaceship->position.x = (newX < 0) ? 0 : (newX > maxX) ? maxX
                                                         : newX;
  spaceship->position.y = (newY < 0) ? 0 : (newY > maxY) ? maxY
                                                         : newY;

  // Draw the spaceship at the new position
  draw_spaceship(game_controller);
}

void move_bullet(GameController *game_controller, int index, int step)
{
  uart_dec(game_controller->bullet_on_screen_count);
  for (int i = 0; i < game_controller->spaceship.bullet_bonus + 1; i++)
  {
    Bullet *bullet = &game_controller->spaceship.bullet[index][i];

    // If the bullet is already inactive, skip it
    if (bullet->name == NULL)
    {
      continue;
    }

    // Clear the bullet at the previous position
    clear_image(bullet->position.x, bullet->position.y, bullet->size.width, bullet->size.height, epd_bitmap_background);

    // Calculate potential new position
    bullet->position.y -= step;

    // Check if the bullet is out of the screen
    if (bullet->position.y <= -bullet->size.height)
    {
      bullet->name = NULL;
      continue; // Skip to the next bullet, do not return
    }

    // Check for collision with aliens in the current wave
    Wave *current_wave = &game_controller->stages[0].waves[game_controller->current_wave];
    for (int j = 0; j < current_wave->alien_count; j++)
    {
      Alien *alien = &current_wave->aliens[j];

      if (alien->name != NULL)
      {
        if (bullet->position.x >= alien->position.x &&
            bullet->position.x <= alien->position.x + alien->size.width &&
            bullet->position.y >= alien->position.y &&
            bullet->position.y <= alien->position.y + alien->size.height)
        {
          uart_puts("Bullet hit an alien!\n");

          // Deal damage to the alien
          deal_damage(game_controller, j);

          // Clear the bullet
          clear_image(bullet->position.x, bullet->position.y, bullet->size.width, bullet->size.height, epd_bitmap_background);

          bullet->name = NULL;
          // No break here, to allow for multiple collisions in the same frame
        }
      }
    }

    // If bullet is still active, draw it at the new position
    if (bullet->name != NULL)
    {
      draw_image(bullet->position.x, bullet->position.y, bullet->size.width, bullet->size.height, bullet->sprite);
    }
  }
}

// void move_alien_bullets(GameController *game_controller, int index, int step) {
//   for (int i = 0; i < game_controller->stages[0].waves[game_controller->current_wave].alien_count; i++)
//   {
//     Alien *alien = &game_controller->stages[0].waves[game_controller->current_wave].aliens[i];
//     Bullet *bullet = &alien->bullet[index];

//     // Clear the bullet at the previous position
//     clear_image(bullet->position.x, bullet->position.y, bullet->size.width, bullet->size.height, epd_bitmap_background);

//     // Calculate potential new position
//     bullet->position.y += step;

//     // Check if the bullet is out of the screen
//     if (bullet->position.y >= SCREEN_HEIGHT)
//     {
//       bullet->name = NULL;
//       return; // No need to continue if the bullet is out of the screen
//     }

//     // Draw the bullet at the new position
//     draw_image(bullet->position.x, bullet->position.y, bullet->size.width, bullet->size.height, bullet->sprite);

//     // Check for collision with the spaceship
//     Spaceship *spaceship = &game_controller->spaceship;
//     if (bullet->position.x >= spaceship->position.x &&
//         bullet->position.x <= spaceship->position.x + spaceship->size.width &&
//         bullet->position.y >= spaceship->position.y &&
//         bullet->position.y <= spaceship->position.y + spaceship->size.height)
//     {
//       // Receive damage from the bullet
//       receive_damage(game_controller);

//       // Clear the bullet
//       clear_image(bullet->position.x, bullet->position.y, bullet->size.width, bullet->size.height, epd_bitmap_background);
//       bullet->name = NULL;

//       return; // Exit after collision
//     }
//   }

// }

int pos_x[5] = {0, 130, 260, 390, 520};
int pos_y[4] = {0, 109, 218, 327};
int row_counts[4] = {0, 0, 0, 0};
int col_counts[5] = {0, 0, 0, 0, 0};

void init_power_up(GameController *game_controller)
{
  int valid_pos = 0, attempts = 0;
  int rand_col, rand_row;
  int type = randomNum() % 2;
  PowerUp powerup;
  init_seed();
  rand_col = randomNum() % 5;
  rand_row = randomNum() % 4;
  powerup.position.x = pos_x[rand_col];
  powerup.position.y = 0;
  powerup.target.x = pos_x[rand_col];
  powerup.target.y = 850;
  powerup.reach_target = 0;

  if (type == 0)
  {
    powerup.sprite = epd_bitmap_health_allArray[0];
  }
  else
  {
    powerup.sprite = epd_bitmap_shield_allArray[0];
  }

  // powerup.sprite = epd_bitmap_health_allArray[0];
  uart_puts("Powerup position: ");
  uart_puts(itoa(powerup.position.x));
  uart_puts(itoa(powerup.position.y));
  uart_puts("\n");
  uart_puts("Powerup target: ");
  uart_puts(itoa(powerup.target.x));
  uart_puts(itoa(powerup.target.y));
  uart_puts("\n");
  game_controller->powerup = powerup;
}

void move_PU_to_position(GameController *game_controller)
{
  PowerUp *powerup = &game_controller->powerup;
  clear_image(powerup->position.x, powerup->position.y, 90, 90, epd_bitmap_background);
  uart_puts("Current Y position: ");
  uart_puts(itoa(powerup->position.y));
  uart_puts("\n");

  if (powerup->position.y < powerup->target.y)
  {
    powerup->position.y += 2;
  }
  else
  {
    powerup->reach_target = 1;
    uart_puts("Powerup reached target\n");
  }

  draw_health_PU(game_controller);
}

int pu_reach_target(GameController *game_controller)
{
  if (!game_controller->powerup.reach_target)
  {
    return 0; // If any alien hasn't reached its position, return false
  }
  return 1; // All aliens have reached their positions
}

void draw_health_PU(GameController *game_controller)
{
  draw_image_object(game_controller->powerup.position.x, game_controller->powerup.position.y, 90, 90, game_controller->powerup.sprite, epd_bitmap_background);
}

void draw_shield_PU(GameController *game_controller)
{
  // int x = pos_x[rand() % 5];
  // int y = pos_y[rand() % 4];
  draw_image_object(780 / 2, 450, 90, 90, epd_bitmap_shield_allArray[0], epd_bitmap_background);
}

void clear_all_bullets(GameController *game_controller)
{
  for (int i = 0; i < MAX_BULLETS; i++)
  {
    for (int j = 0; j < game_controller->spaceship.bullet_bonus + 1; j++)
    {
      Bullet *bullet = &game_controller->spaceship.bullet[i][j];
      if (bullet->name != NULL)
      {
        clear_image(bullet->position.x, bullet->position.y, bullet->size.width, bullet->size.height, epd_bitmap_background);
        bullet->name = NULL;
      }
    }
  }
}

void add_bullet(GameController *game_controller)
{
  int num_positions;
  int positions[MAX_BULLETS][2]; // Maximum of MAX_BULLETS positions

  // Calculate bullet positions
  calculate_bullet_positions(game_controller, positions, &num_positions);

  // Reset the bullet count if it reaches the maximum
  if (game_controller->bullet_on_screen_count >= MAX_BULLETS)
  {
    game_controller->bullet_on_screen_count = 0;
    clear_all_bullets(game_controller);
  }

  // Add new bullets to the screen
  for (int i = 0; i < num_positions; i++)
  {
    if (game_controller->bullet_on_screen_count < MAX_BULLETS)
    {
      Bullet bullet;
      bullet.name = "Bullet";
      bullet.size.width = BUlLET_WIDTH;
      bullet.size.height = BULLET_HEIGHT;
      bullet.position.x = positions[i][0];
      bullet.position.y = positions[i][1];
      bullet.sprite = epd_bullet_lv1[0];

      // Add bullet to the spaceship's bullet array
      game_controller->spaceship.bullet[game_controller->bullet_on_screen_count][0] = bullet;
      game_controller->bullet_on_screen_count++;
    }
  }
}

// void add_alien_bullet(GameController *game_controller, int index)
// {
//   Wave *current_wave = &game_controller->stages[0].waves[game_controller->current_wave];
//   Alien *alien = &current_wave->aliens[index];
//   Bullet bullet;
//   bullet.name = "Alien Bullet";
//   bullet.size.width = 12;
//   bullet.size.height = 48;
//   bullet.position.x = alien->position.x + 65;
//   bullet.position.y = alien->position.y + 50;
//   bullet.sprite = epd_bitmap_alien_bullet;
//   alien->bullet[game_controller->bullet_on_screen_alien_count] = bullet;
//   game_controller->bullet_on_screen_alien_count++;
// }
// Receive damage from enemies
void receive_damage(GameController *game_controller)
{
  game_controller->spaceship.health -= 10;
  clear_image(59, SCREEN_HEIGHT - 45, 250, 10, epd_bitmap_background);
  draw_health_bar(game_controller);
}

void deal_damage(GameController *game_controller, int index)
{
  Wave *current_wave = &game_controller->stages[0].waves[game_controller->current_wave];
  Alien *alien = &current_wave->aliens[index];
  alien->health -= 10;
  if (alien->health <= 0)
  {
    clear_image(alien->position.x, alien->position.y, alien->size.width, alien->size.height, epd_bitmap_background);
    alien->name = NULL;
  }
}

void clear_wave(GameController *game_controller)
{
  int defeat_count = 0;
  Wave *current_wave = &game_controller->stages[0].waves[game_controller->current_wave];
  for (int i = 0; i < current_wave->alien_count; i++)
  {
    Alien *alien = &current_wave->aliens[i];
    if (alien->name == NULL)
    {
      defeat_count++;
    }
  }

  if (defeat_count == current_wave->alien_count)
  {
    wait_msec(1000000);
    game_controller->current_wave++;
    init_wave(game_controller);

    draw_alien(game_controller);
  }
}

void move_aliens(GameController *game_controller, int step)
{
  // Update position of the alien
  Wave *current_wave = &game_controller->stages[0].waves[game_controller->current_wave];

  for (int i = 0; i < current_wave->alien_count; i++)
  {
    Alien *alien = &current_wave->aliens[i];
    if (alien->name != NULL)
    {
      clear_image(alien->position.x, alien->position.y, alien->size.width, alien->size.height, epd_bitmap_background);
      alien->position.x += step * alien->direction;

      // Check for screen boundaries and change direction if necessary
      if (alien->position.x <= 0 || alien->position.x + alien->size.width >= SCREEN_WIDTH)
      {
        alien->direction *= -1;                       // Reverse direction
        alien->position.x += step * alien->direction; // Move back into screen bounds
      }

      draw_image(alien->position.x, alien->position.y, alien->size.width, alien->size.height, alien->sprite);
    }
  }
}

void calculate_bullet_positions(GameController *game_controller,
                                int positions[][2], int *num_positions)
{
  int bonus = game_controller->spaceship.bullet_bonus;
  int spaceship_center_x = game_controller->spaceship.position.x +
                           game_controller->spaceship.size.width / 2 - 6;
  int spaceship_center_y = game_controller->spaceship.position.y +
                           game_controller->spaceship.size.height / 2 - 120;

  if (bonus > 4)
  {
    *num_positions = 0;
    return;
  }

  *num_positions = bonus + 1;

  if (*num_positions == 1)
  {
    // Special pattern for one bullet
    positions[0][0] = spaceship_center_x;
    positions[0][1] = spaceship_center_y + 24;
  }
  else if (*num_positions == 2)
  {
    // Special pattern for two bullets
    int spacing = 24;
    positions[0][0] = spaceship_center_x - spacing / 2;
    positions[0][1] = spaceship_center_y + 24;
    positions[1][0] = spaceship_center_x + spacing / 2;
    positions[1][1] = spaceship_center_y + 24;
  }
  else if (*num_positions == 3)
  {
    // Special pattern for three bullets
    positions[0][0] = spaceship_center_x - 24;
    positions[0][1] = spaceship_center_y + 6;
    positions[1][0] = spaceship_center_x;
    positions[1][1] = spaceship_center_y - 24;
    positions[2][0] = spaceship_center_x + 24;
    positions[2][1] = spaceship_center_y + 6;
  }
  else if (*num_positions == 4)
  {
    // Special pattern for four bullets
    positions[0][0] = spaceship_center_x - 36;
    positions[0][1] = spaceship_center_y + 6;
    positions[1][0] = spaceship_center_x - 12;
    positions[1][1] = spaceship_center_y - 24;
    positions[2][0] = spaceship_center_x + 12;
    positions[2][1] = spaceship_center_y - 24;
    positions[3][0] = spaceship_center_x + 36;
    positions[3][1] = spaceship_center_y + 6;
  }
  else if (*num_positions == 5)
  {
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
  }
  else
  {
    *num_positions = 0;
  }
}

// Collision detection (should check at the alien)
void collision_detection(GameController *game_controller)
{
}

void draw_lose_screen(GameController *game_controller, int seconds)
{
  draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_lose_screen);
  draw_completed_time(seconds, 505);
}

void draw_win_final_screen(GameController *game_controller, int seconds)
{
  draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_win_final_screen);
  draw_stars(seconds);
  draw_completed_time(seconds, 605);
}

void draw_win_screen(GameController *game_controller, int seconds)
{
  draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_win_screen);
  draw_stars(seconds);
  draw_completed_time(seconds, 476);
}

void draw_stars(int seconds)
{
  if (seconds <= 20)
  {
    draw_image(195, 100, 390, 100, epd_bitmap_stars_5);
  }
  else if (seconds <= 40)
  {
    draw_image(195, 100, 390, 100, epd_bitmap_stars_3);
  }
  else
  {
    draw_image(195, 100, 390, 100, epd_bitmap_stars_1);
  }
}

void draw_completed_time(int seconds, int y)
{
  if (seconds < 10)
  {
    draw_image(502, y, 37, 37, epd_bitmap_digits_allArray[seconds]);
  }
  else
  {
    int tens = seconds / 10;
    int ones = seconds % 10;

    // Draw tens digit
    draw_image(480, y, 37, 37, epd_bitmap_digits_allArray[tens]);
    // Draw ones digit
    draw_image(502, y, 37, 37, epd_bitmap_digits_allArray[ones]);
  }

  draw_image(535, y, 97, 37, epd_bitmap_secs);
}

char *itoa(int num)
{
  static char str[12]; // Large enough for an integer, includes space for
                       // negative sign and null terminator
  int i = 0;
  int isNegative = 0;

  // Handle 0 explicitly, otherwise, an empty string is printed for 0
  if (num == 0)
  {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  // In standard itoa(), negative numbers are handled only with base 10
  // Otherwise, numbers are considered unsigned
  if (num < 0)
  {
    isNegative = 1;
    num = -num;
  }

  // Process individual digits
  while (num != 0)
  {
    int rem = num % 10;
    str[i++] = rem + '0'; // Convert int to char
    num = num / 10;
  }

  // If number is negative, append '-'
  if (isNegative)
    str[i++] = '-';

  str[i] = '\0'; // Append string terminator

  // Reverse the string
  int start = 0;
  int end = i - 1;
  while (start < end)
  {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }

  return str;
}
void draw_badge(int badge)
{
  // Badge Constants
  const int BONUS_WIDTH = 210;
  const int BONUS_HEIGHT = 226;
  const int POS_X = (SCREEN_WIDTH - BONUS_WIDTH) / 2;
  const int POS_Y = (SCREEN_HEIGHT - BONUS_HEIGHT) / 2;

  // Badge Animation Constants
  float badge_opacity = 1.0f;             // Initial opacity
  int fade_duration = 100;                // Fade duration in frames
  unsigned int animation_duration = 1000; // Animation duration in milliseconds

  if (badge == BULLET_BONUS)
  {
    // Gradually decrease opacity over fade duration
    for (int frame = 0; frame < fade_duration; frame++)
    {
      // Draw the badge with current opacity
      draw_image_with_opacity(POS_X, POS_Y, BONUS_WIDTH, BONUS_HEIGHT,
                              epd_bullet_bonus_badge[0], epd_bitmap_background,
                              badge_opacity);

      // Wait for a specific amount of time
      unsigned int frame_duration = animation_duration / fade_duration;
      wait_msec(frame_duration);

      // Decrease opacity gradually
      badge_opacity -= 1.0f / fade_duration;
      if (badge_opacity < 0.0f)
      {
        badge_opacity = 0.0f;
      }
    }
  }
}

void change_spaceship(GameController *game_controller, int order)
{
  switch (order)
  {
  case 1:
    game_controller->spaceship.sprite = epd_bitmap_ship_l1_allArray[0];
    game_controller->spaceship.size.width = 124;
    game_controller->spaceship.size.height = 188;
    break;
  case 2:
    game_controller->spaceship.sprite = epd_blader[0];
    game_controller->spaceship.size.width = 124;
    game_controller->spaceship.size.height = 128;
    break;
  case 3:
    game_controller->spaceship.sprite = epd_bitmap_ship_l3_allArray[0];
    game_controller->spaceship.size.width = 124;
    game_controller->spaceship.size.height = 127;
    break;
  default:
    break;
  }
}
