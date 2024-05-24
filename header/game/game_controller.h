#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "game_struct.h"
#include "../global.h"
#include "../framebf.h"
#include "../timer.h"
#include "ui.h"


#define STEP 20
typedef struct GameController
{
    // int game_map[MAP_HEIGHT][MAP_WIDTH], is_game_active;
    // EnemyList enemy_list;
    Stage stages[9];
    Spaceship spaceship;
    Alien alien;
    Alien aliens[5];
    int alien_count;
    int stage_level;
    // int weapon_x, weapon_y, weapon;
    // int score, diff, map, cancel_attack_timer;
} GameController;

extern int pos_x[5];
extern int pos_y[4] ;
extern int row_counts[4];
void init_background(GameController *game_controller);
void init_spaceship(GameController *game_controller);
void init_bullet(GameController *game_controller);
void init_alien(Alien *alien, GameController *game_controller);
void move_aliens_to_positions(GameController *game_controller);
int all_aliens_reached(GameController *game_controller);
void game_loop(GameController *game_controller);


// Functions to initialize

void init_controller(GameController *game_controller);
void init_spaceship(GameController *game_controller);
void init_bullet(GameController *game_controller);
void init_stages(GameController *game_controller);
void init_game(GameController *game_controller);



void draw_spaceship(GameController *game_controller);
void draw_bullet(GameController *game_controller);
void draw_stages(GameController *game_controller);
void draw_background();
void draw_health_bar(GameController *game_controller);
void draw_welcome_screen();

void move_spaceship(GameController *game_controller, int x_dir, int y_dir);
void move_bullet(GameController *game_controller, int x_dir, int y_dir);
void copy_alien(Alien *dest, const Alien *src);
void draw_aliens(GameController *game_controller);
void send_serial(char *message);
char* itoa(int num);

void change_stage(GameController *game_controller, int diff);

#endif
