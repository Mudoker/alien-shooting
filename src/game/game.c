#include "../../header/game/game.h"
// #include "../../header/framebf.h"
// #include "../../assets/games/boss/small_boss.h"
// #include "../../assets/games/spaceship/blader.h"

void gameCli()
{
    framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    GameController game_controller_obj;
    GameController *game_controller = &game_controller_obj;

    stage_screen(game_controller);
    // in_game_screen(game_controller);
}