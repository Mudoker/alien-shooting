#ifndef FRAMEBF_H_
#define FRAMEBF_H_

#include "mbox.h"
#include "uart.h"

void framebf_init(int physicalWidth, int physicalHeight, int virtualWidth, int virtualHeight, int offsetX, int offsetY);
void draw_pixelARGB32(int x, int y, unsigned int attr);
void draw_rectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill);
void draw_image(int x, int y, int w, int h, const unsigned long *image);

#endif