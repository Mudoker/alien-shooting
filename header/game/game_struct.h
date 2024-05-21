#ifndef GAME_STRUCT_H
#define GAME_STRUCT_H

#include "core_struct.h"

// Forward declaration
struct Alien;
struct Bullet;
struct Spaceship;

typedef struct Bullet
{
  char *id;                         // Unique identifier
  char name[MAX_STR_LENGTH];        // Bullet name
  char description[MAX_STR_LENGTH]; // Bullet description
  float damage;                 // Damage
  const unsigned long *sprite;           // Sprite (Image)
  Position position;                // Position

  // Methods
  boolean (*draw)(int x, int y); // Spawn the Bullet
  boolean (*destroy)();          // Destroy the Bullet
  boolean (*move)(int x, int y); // Move the Bullet
} Bullet;

// Game structs
typedef struct Spaceship
{
  char *id;                  // Unique identifier
  char name[MAX_STR_LENGTH]; // Spaceship name
  Position position;                // Position
  Size size;                       // Size
  Bullet bullet;             // Bullet
  float health;              // Health
  int speed;                  // Speed
  float damage;               // Damage
  float mana;                  // Mana
  const unsigned long *sprite;          // Sprite (Image)
  //char Bullets[MAX_BulletS]; // Bullets

  // Methods
  boolean (*draw)();                               // Draw the spaceship
  boolean (*move)(int x, int y);                   // Move the spaceship
  boolean (*shoot)(int x, int y);                  // Shoot
  boolean (*equip)(struct Bullet *Bullet);   // Equip an Bullet
  boolean (*unequip)(struct Bullet *Bullet); // Unequip an Bullet
  boolean (*powerup)(int x, int y);                // Powerup (use mana)
} Spaceship;

typedef struct Alien
{
  char *id;                  // Unique identifier
  char name[MAX_STR_LENGTH]; // Alien name
  Position position;         // Position
  Position target;
  int reached_target; 
  Size size;                 // Size
  float health;        // Health
  int speed;            // Speed
  float damage;         // Damage
  unsigned long **sprite;    // Sprite (Image)

  // Methods
  boolean (*draw)();              // Draw the alien
  boolean (*move)(int x, int y);  // Move the alien
  boolean (*shoot)(int x, int y); // Shoot
  boolean (*die)();               // Die
} Alien;

#endif
