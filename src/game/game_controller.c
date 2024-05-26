// #include "../../header/game/game_controller.h"
// #include "../../assets/games/alient/alient_1.h"
// #include "../../assets/games/background.h"
// #include "../../assets/games/bullet/bullet_lv1.h"
// #include "../../assets/games/spaceship/blader.h"
// #include "../../assets/games/stages.h"
// #include "../../header/uart.h"
// #include "../utils/memcpy.h"
// #include "../utils/randomNum.h"
// #include "../../assets/games/welcome.h"

// void init_controller(GameController *game_controller)
// {
//     // game_controller->stage_level = 1;
//     // init_background(game_controller);
//     init_spaceship(game_controller);
//     //init_bullet(game_controller);
//     init_stages(game_controller);
// }
// void init_all_enemies(GameController *game_controller);
// void init_background(GameController *game_controller) {
//   draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
//                   background[0]);
// }


// // Initialize the spaceship object
// void init_spaceship(GameController *game_controller)
// {
//     Spaceship your_spaceship;
//     // Spaceship's size
//     your_spaceship.size.width = 124;
//     your_spaceship.size.height = 128;

//     // Initial position of the spaceship
//     // your_spaceship.position.x = (SCREEN_WIDTH - your_spaceship.size.width) / 2;
//     // your_spaceship.position.y = SCREEN_HEIGHT - your_spaceship.size.height;

//   // Image of the spaceship
//   your_spaceship.sprite = blader[0];
//   game_controller->spaceship = your_spaceship;

//   draw_spaceship(game_controller);
//   // draw_alien(game_controller);
// }

// void init_bullet(GameController *game_controller) {
//   Bullet bullet;
//   bullet.position.x = game_controller->spaceship.position.x +
//                       (game_controller->spaceship.size.width - 12) / 2;
//   bullet.position.y = game_controller->spaceship.position.y - 48 - 20;
//   bullet.sprite = epd_bitmap_bullet_allArray[0];
//   game_controller->spaceship.bullet = bullet;
//   draw_bullet(game_controller);
// }
// int pos_x[5] = {0, 130, 260, 390, 520};
// int pos_y[4] = {0, 109, 218, 327};
// int row_counts[4] = {0, 0, 0, 0};
// int col_counts[5] = {0, 0, 0, 0, 0};

// // void init_alien(Alien *enemy, GameController *game_controller)
// // {
// //     init_seed();
// //     Alien alien;
// //     boolean valid_pos = False;

// //     while (!valid_pos)
// //     {
// //         int rand_col = randomNum() % 5;
// //         int rand_row = randomNum() % 4;

// //         if (col_counts[rand_col] < MAX_ENEMY_IN_COL && row_counts[rand_row] <
// //         MAX_ENEMY_IN_ROW)
// //         {
// //             alien.position.x = pos_x[rand_col];
// //             alien.position.y = pos_y[rand_row];
// //             valid_pos = True;

// //             // Update the counts for this row and column
// //             col_counts[rand_col]++;
// //             row_counts[rand_row]++;
// //         }
// //     }

// //     uart_puts("alien x: ");
// //     uart_puts(itoa(alien.position.x));
// //     uart_puts("alien y: ");
// //     uart_puts(itoa(alien.position.y));
// //     uart_puts("\n");
// //     alien.sprite = epd_bitmap_alient_allArray[0];
// //     game_controller->alien = alien;

// //     draw_alien(game_controller);
// // }

// void init_alien(Alien *alien, GameController *game_controller) {
//   init_seed();
//   int valid_pos = 0, attempts = 0;
//   int rand_col, rand_row;

//   while (!valid_pos &&
//          attempts <
//              50) { // Limit the number of attempts to prevent infinite loop
//     rand_col = randomNum() % 5;
//     rand_row = randomNum() % 4;

//     if (col_counts[rand_col] < MAX_ENEMY_IN_COL &&
//         row_counts[rand_row] < MAX_ENEMY_IN_ROW) {
//       alien->position.x = pos_x[rand_col];
//       alien->position.y = 0;
//       alien->target.x = pos_x[rand_col];
//       alien->target.y = pos_y[rand_row];
//       alien->reached_target = 0;
//       alien->sprite = (unsigned long *)epd_bitmap_alient_allArray[0];

