#include "../../header/game/screen.h"
#include "../../assets/games/background.h"
#include "../../assets/games/welcome_screen/welcome.h"
#include "../../header/game/ui.h"

void in_game_screen(GameController *game_controller) {
  draw_background(epd_bitmap_background);
  boolean is_update = True;
  while (1) {
    if (is_update) {
      is_update = False;
      draw_spaceship(&game_controller->spaceship, epd_bitmap_background);
    }

    // Check if a character is received
    char c = getUart();
    switch (c) {
    case 'w':
      move_spaceship(game_controller, KEY_UP, 20);
      is_update = True;
      break;
    case 's':
      move_spaceship(game_controller, KEY_DOWN, 20);
      is_update = True;
      break;
    case 'a':
      move_spaceship(game_controller, KEY_LEFT, 20);
      is_update = True;
      break;
    case 'd':
      move_spaceship(game_controller, KEY_RIGHT, 20);
      is_update = True;
      break;
    default:
      break;
    }
  }
}

void stage_screen(GameController *game_controller) {
  draw_background(epd_bitmap_background);
  boolean is_update = True;
  while (1) {
    if (is_update) {
      if (game_controller->stage_level < 1) {
        game_controller->stage_level = 1;
      } else if (game_controller->stage_level > MAX_STAGES) {
        game_controller->stage_level = MAX_STAGES;
      }

      is_update = False;

      int yOffset = 40; // Start with the offset for the active stage
      for (int i = 0; i < MAX_STAGES; i++) {
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
    switch (c) {
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

void welcome_screen(GameController *game_controller) {
  draw_background(epd_bitmap_welcome);

  game_controller->spaceship.position.x =
      (SCREEN_WIDTH - game_controller->spaceship.size.width) / 2;
  game_controller->spaceship.position.y =
      (SCREEN_HEIGHT - game_controller->spaceship.size.height) / 2;

  // draw_spaceship(&game_controller->spaceship);

  while (1) {
    // Check if a character is received
    char c = getUart();
    switch (c) {
    case '1':
      //   stage_screen(game_controller);
      break;
    case '2':
      // change_stage(game_controller, 1);
      break;
    case '3':
      // in_game_screen(game_controller);
      break;
    default:
      break;
    }
  }
}
