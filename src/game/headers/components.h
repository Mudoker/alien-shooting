#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "./core_struct.h"

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
} Button;

#endif