//       valid_pos = 1;
//       col_counts[rand_col]++;
//       row_counts[rand_row]++;
//     }
//     attempts++;
//   }
//   if (valid_pos) {
//     copy_alien(&game_controller->aliens[game_controller->alien_count++], alien);

//     uart_puts("Alien initialized\n");
//   } else {
//     uart_puts("Failed to place alien\n");
//   }
// }

// void move_aliens_to_positions(GameController *game_controller) {
//   int all_reached = 1;
//   for (int i = 0; i < game_controller->alien_count; i++) {
//     Alien *alien = &game_controller->aliens[i];
//     if (!alien->reached_target) {
//       clear_image(alien->position.x, alien->position.y, 130, 109,
//                   background[0]);
//       if (alien->position.y < alien->target.y) {
//         alien->position.y += 2; // Consider making this a configurable parameter
//         all_reached = 0;
//       } else {
//         alien->reached_target = 1;
//       }
//       draw_aliens(game_controller); // Draw all aliens for consistency
//     }
//   }

//   if (all_reached) {
//     uart_puts("All aliens reached their grid positions.\n");
//   }
// }

// void game_loop(GameController *game_controller) {
//   init_all_enemies(game_controller); // Make sure aliens are initialized before
//                                      // the loop starts

//   while (!all_aliens_reached(game_controller)) {
//     move_aliens_to_positions(game_controller);
//     wait_msec(16); // Correct timing for approximately 60 FPS
//   }
// }

// int all_aliens_reached(GameController *game_controller) {
//   for (int i = 0; i < MAX_ENEMY; i++) {
//     if (!game_controller->aliens[i].reached_target) {
//       return 0; // If any alien hasn't reached its position, return false
//     }
//   }
//   return 1; // All aliens have reached their positions
// }

// void draw_aliens(GameController *game_controller) {
//   for (int i = 0; i < game_controller->alien_count; i++) {
//     Alien *alien = &game_controller->aliens[i];
//     draw_image_object(alien->position.x, alien->position.y, 130, 109,
//                       alien->sprite, background[0]);
//   }
// }

// void init_all_enemies(GameController *game_controller) {
//   for (int i = 0; i < 5;
//        i++) { // Assuming 5 is the total number of aliens you can have
//     init_alien(&game_controller->aliens[i], game_controller);
//   }
// }

// void copy_alien(Alien *dest, const Alien *src) {
//   dest->position.x = src->position.x;
//   dest->position.y = src->position.y;
//   dest->target.x = src->target.x;
//   dest->target.y = src->target.y;
//   dest->reached_target = src->reached_target;
//   dest->sprite = src->sprite;
// }

// // void init_all_enemies(GameController *game_controller)
// // {
// //     Alien enemies[MAX_ENEMY];
// //     for (int i = 0; i < MAX_ENEMY; i++)
// //     {
// //         init_alien(&enemies[i], game_controller);
// //     }
// // }


// void init_stages(GameController *game_controller)
// {
//     for (int i = 0; i < 9; i++) {
//         Stage stage;
//         stage.level = i + 1;
//         strcpy(stage.name, "Stage ");
//         strcat(stage.name, int_to_string(i + 1));
//         game_controller->stages[i] = stage;
//     }
//     game_controller->stage_level = 1;
//     // draw_stages(game_controller);
// }

// void init_game(GameController *game_controller)
// {
//     game_controller->spaceship.health = 100;
//     game_controller->spaceship.position.x = (SCREEN_WIDTH - game_controller->spaceship.size.width) / 2;
//     game_controller->spaceship.position.y = SCREEN_HEIGHT - game_controller->spaceship.size.height;
// }
//     // draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, background[0]);
// // Draw the spaceship on the screen
// void draw_spaceship(GameController *game_controller) {
//   draw_image_object(game_controller->spaceship.position.x,
//                     game_controller->spaceship.position.y,
//                     game_controller->spaceship.size.width,
//                     game_controller->spaceship.size.height,
//                     game_controller->spaceship.sprite,
//                     background[0]);
// }


// // Draw the bullet on the screen
// void draw_bullet(GameController *game_controller) {
//   draw_image_object(game_controller->spaceship.bullet.position.x,
//                     game_controller->spaceship.bullet.position.y, 12, 48,
//                     game_controller->spaceship.bullet.sprite,
//                     background[0]);
// }


