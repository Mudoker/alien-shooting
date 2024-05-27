#ifndef GAME_STRUCT_H
#define GAME_STRUCT_H

#include "core_struct.h"

// Forward declaration
struct Alien;
struct Bullet;
struct Spaceship;
struct Stage;
struct Wave;

#define MAX_BULLETS 1000

typedef struct Bullet
{
  char *id;                    // Unique identifier
  char *name;                  // Bullet name
  float damage;                // Damage
  Size size;                   // Size
  const unsigned long *sprite; // Sprite (Image)
  Position position;           // Position

  // Methods
  boolean (*draw)(int x, int y); // Spawn the Bullet
  boolean (*destroy)();          // Destroy the Bullet
  boolean (*move)(int x, int y); // Move the Bullet
} Bullet;

// Game structs
typedef struct Spaceship
{
  char *id;                      // Unique identifier
  char *name;                    // Spaceship name
  Position position;             // Position
  Size size;                     // Size
  Bullet bullet[MAX_BULLETS][5]; // Bullet
  float health;                  // Health
  int speed;                     // Speed
  float damage;                  // Damage
  float mana;                    // Mana
  int bullet_bonus;              // Bullet bonus
  const unsigned long *sprite;   // Sprite (Image)

  // Methods
  boolean (*show)();                         // Draw the spaceship
  boolean (*move)(int x, int y);             // Move the spaceship
  boolean (*shoot)(int x, int y);            // Shoot
  boolean (*equip)(struct Bullet *Bullet);   // Equip an Bullet
  boolean (*unequip)(struct Bullet *Bullet); // Unequip an Bullet
  boolean (*powerup)(int x, int y);          // Powerup (use mana)
} Spaceship;

typedef struct Alien
{
  char *id;          // Unique identifier
  char *name;        // Alien name
  Position position; // Position
  Position target;
  int reached_target;
  Size size;                   // Size
  float health;                // Health
  int speed;                   // Speed
  float damage;                // Damage
  const unsigned long *sprite; // Sprite (Image)
  int direction;               // Direction

  // Methods
  boolean (*draw)();              // Draw the alien
  boolean (*move)(int x, int y);  // Move the alien
  boolean (*shoot)(int x, int y); // Shoot
  boolean (*die)();               // Die
} Alien;

typedef struct Wave
{
  int level;       // Wave level
  int alien_count; // Alien count
  Alien aliens[5]; // Aliens
} Wave;

typedef struct Stage
{
  char name[MAX_STR_LENGTH]; // Stage name
  int level;                 // Stage level
  Wave waves[3];             // Waves
} Stage;

typedef struct PowerUp
{
  char *id;   // Unique identifier
  char *name; // PowerUp name
  int type;
  Position position;
  Position target;
  int reach_target;            // Position
  Size size;                   // Size
  const unsigned long *sprite; // Sprite (Image)

  // Methods
  boolean (*draw)(); // Draw the PowerUp
  boolean (*use)();  // Use the PowerUp
} PowerUp;
#endif
