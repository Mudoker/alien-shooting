#ifndef CGAME_H
#define CGAME_H

#include "game_struct.h"
#include "../global.h"
#include "../framebf.h"
#include "../timer.h"
#include "ui.h"

#define MAX_ALIENS 20
#define MAX_STAGES 9

typedef enum {
  KEY_UP = 0,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT,
} Key;

typedef enum {
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
typedef enum {
  WELCOME = 0,
  STAGE,
  IN_GAME,
} Page;

typedef struct Display Display;

typedef struct GameController {
  // Attributes
  Stage stages[MAX_STAGES];
  Spaceship spaceship;
  Alien alien;
  Alien aliens[MAX_ALIENS];
  int alien_count;
  int stage_level;
  Display *screen;
  int bullet_on_screen_count;
  Page page;

  // Methods
  void (*init)(void);
  void (*destroy)(void);
  int (*getInput)(void);
  void (*update)(void);
  void (*render)(void);
} GameController;

struct Display {
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
void init_bullet(GameController *game_controller, const unsigned long *sprite,
                 int width, int height, int x, int y);
void init_stages(GameController *game_controller);
void init_controller(GameController *game_controller);
void init_alien(GameController *game_controller, const unsigned long *sprite,
                int width, int height, int x, int y);

void draw_spaceship(GameController *game_controller);
void draw_background();
void draw_health_bar(GameController *game_controller);
void draw_welcome_screen();
void draw_alien(GameController *game_controller);

void collision_detection(GameController *game_controller);


void move_spaceship(GameController *game_controller, int key, int step);
void move_bullet(GameController *game_controller, int index, int step);

void add_bullet(GameController *game_controller, int x, int y);

void deal_damage(GameController *game_controller);

#endif // CGAME_H
