// --------------------------------------IMAGE_H-------------------------------------

// Header file for the OS command module
#ifndef IMAGE_H
#define IMAGE_H

#include "framebf.h"
#include "utils.h"

void imageCli();
void updatePosition(int x_dir, int y_dir, int *offset_x, int *offset_y);
#endif