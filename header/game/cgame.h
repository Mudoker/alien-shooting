#ifndef CGAME_H
#define CGAME_H

#include "../framebf.h"
#include "../global.h"
#include "../timer.h"
#include "game_struct.h"
#include "ui.h"

#define MAX_ALIENS 20
#define MAX_STAGES 9

typedef enum
{
  KEY_UP = 0,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT,
} Key;

typedef enum
{
  STAGE_1 = 0,
  STAGE_2,
  STAGE_3,
  STAGE_4,
  STAGE_5,
  STAGE_6,
  STAGE_7,
  STAGE_8,
  STAGE_9,
} StageLevel;

// Current page
typedef enum
{
  WELCOME = 0,
  STAGE,
  IN_GAME,
} Page;

typedef enum
{
  BULLET_BONUS = 0,
  HEALTH_BONUS,
  SHIELD_BONUS,
} Badge;

typedef struct Display Display;

typedef struct GameController
{
  // Attributes
  Stage stages[MAX_STAGES];
  Spaceship spaceship;
  // Alien alien;
  Alien *aliens;
  int alien_count;
  int stage_level;
  int current_wave;
  Display *screen;
  int bullet_on_screen_count;
  Page page;
  int score;
  PowerUp powerup;
  int command_count;

  // Methods
  void (*init)(void);
  void (*destroy)(void);
  int (*getInput)(void);
  void (*update)(void);
  void (*render)(void);
} GameController;

struct Display
{
  void (*init_frame)(int offset_x, int offset_y);
  void (*draw_sprite)(int x, int y, int width, int height,
                      const unsigned long *sprite);
};

// Function prototypes
void gameCli();
void init_frame(int offset_x, int offset_y);
void init_spaceship(GameController *game_controller,
                    const unsigned long *sprite, int width, int height, int x,
                    int y);
Spaceship *init_current_ship_option();
void init_bullet(GameController *game_controller, const unsigned long *sprite,
                 int width, int height, int x, int y, int index);
void init_stages(GameController *game_controller);
void init_controller(GameController *game_controller);
void init_alien(Alien *Alien, const unsigned long *sprite, int width, int height, int x, int y);
void init_wave(GameController *game_controller);

void draw_background();
void draw_health_bar(GameController *game_controller);
void draw_welcome_screen();
void draw_alien(GameController *game_controller);
void draw_health_PU(GameController *game_controller);
void draw_shield_PU(GameController *game_controller);
char *itoa(int num);

void draw_spaceship(GameController *game_controller);
void draw_spaceship_option(Spaceship *spaceship, int order, int clear, Spaceship *current_ship_option);
void draw_ship_selection_page();
void draw_arrows(int order);
void change_spaceship(GameController *game_controller, int order);

void collision_detection(GameController *game_controller);
void clear_wave(GameController *game_controller);
void move_alien(GameController *game_controller, int step);

void move_spaceship(GameController *game_controller, int key, int step);
void move_bullet(GameController *game_controller, int index, int step);

void add_bullet(GameController *game_controller);

void deal_damage(GameController *game_controller, int index);

void draw_badge(int badge);

void draw_lose_screen(GameController *game_controller, int seconds);
void draw_win_final_screen(GameController *game_controller, int seconds);
void draw_win_screen(GameController *game_controller, int seconds);

#endif // CGAME_H
