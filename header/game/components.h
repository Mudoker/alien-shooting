#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "./core_struct.h"

// Forward declaration
struct Button;

// Component structs
typedef struct Button {
  // Attributes
  char *id;               // Unique identifier
  Position position;      // Position
  Size size;              // Size
  unsigned long **sprite; // Sprite (Image)
  boolean visible = True; // Visibility

  // Methods
  boolean (*on_select)();    // Click the button
  boolean (*on_animation)(); // Pulse animation
  boolean (*draw)();         // Draw the button
  boolean (*destroy)();      // Destroy the button
} Button;

#endif