// void draw_stages(GameController *game_controller)
// {
//     for (int i = 0; i < 9; i++) {
//         if (game_controller->stages[i].level == game_controller->stage_level) {
//             draw_button(SCREEN_WIDTH / 2 - 150, 100 + i * 80, 300, 40, game_controller->stages[i].name, 1);
//             
//         } else {
//             draw_button(SCREEN_WIDTH / 2 - 150, 100 + i * 80, 300, 40, game_controller->stages[i].name, 0);
//         }
//     }
// }

// void draw_background()
// {
//     draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, background[0]);
// }

// void draw_health_bar(GameController *game_controller)
// {
//     float healthPercentage = (float) game_controller->spaceship.health / 100.0;
//     draw_capsuleARGB32(50, 50, 300, 50, 0x00FF0000, 1, healthPercentage);
// }

// void draw_welcome_screen()
// {
//     draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_welcome);
// }


// void move_spaceship(GameController *game_controller, int x_dir, int y_dir)
// {
//     Spaceship *spaceship = &game_controller->spaceship;
//     clear_image(spaceship->position.x, spaceship->position.y, spaceship->size.width, spaceship->size.height, background[0]);

//   if (spaceship->position.x + x_dir * STEP >= 0 &&
//       spaceship->position.x + x_dir * STEP <=
//           SCREEN_WIDTH - spaceship->size.width) {
//     spaceship->position.x += x_dir * STEP;
//   }

//   if (spaceship->position.y + y_dir * STEP >= 0 &&
//       spaceship->position.y + y_dir * STEP <=
//           SCREEN_HEIGHT - spaceship->size.height) {
//     spaceship->position.y += y_dir * STEP;
//   }
//   draw_spaceship(game_controller);
// }

// void move_bullet(GameController *game_controller, int x_dir, int y_dir) {
//   Spaceship *spaceship = &game_controller->spaceship;
//   Bullet *bullet = &spaceship->bullet;
//   clear_image(bullet->position.x, bullet->position.y, 12, 48,
//               background[0]);
//   // draw_image(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,background[0]);

//   if (bullet->position.x + x_dir * 48 >= 0 &&
//       bullet->position.x + x_dir * 48 <= SCREEN_WIDTH - 12) {
//     bullet->position.x += x_dir * 48;
//   }

//   if (bullet->position.y + y_dir * 48 >= 0 &&
//       bullet->position.y + y_dir * 48 <= SCREEN_HEIGHT - 48) {
//     bullet->position.y += y_dir * 48;
//   }

//   draw_bullet(game_controller);
//   wait_msec(8000);
// }

// char *itoa(int num) {
//   static char str[12]; // Large enough for an integer, includes space for
//                        // negative sign and null terminator
//   int i = 0;
//   int isNegative = 0;

//   // Handle 0 explicitly, otherwise, an empty string is printed for 0
//   if (num == 0) {
//     str[i++] = '0';
//     str[i] = '\0';
//     return str;
//   }

//   // In standard itoa(), negative numbers are handled only with base 10
//   // Otherwise, numbers are considered unsigned
//   if (num < 0) {
//     isNegative = 1;
//     num = -num;
//   }

//   // Process individual digits
//   while (num != 0) {
//     int rem = num % 10;
//     str[i++] = rem + '0'; // Convert int to char
//     num = num / 10;
//   }

//   // If number is negative, append '-'
//   if (isNegative)
//     str[i++] = '-';

//   str[i] = '\0'; // Append string terminator

//   // Reverse the string
//   int start = 0;
//   int end = i - 1;
//   while (start < end) {
//     char temp = str[start];
//     str[start] = str[end];
//     str[end] = temp;
//     start++;
//     end--;
//   }

//   return str;
// }

// void change_stage(GameController *game_controller, int diff)
// {
//     draw_button(SCREEN_WIDTH / 2 - 150, 100 + (game_controller->stage_level - 1) * 80, 300, 40, game_controller->stages[game_controller->stage_level - 1].name, 0);
//     game_controller->stage_level += diff;
//     if (game_controller->stage_level < 1)
//     {
//         game_controller->stage_level = 9;
//     }
//     else if (game_controller->stage_level > 9)
//     {
//         game_controller->stage_level = 1;
//     }
//     draw_button(SCREEN_WIDTH / 2 - 150, 100 + (game_controller->stage_level - 1) * 80, 300, 40, game_controller->stages[game_controller->stage_level - 1].name, 1);
// }
