// #include "../../header/game/game.h"
#include "../../header/game/cgame.h"
// #include "../../header/global.h"
// #include "../../header/framebf.h"
// #include "../../assets/games/boss/small_boss.h"
#include "../../assets/games/background.h"
#include "../../assets/games/spaceship/blader.h"
#include "../../header/utils.h"

void gameCli() {
  GameController cgame;
  cgame.screen = &((Display){.init_frame = &init_frame});
  cgame.screen->init_frame(0, 0);
  init_spaceship(&cgame, epd_blader[0], 124, 128, 0, 0);

  draw_background(epd_background[0]);
  draw_spaceship(&cgame.spaceship);

  //   welcome_screen(game_controller);

  // stage_screen(game_controller);
  // in_game_screen(game_controller);
}
