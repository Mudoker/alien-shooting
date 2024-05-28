#include "../../header/game/screen.h"
#include "../../header/game/ui.h"

// Function prototypes
void result_screen(GameController *game_controller);
void lose_screen(GameController *game_controller, int seconds);
void win_final_screen(GameController *game_controller, int seconds);
void win_screen(GameController *game_controller, int seconds);

void in_game_screen(GameController *game_controller)
{
  game_controller->current_wave = 0;
  init_wave(game_controller);

  draw_background();

  // Reset spaceship position
  game_controller->spaceship.position.x =
      (SCREEN_WIDTH - game_controller->spaceship.size.width) / 2;
  game_controller->spaceship.position.y =
      (SCREEN_HEIGHT - game_controller->spaceship.size.height);

  draw_spaceship(game_controller);
  draw_health_bar(game_controller);
  draw_alien(game_controller);
  
  int last_powerup_update = 0; // Add this variable to track the time
  int bullet_timer = 0;
  int fire_timer = 0;
  int alien_move_timer = 0;
  int alien_move_step = 10;
  int power_up_timer = 0;
  int powerup_active = 0;
  int next_powerup_time = 8000; // Initial delay for the first power-up
  static int  shieldTimer = 0;
  // lighting();

  while (1)
  {
    // Check if a character is received
    clear_wave(game_controller);
    char c = getUart();
    switch (c)
    {
    case 'w':
      manage_command(game_controller, "Moved spaceship to up", c, 1);
      move_spaceship(game_controller, KEY_UP, 14);
      break;
    case 's':
      manage_command(game_controller, "Moved spaceship to down", c, 1);
      move_spaceship(game_controller, KEY_DOWN, 14);
      break;
    case 'a':
      manage_command(game_controller, "Moved spaceship to left", c, 1);
      move_spaceship(game_controller, KEY_LEFT, 14);
      break;
    case 'd':
      manage_command(game_controller, "Moved spaceship to right", c, 1);
      move_spaceship(game_controller, KEY_RIGHT, 14);
      break;
    default:
      handle_wrong_input(game_controller, c);
      break;
    }

    // Increment the bullet timer
    bullet_timer += 30;
    alien_move_timer += 30;
    power_up_timer += 700;

    if (fire_timer == 5)
    {
      add_bullet(game_controller);
      fire_timer = 0;
    }

    // Bullet movement
    if (bullet_timer >= 10000000)
    { // 1 second for smoother bullet movement
      for (int i = 0; i < game_controller->bullet_on_screen_count; i++)
      {
        for (int j = 0; j < game_controller->spaceship.bullet_bonus + 1; j++)
        {
          if (game_controller->spaceship.bullets[i][j].name != NULL)
          {
            move_bullet(game_controller, i, 20);
          }
        }
      }
      fire_timer++;
      bullet_timer = 0;
    }

    // Alien movement
    if (alien_move_timer >= 10000000)
    { // 1 second for smoother alien movement
      move_aliens(game_controller, alien_move_step);
      alien_move_timer = 0;
    }
    if (power_up_timer >= 10000000)
    {
      move_PU_to_position(game_controller);

      power_up_timer = 0;
    }
   
      game_controller->spaceship.shieldTimer -= 80;

  }
}

void stage_screen(GameController *game_controller)
{
  draw_background();
  boolean is_update = True;
  while (1)
  {
    if (is_update)
    {
      if (game_controller->stage_level < 1)
      {
        game_controller->stage_level = 1;
      }
      else if (game_controller->stage_level > MAX_STAGES)
      {
        game_controller->stage_level = MAX_STAGES;
      }

      is_update = False;

      int yOffset = 300; // Start with the offset for the active stage
      for (int i = 0; i < MAX_STAGES; i++)
      {
        int buttonState = (game_controller->stage_level ==
                           i + 1); // 1 for current, 0 for inactive

        // Draw the button with the calculated offset and state
        draw_button(SCREEN_WIDTH / 2 - 150, yOffset, 300, 60,
                    game_controller->stages[i].name, buttonState);

        yOffset += 120; // Increase the y-offset for the next button
      }
    }

    // Check if a character is received
    char c = getUart();
    switch (c)
    {
    case 'w':
      game_controller->stage_level--;
      is_update = True;

      manage_command(game_controller, "Moved up to select another stage level", c, 1);
      break;
    case 's':
      game_controller->stage_level++;
      is_update = True;

      manage_command(game_controller, "Moved down to select another stage level", c, 1);
      break;
    case '\n':
      manage_command(game_controller, "Selected a stage level to play", c, 1);
      in_game_screen(game_controller);
      break;
    default:
      handle_wrong_input(game_controller, c);
      break;
    }
  }
}

