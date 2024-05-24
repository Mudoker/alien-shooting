// #include "../../header/game/game.h"
#include "../../header/game/cgame.h"
#include "../../header/global.h"
// #include "../../header/framebf.h"
// #include "../../assets/games/boss/small_boss.h"
// #include "../../assets/games/spaceship/blader.h"

void gameCli() {
  GameController cgame;
  cgame.screen = &((Display){
      .init_frame = &init_frame,
  });

  cgame.screen->init_frame(0, 0);

  // GameController game_controller_obj;
  // GameController *game_controller = &game_controller_obj;
  // init_controller(game_controller);

  // welcome_screen(game_controller);

  // stage_screen(game_controller);
  // in_game_screen(game_controller);
}
