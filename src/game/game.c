#include "../../header/game/game.h"
//#include "../../header/framebf.h"
// #include "../../header/global.h"
// #include "../../assets/games/boss/small_boss.h"
// #include "../../assets/games/spaceship/blader.h"

void gameCli() {
    framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    GameController game_controller_obj;
    GameController *game_controller = &game_controller_obj;

    //init_spaceship(game_controller);
    in_game_screen(game_controller);

    // int ship_position_X = (SCREEN_WIDTH - 124) / 2, ship_position_Y = SCREEN_HEIGHT - 128;
    // const unsigned long *boss = epd_bitmap_boss_allArray[0];
    // const unsigned long *spaceship = epd_bitmap_spaceship_allArray[0];
    // draw_image(ship_position_X, ship_position_Y, 124, 128, spaceship);
    // draw_image(0, 0, 467, 301, boss);

    // while (1) {

    //     char c = uart_getc();;
    //     switch (c) {
    //         case 'w':
    //             update_position_game(0, -1, &ship_position_X, &ship_position_Y, spaceship);
    //             break;
    //         case 's':
    //             update_position_game(0, 1, &ship_position_X, &ship_position_Y, spaceship);
    //             break;
    //         case 'a':
    //             update_position_game(-1, 0, &ship_position_X, &ship_position_Y, spaceship);
    //             break;
    //         case 'd':
    //             update_position_game(1, 0, &ship_position_X, &ship_position_Y, spaceship);
    //             break;
    //         default:
    //             break;
    //     }
    //     draw_image(ship_position_X, ship_position_Y, 124, 128, spaceship);
    //     //clear_image(0, 0, 467, 301);
    //     draw_image(0, 0, 467, 301, boss);
    // }
}

// void update_position_game(int x_dir, int y_dir, int *offset_x, int *offset_y, const unsigned long *spaceship) {
//   // Check if the new offset values are within the image bounds
//     clear_image(*offset_x, *offset_y, 124, 128);
//     //
//     if (*offset_x + x_dir * 5 >= 0 &&
//         *offset_x + x_dir * 5 <= SCREEN_WIDTH - 124) {
//         // Update the offset values
//         *offset_x += x_dir * 5;
//     }

//     // Check if the new offset values are within the image bounds
//     if (*offset_y + y_dir * 5 >= 0 &&
//         *offset_y + y_dir * 5 <= SCREEN_HEIGHT - 128) {
//         // Update the offset values
//         *offset_y += y_dir * 5;
        
//     }
// }