void ship_selection_screen(GameController *game_controller)
{
  int order = 1;

  Spaceship *current_ship_option = init_current_ship_option();

  draw_background();
  draw_ship_selection_page();

  draw_spaceship_option(&game_controller->spaceship, order, 0, &current_ship_option);
  draw_arrows(order);

  while (1)
  {
    // Check if a character is received
    char c = getUart();
    switch (c)
    {
    case 'a':
      manage_command(game_controller, "Moved left to select another spaceship", c, 1);
      if (order > 1)
      {
        order--;
        draw_spaceship_option(&game_controller->spaceship, order, 1, &current_ship_option);
        draw_arrows(order);
      }
      break;
    case 'd':
      manage_command(game_controller, "Moved right to select another spaceship", c, 1);

      if (order < 3)
      {
        order++;
        draw_spaceship_option(&game_controller->spaceship, order, 1, &current_ship_option);
        draw_arrows(order);
      }
      break;
    case '\n':
      manage_command(game_controller, "Selected a spaceship", c, 1);

      change_spaceship(game_controller, order);
      welcome_screen(game_controller);
      return;
    default:
      handle_wrong_input(game_controller, c);
      break;
    }
  }
}

void result_screen(GameController *game_controller)
{
  int seconds = 20; // TODO: make it dynamic from the timer

  if (seconds > 60)
  {
    lose_screen(game_controller, seconds);
  }

  if (game_controller->stage_level == MAX_STAGES)
  {
    win_final_screen(game_controller, seconds);
  }
  else
  {
    win_screen(game_controller, seconds);
  }
}

void lose_screen(GameController *game_controller, int seconds)
{
  draw_lose_screen(game_controller, seconds);

  while (1)
  {
    char c = getUart();
    switch (c)
    {
    case 'y':
      manage_command(game_controller, "Redirected to the game screen from lose result screen", c, 1);
      in_game_screen(game_controller);
      break;
    case 'n':
      manage_command(game_controller, "Redirected to the welcome screen from lose result screen", c, 1);
      welcome_screen(game_controller);
      break;
    default:
      handle_wrong_input(game_controller, c);
      break;
    }
  }
}

void win_final_screen(GameController *game_controller, int seconds)
{
  draw_win_final_screen(game_controller, seconds);

  while (1)
  {
    char c = getUart();
    switch (c)
    {
    case 'n':
      manage_command(game_controller, "Redirected to the welcome screen from win final result screen", c, 1);
      welcome_screen(game_controller);
      break;
    default:
      handle_wrong_input(game_controller, c);
      break;
    }
  }
}

void win_screen(GameController *game_controller, int seconds)
{
  draw_win_screen(game_controller, seconds);

  while (1)
  {
    char c = getUart();
    switch (c)
    {
    case 'y':
      manage_command(game_controller, "Redirected to the next stage's game screen from win result screen", c, 1);
      game_controller->stage_level++;
      in_game_screen(game_controller);
      break;
    case 'n':
      manage_command(game_controller, "Redirected to the welcome screen from win result screen", c, 1);
      welcome_screen(game_controller);
      break;
    default:
      handle_wrong_input(game_controller, c);
      break;
    }
  }
}

void welcome_screen(GameController *game_controller)
{
  draw_welcome_screen();

  game_controller->spaceship.position.x =
      (SCREEN_WIDTH - game_controller->spaceship.size.width) / 2;
  game_controller->spaceship.position.y =
      (SCREEN_HEIGHT - game_controller->spaceship.size.height) / 2;

  draw_spaceship(game_controller);

  while (1)
  {
    char c = getUart();
    switch (c)
    {
    case '1':
      manage_command(game_controller, "Redirected to the stage screen from welcome screen", c, 1);
      stage_screen(game_controller);
      break;
    case '2':
      manage_command(game_controller, "Redirected to the spaceship selection screen from welcome screen", c, 1);
      ship_selection_screen(game_controller);
      break;
    default:
      handle_wrong_input(game_controller, c);
      break;
    }
  }
}

void manage_command(GameController *game_controller, char *log, char *c, int is_positive)
{
  game_controller->command_count++;
  uart_logs(game_controller->command_count, log, c, is_positive);
}

void handle_wrong_input(GameController *game_controller, char *c)
{
  if (c != NULL && c != '\n')
  {
    manage_command(game_controller, "Wrong input", c, 0);
  }
}
