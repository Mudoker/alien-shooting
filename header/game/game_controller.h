#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "game_struct.h"
#include "../global.h"
#include "../framebf.h"
#include "../timer.h"

#define STEP 5
typedef struct GameController
{
    // int game_map[MAP_HEIGHT][MAP_WIDTH], is_game_active;
    // EnemyList enemy_list;
    Spaceship spaceship;

    // int weapon_x, weapon_y, weapon;
    // int score, diff, map, cancel_attack_timer;
} GameController;

void init_background(GameController *game_controller);
void init_spaceship(GameController *game_controller);
void init_bullet(GameController *game_controller);
void draw_spaceship(GameController *game_controller);
void move_spaceship(GameController *game_controller, int x_dir, int y_dir);
void draw_bullet(GameController *game_controller);
void move_bullet(GameController *game_controller, int x_dir, int y_dir);
void display_stages();

#endif