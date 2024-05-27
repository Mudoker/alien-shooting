#include "../../header/game/cgame.h"
#include "../../header/game/screen.h"
#include "../../header/utils.h"

void gameCli()
{
  GameController cgame;
  init_controller(&cgame);

  uart_show_info();

  if (cgame.page == WELCOME)
  {
    welcome_screen(&cgame);
  }
  else if (cgame.page == STAGE)
  {
    stage_screen(&cgame);
  }
  else if (cgame.page == IN_GAME)
  {
    in_game_screen(&cgame);
  }
}
