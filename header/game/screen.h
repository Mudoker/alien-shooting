#ifndef SCREEN_H
#define SCREEN_H

#include "../../header/game/cgame.h"
#include "../../header/timer.h"
#include "./cgame.h"

void in_game_screen(GameController *game_controller);
void stage_screen(GameController *game_controller);
void ship_selection_screen(GameController *game_controller);
void result_screen(GameController *game_controller, int defeat_count);
void welcome_screen(GameController *game_controller);
void in_game_screen(GameController *game_controller);
void stage_screen(GameController *game_controller);
void ship_selection_screen(GameController *game_controller);
void manage_command(GameController *game_controller, char *log);

#endif
