
#include "../../header/game/cgame.h"
#include "../../assets/games/alient/alient_1.h"
#include "../../assets/games/power_up/health.h"
#include "../../assets/games/power_up/shield.h"
#include "../utils/randomNum.h"
#include "../../assets/games/background.h"
#include "../../assets/games/bullet/bullet_lv1.h"
#include "../../assets/games/health_logo.h"
#include "../../assets/games/powers_up/badge/bonus_bullets.h"
#include "../../assets/games/spaceship/blader.h"
#include "../../assets/games/welcome_screen/welcome.h"
#include "../../assets/games/explosion/explosion.h"

#define BUlLET_WIDTH 17
#define BULLET_HEIGHT 52

void calculate_bullet_positions(GameController *game_controller,
                                int positions[][2], int *num_positions);

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
  init_alien(game_controller, epd_bitmap_alient_1_resize, 130, 109,
             (SCREEN_WIDTH - 130) / 2, 10);
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
    Stage stage;
    stage.level = i + 1;
    strcpy(stage.name, "STAGE ");
    strcat(stage.name, int_to_string(i + 1));
    game_controller->stages[i] = stage;
  }
  game_controller->stage_level = 1;
}

void init_alien(GameController *game_controller, const unsigned long *sprite,
                int width, int height, int x, int y)
{
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

void deinit_alien(GameController *game_controller)
{
  game_controller->alien.name = NULL;
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
  draw_capsuleARGB32(59, SCREEN_HEIGHT - 45, 250, 10, 0x00FF0000, 1,
                     healthPercentage);
  draw_image_object(20, SCREEN_HEIGHT - 60, 40, 40, epd_bitmap_health_bar_icon,
                    epd_bitmap_background);
}

void draw_welcome_screen()
{
  draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_welcome);
}

// Draw alien
void draw_alien(GameController *game_controller)
{
  draw_image(game_controller->alien.position.x,
             game_controller->alien.position.y,
             game_controller->alien.size.width,
             game_controller->alien.size.height, game_controller->alien.sprite);
}

void move_spaceship(GameController *game_controller, int key, int step)
{
  Spaceship *spaceship = &game_controller->spaceship;
  clear_image(spaceship->position.x, spaceship->position.y,
              spaceship->size.width, spaceship->size.height,
              epd_bitmap_background);
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
  // Get all bullets at all indexes based on the bonus
  for (int i = 0; i < game_controller->spaceship.bullet_bonus + 1; i++)
  {
    Bullet *bullet = &game_controller->spaceship.bullet[index][i];
    Alien *alien = &game_controller->alien;

    if (bullet->name != NULL)
    {
      clear_image(bullet->position.x, bullet->position.y, bullet->size.width,
                  bullet->size.height, epd_bitmap_background);
      // Calculate potential new position
      bullet->position.y = bullet->position.y - step;

      draw_image(bullet->position.x, bullet->position.y, bullet->size.width,
                 bullet->size.height, bullet->sprite);

      if (bullet->position.y <= -bullet->size.height)
      {
        bullet->name = NULL;
      }

      if (alien->name != NULL)
      {
        if (bullet->position.x >= alien->position.x &&
            bullet->position.x <= alien->position.x + alien->size.width &&
            bullet->position.y >= alien->position.y &&
            bullet->position.y <= alien->position.y + alien->size.height)
        {
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

// void move_PU_to_position(GameController *game_controller)
// {
//   PowerUp *powerup = &game_controller->powerup;
//   clear_image(powerup->position.x, powerup->position.y, 90, 90, epd_bitmap_background);
//   if (powerup->position.y < powerup->target.y)
//   {
//     powerup->position.y += 2;
//   }
//   else
//   {
//     powerup->reach_target = 1;
//   }
//   draw_health_PU(game_controller);
//   // draw_image_object(powerup->position.x, powerup->position.y, 90, 90, powerup->sprite, epd_bitmap_background);
// }

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

void game_loop(GameController *game_controller)
{
  // while (1)
  // {
  //   init_power_up(game_controller);

  //   while (!pu_reach_target(game_controller))
  //   {
  //     move_PU_to_position(game_controller);
  //     wait_msec(8000);
  //   }
  // }
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
void move_alien(GameController *game_controller, int step)
{
  Alien *alien = &game_controller->alien;
  clear_image(alien->position.x, alien->position.y, alien->size.width, alien->size.height, epd_bitmap_background);
  // Calculate potential new position
  int newX = alien->position.x;
  int newY = alien->position.y;

  // Calculate boundary limits
  int maxX = SCREEN_WIDTH - alien->size.width;
  int maxY = SCREEN_HEIGHT - alien->size.height;

  // Clamp position to stay within boundaries
  alien->position.x = (newX < 0) ? 0 : (newX > maxX) ? maxX
                                                     : newX;
  alien->position.y = (newY < 0) ? 0 : (newY > maxY) ? maxY
                                                     : newY;

  // Draw the spaceship at the new position
  draw_alien(game_controller);
}

void add_bullet(GameController *game_controller)
{
  int num_positions;
  int positions[MAX_BULLETS][2]; // Maximum of MAX_BULLETS positions

  // Calculate bullet positions
  calculate_bullet_positions(game_controller, positions, &num_positions);

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
      game_controller->spaceship
          .bullet[game_controller->bullet_on_screen_count][0] = bullet;
      game_controller->bullet_on_screen_count++;
    }
  }
}

// Receive damage from enemies
void receive_damage(GameController *game_controller)
{
  game_controller->spaceship.health -= 10;
  clear_image(59, SCREEN_HEIGHT - 45, 250, 10, epd_bitmap_background);
  draw_health_bar(game_controller);
}

void deal_damage(GameController *game_controller)
{
  game_controller->alien.health -= 10;
  uart_dec(game_controller->alien.health);
  if (game_controller->alien.health <= 0)
  {
    clear_image(game_controller->alien.position.x,
                game_controller->alien.position.y,
                game_controller->alien.size.width,
                game_controller->alien.size.height, epd_bitmap_background);
    game_controller->alien.name = NULL;
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

void explosion()
{
  // framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, cinema_bg_width, cinema_bg_height, 0, 0);
  display_explosion(paddingLeft, paddingTop, 90, 90, 10, epd_bitmap_explosion_allArray);
  
}

void display_explosion(int x, int y, int w, int h, int num_frames, const unsigned long **video)
{
  for (int i = 0; i < 1; i++)
  {
    for (int frame = 0; frame < num_frames; frame++)
    {
      draw_image(x, y, w, h, video[frame]);
      wait_msec(100500);
      clear_image(paddingLeft, paddingTop, 90, 90, epd_bitmap_background);
    }
    
  }
  
}
