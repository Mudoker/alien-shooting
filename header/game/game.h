#ifndef GAME_H
#define GAME_H

#include "ui.h"

void gameCli();
void clear_image(int x, int y, int w, int h);
void update_position_game(int x_dir, int y_dir, int *offset_x, int *offset_y, const unsigned long *spaceship);

#endif