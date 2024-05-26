
#include "../../header/game/cgame.h"
#include "../../assets/games/bullet/bullet_lv1.h"
#include "../../assets/games/spaceship/blader.h"
#include "../../assets/games/health_logo.h"
#include "../../assets/games/welcome_screen/welcome.h"
#include "../../assets/games/background.h"
#include "../../assets/games/ship_selection_screen/ship_selection_title.h"
#include "../../assets/games/ship_selection_screen/ship_selection_button.h"
#include "../../assets/games/ship_selection_screen/arrow_left.h"
#include "../../assets/games/ship_selection_screen/arrow_right.h"

#include "../../assets/games/spaceship/ship_lev1.h"
#include "../../assets/games/spaceship/ship_lev3.h"

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

  init_stages(game_controller);
  init_spaceship(game_controller, epd_blader[0], 124, 128,
                 (SCREEN_WIDTH - 124) / 2, SCREEN_HEIGHT - 128);
  init_bullet(game_controller, epd_bullet_lv1[0], 12, 48,
              game_controller->spaceship.position.x + 124 / 2 - 6,
              game_controller->spaceship.position.y - 20);
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

  spaceship.position.x = x;
  spaceship.position.y = y;
  spaceship.health = 100;

  spaceship.sprite = sprite;

  game_controller->spaceship = spaceship;
}

Spaceship init_current_ship_option()
{
  Spaceship spaceship;
  spaceship.name = "Blader";
  spaceship.size.width = 124;
  spaceship.size.height = 188;

  spaceship.position.x = (SCREEN_WIDTH - 124) / 2;
  spaceship.position.y = (SCREEN_HEIGHT - 188) / 2;
  spaceship.health = 100;

  spaceship.sprite = epd_bitmap_ship_l1_allArray[0];

  return spaceship;
}

void init_bullet(GameController *game_controller, const unsigned long *sprite,
                 int width, int height, int x, int y)
{
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

// Draw spaceship
void draw_spaceship(GameController *game_controller)
{
  Spaceship spaceship = game_controller->spaceship;
  draw_image(spaceship.position.x, spaceship.position.y,
             spaceship.size.width, spaceship.size.height, spaceship.sprite);
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
    current_ship_option->size.width = 135;
    current_ship_option->size.height = 112;
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
    clear_image(60, 400, 70, 72, arrow_left);
    draw_image(650, 400, 70, 72, arrow_right);
    break;
  case 2:
    draw_image(60, 400, 70, 72, arrow_left);
    draw_image(650, 400, 70, 72, arrow_right);
    break;
  case 3:
    draw_image(60, 400, 70, 72, arrow_left);
    clear_image(650, 400, 70, 72, arrow_right);
    break;
  default:
    break;
  }
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

// ALways go vertically up
void move_bullet(Bullet *bullet, int step)
{

  clear_image(bullet->position.x, bullet->position.y, bullet->size.width, bullet->size.height, epd_bitmap_background);
  // Calculate potential new position
  bullet->position.y = bullet->position.y - step;

  draw_image(bullet->position.x, bullet->position.y, bullet->size.width, bullet->size.height, bullet->sprite);

  if (bullet->position.y <= -bullet->size.height)
  {
    bullet->name = NULL;
  }
}

void add_bullet(GameController *game_controller, int x, int y)
{
  // Get the total number of bullets on the screen
  int bullet_count = game_controller->bullet_on_screen_count;

  // Add a new bullet to the screen
  if (bullet_count < MAX_BULLETS)
  {
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

// Deal damage to the spaceship
void deal_damage(GameController *game_controller)
{
  game_controller->spaceship.health -= 10;
  clear_image(59, SCREEN_HEIGHT - 45, 250, 10, epd_bitmap_background);
  draw_health_bar(game_controller);
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
    game_controller->spaceship.size.width = 135;
    game_controller->spaceship.size.height = 112;
    break;
  default:
    break;
  }
}
