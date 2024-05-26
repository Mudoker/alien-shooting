#include "../../header/game/screen.h"
#include "../../header/game/ui.h"

#include "../../assets/games/background.h"
#include "../../assets/games/ship_selection_screen/ship_selection_title.h"
#include "../../assets/games/ship_selection_screen/ship_selection_button.h"
#include "../../assets/games/ship_selection_screen/arrow_left.h"
#include "../../assets/games/ship_selection_screen/arrow_right.h"

#include "../../assets/games/spaceship/ship_lev1.h"
#include "../../assets/games/spaceship/blader.h"
#include "../../assets/games/spaceship/ship_lev3.h"

void in_game_screen(GameController *game_controller)
{
  draw_background();

  game_controller->spaceship.position.x = (SCREEN_WIDTH - game_controller->spaceship.size.width) / 2;
  game_controller->spaceship.position.y = SCREEN_HEIGHT - game_controller->spaceship.size.height;
  draw_spaceship(game_controller);
  draw_health_bar(game_controller);

  int bullet_timer = 0;
  int fire_timer = 0;

  while (1)
  {
    // Check if a character is received
    char c = getUart();
    switch (c)
    {
    case 'w':
      move_spaceship(game_controller, KEY_UP, 10);
      deal_damage(game_controller);
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

    if (fire_timer == 5)
    {
      add_bullet(game_controller,
                 game_controller->spaceship.position.x +
                     game_controller->spaceship.size.width / 2 - 6,
                 game_controller->spaceship.position.y -
                     game_controller->spaceship.size.height / 2);
      fire_timer = 0;
    }

    // Bullet movement
    if (bullet_timer >= 10000000)
    { // 1 second for smoother bullet movement
      for (int i = 0; i < MAX_BULLETS; i++)
      {
        if (game_controller->spaceship.bullet[i].name != NULL)
        {
          move_bullet(&game_controller->spaceship.bullet[i], 20);
        }
      }
      fire_timer++;
      bullet_timer = 0;
    }
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

void ship_selection_screen(GameController *game_controller)
{
  int order = 1;

  draw_background(epd_bitmap_background);
  draw_image(0, 60, SCREEN_WIDTH, 186, epd_bitmap_ship_selection_title);
  draw_image(215, 650, 350, 103, epd_bitmap_ship_selection_button);

  draw_spaceship_option(&game_controller->spaceship); // TODO: Pass order
  draw_arrows(epd_bitmap_arrow_left, epd_bitmap_arrow_right, order);

  while (1)
  {
    // Check if a character is received
    char c = getUart();
    switch (c)
    {
    case 'a':
      if (order > 1)
      {
        order--;
        draw_spaceship_option(&game_controller->spaceship); // TODO: Pass order
        draw_arrows(epd_bitmap_arrow_left, epd_bitmap_arrow_right, order);
      }
      break;
    case 'd':
      if (order < 3)
      {
        order++;
        draw_spaceship_option(&game_controller->spaceship); // TODO: Pass order
        draw_arrows(epd_bitmap_arrow_left, epd_bitmap_arrow_right, order);
      }
      break;
    case '\n':
      // clear the current spaceship option
      clear_image((SCREEN_WIDTH - game_controller->spaceship.size.width) / 2,
                  (SCREEN_HEIGHT - game_controller->spaceship.size.height) / 2,
                  game_controller->spaceship.size.width,
                  game_controller->spaceship.size.height,
                  &game_controller->spaceship);

      switch (order)
      {
      case 1:
        game_controller->spaceship.sprite = epd_bitmap_ship_l1_allArray[0];
        break;
      case 2:
        game_controller->spaceship.sprite = epd_blader[0];
        break;
      case 3:
        game_controller->spaceship.sprite = epd_bitmap_ship_l3_allArray[0];
        break;
      default:
        break;
      }

      draw_spaceship_option(&game_controller->spaceship);
      return;
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
      ship_selection_screen(game_controller);
      break;
    default:
      break;
    }
  }
}
