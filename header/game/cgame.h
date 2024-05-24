#ifndef CGAME_H
#define CGAME_H

#include "../framebf.h"
#include "../utils.h"
#include "./game_struct.h"

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
void gameCli(void);
void init_frame(int offset_x, int offset_y);
void init_spaceship(GameController *game_controller,
                    const unsigned long *sprite, int width, int height, int x,
                    int y);
void draw_spaceship(Spaceship *spaceship);
void draw_background(const unsigned long *sprite);
void init_controller(GameController *game_controller);
void move_spaceship(GameController *game_controller, int key, int step,
                    const unsigned long *epd_bitmap_background);
void render_sprite(int current_x, int current_y, int previous_x, int previous_y,
                   int width, int height, const unsigned long *sprite,
                   const unsigned long *background);
void move_bullet(Bullet *bullet, int step,
                 const unsigned long *epd_bitmap_background);

void add_bullet(GameController *game_controller, int x, int y);

#endif // CGAME_H
