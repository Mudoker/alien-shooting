#include "../../header/game/screen.h"
#include "../../assets/games/background.h"
#include "../../assets/games/welcome_screen/welcome.h"
#include "../../header/game/ui.h"

void in_game_screen(GameController *game_controller) {
  while (1) {
    draw_background(epd_bitmap_background);
    draw_spaceship(&game_controller->spaceship);
  }
  // Initialize the spaceship object
//   draw_background();
  // draw_capsuleARGB32(100, 100, 200, 200, 0x00AA0000);
  // init_spaceship(game_controller);
  // init_bullet(game_controller);
//   init_game(game_controller);

//   draw_health_bar(game_controller);
//   draw_spaceship(game_controller);

//   // init_all_enemies(game_controller);
//   // game_loop(game_controller);

//   int bullet_timer = 0; // Variable to track time elapsed for bullet

//   while (1) {

//     // Check if a character is received
//     char c = getUart();
//     switch (c) {
//     case 'w':
//       move_spaceship(game_controller, 0, -1);
//       break;
//     case 's':
//       move_spaceship(game_controller, 0, 1);
//       break;
//     case 'a':
//       move_spaceship(game_controller, -1, 0);
//       break;
//     case 'd':
//       move_spaceship(game_controller, 1, 0);
//       break;
//     default:
//       break;
//     }

    // // Move the bullet
    // move_bullet(game_controller, 0, -1);
    // // Increment the bullet timer
    // bullet_timer += 8000; // Assuming this is the delay between bullets

    // // Check if 5 seconds have elapsed
    // if (bullet_timer > 1000000) {   // 1 seconds
    //   init_bullet(game_controller); // Create a new bullet after 1 second
    //   bullet_timer = 0;             // Reset the timer
    // }
//   }
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

  draw_spaceship(&game_controller->spaceship);

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
