#ifndef GAME_STRUCT_H
#define GAME_STRUCT_H

#include "core_struct.h"

// Forward declaration
struct Equipment;
struct Alien;
struct Spaceship;

// Game structs
typedef struct Spaceship {
  char *id;                  // Unique identifier
  char name[MAX_STR_LENGTH]; // Spaceship name
  Position position = {
      GAME_WIDTH / 2,
      GAME_HEIGHT,
  }; // Position
  Size size;                       // Size
  float health = 100;              // Health
  int speed = 10;                  // Speed
  float damage = 10;               // Damage
  float mana = 0;                  // Mana
  unsigned long **sprite;          // Sprite (Image)
  char equipments[MAX_EQUIPMENTS]; // Equipments

  // Methods
  boolean (*draw)();                               // Draw the spaceship
  boolean (*move)(int x, int y);                   // Move the spaceship
  boolean (*shoot)(int x, int y);                  // Shoot
  boolean (*equip)(struct Equipment *equipment);   // Equip an equipment
  boolean (*unequip)(struct Equipment *equipment); // Unequip an equipment
  boolean (*powerup)(int x, int y);                // Powerup (use mana)
} Spaceship;

typedef struct Equipment {
  char *id;                         // Unique identifier
  char name[MAX_STR_LENGTH];        // Equipment name
  char description[MAX_STR_LENGTH]; // Equipment description
  float damage = 0;                 // Damage
  unsigned long **sprite;           // Sprite (Image)
  Position position;                // Position

  // Methods
  boolean (*draw)(int x, int y); // Spawn the equipment
  boolean (*destroy)();          // Destroy the equipment
  boolean (*move)(int x, int y); // Move the equipment
} Equipment;

typedef struct Alien {
  char *id;                  // Unique identifier
  char name[MAX_STR_LENGTH]; // Alien name
  Position position;         // Position
  Size size;                 // Size
  float health = 100;        // Health
  int speed = 10;            // Speed
  float damage = 10;         // Damage
  unsigned long **sprite;    // Sprite (Image)

  // Methods
  boolean (*draw)();              // Draw the alien
  boolean (*move)(int x, int y);  // Move the alien
  boolean (*shoot)(int x, int y); // Shoot
  boolean (*die)();               // Die
} Alien;

#endif
