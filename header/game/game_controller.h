#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "../../src/game/headers/game_struct.h"

typedef struct GameController
{
    //int game_map[MAP_HEIGHT][MAP_WIDTH], is_game_active;
    //EnemyList enemy_list;
    Spaceship spaceship;

    // int weapon_x, weapon_y, weapon;
    // int score, diff, map, cancel_attack_timer;
} GameController;

void init_spaceship(GameController *game_controller);
void draw_spaceship(GameController *game_controller);

#endif