// #include "../../header/game/game.h"
#include "../../header/game/cgame.h"
#include "../../header/game/screen.h"
// #include "../../header/global.h"
// #include "../../header/framebf.h"
// #include "../../assets/games/boss/small_boss.h"
// #include "../../assets/games/spaceship/blader.h"
#include "../../header/utils.h"

void gameCli() {
  GameController cgame;
  init_controller(&cgame);
  if (cgame.page == WELCOME) {
    welcome_screen(&cgame);
  } else if (cgame.page == STAGE) {
    stage_screen(&cgame);
  } else if (cgame.page == IN_GAME) {
    in_game_screen(&cgame);
  }
}
