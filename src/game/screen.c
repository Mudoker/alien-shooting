#include "../../header/game/screen.h"
#include "../../header/timer.h"

void in_game_screen(GameController *game_controller)
{
    // Initialize the spaceship object
    init_spaceship(game_controller);
    init_bullet(game_controller);

    int bullet_timer = 0; // Variable to track time elapsed for bullet creation

    while (1)
    {

        // Check if a character is received
        char c = getUart();
        switch (c)
        {
        case 'w':
            move_spaceship(game_controller, 0, -1);
            break;
        case 's':
            move_spaceship(game_controller, 0, 1);
            break;
        case 'a':
            move_spaceship(game_controller, -1, 0);
            break;
        case 'd':
            move_spaceship(game_controller, 1, 0);
            break;
        default:
            break;
        }

        // Move the bullet
        move_bullet(game_controller, 0, -1);
        // Increment the bullet timer
        bullet_timer += 8000; // Assuming this is the delay between bullet movements

        // Check if 5 seconds have elapsed
        if (bullet_timer > 1000000)
        {                                 // 1 seconds
            init_bullet(game_controller); // Create a new bullet after 1 second
            bullet_timer = 0;             // Reset the timer
        }
    }
}

void stage_screen(GameController *game_controller)
{
    // Display the stages
    init_stages(game_controller);
    while (1)
    {
        // Check if a character is received
        char c = getUart();
        switch (c)
        {
        case '1':
            in_game_screen(game_controller);
            break;
        case '2':
            in_game_screen(game_controller);
            break;
        case '3':
            in_game_screen(game_controller);
            break;
        case '4':
            in_game_screen(game_controller);
            break;
        // 5~8
        case '9':
            in_game_screen(game_controller);
            break;
        default:
            break;
        }
    }
}
