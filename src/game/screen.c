#include "../../header/game/screen.h"
#include "../../header/game/ui.h"

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
  // draw_health_PU(game_controller);
  // draw_shield_PU(game_controller);

  int bullet_timer = 0;
  int fire_timer = 0;
  int alien_move_timer = 0;
  int alien_move_step = 10;

  while (1)
  {
    // Check if a character is received
    clear_wave(game_controller);
    char c = getUart();
    switch (c)
    {
    case 'w':
      move_spaceship(game_controller, KEY_UP, 10);
      break;
    case 's':
      move_spaceship(game_controller, KEY_DOWN, 10);
      break;
    case 'a':
      move_spaceship(game_controller, KEY_LEFT, 10);
      break;
    case 'd':
      move_spaceship(game_controller, KEY_RIGHT, 10);
      break;
    default:
      break;
    }

    // Increment the bullet timer
    bullet_timer += 30;
    alien_move_timer += 30;

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
          if (game_controller->spaceship.bullet[i][j].name != NULL)
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
  }

  // game_loop(game_controller);
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

      int yOffset = 40; // Start with the offset for the active stage
      for (int i = 0; i < MAX_STAGES; i++)
      {
        int buttonState = (game_controller->stage_level ==
                           i + 1); // 1 for current, 0 for inactive

        // Draw the button with the calculated offset and state
        draw_button(SCREEN_WIDTH / 2 - 150, yOffset, 300, 60,
                    game_controller->stages[i].name, buttonState);

        yOffset += 90; // Increase the y-offset for the next button
      }
    }

    // Check if a character is received
    char c = getUart();
    switch (c)
    {
    case 'w':
      game_controller->stage_level--;
      is_update = True;
      break;
    case 's':
      game_controller->stage_level++;
      is_update = True;
      break;
    case '\n':
      in_game_screen(game_controller);
      break;
    default:
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
    // Check if a character is received
    char c = getUart();
    switch (c)
    {
    case '1':
      stage_screen(game_controller);
      break;
    case '2':
      // change_stage(game_controller, 1);
      break;
    case '3':
      in_game_screen(game_controller);
      break;
    default:
      break;
    }
  }
}
