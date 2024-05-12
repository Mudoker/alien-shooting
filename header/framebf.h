#ifndef FRAMEBF_H_
#define FRAMEBF_H_

#include "mbox.h"
#include "uart.h"
#include "utils.h"


void framebf_init(int pw, int ph, int vw, int vh, int offsetX, int offsetY);
void draw_pixelARGB32(int x, int y, unsigned int attr);
void draw_pixelARGB32_image(int x, int y, unsigned int attr, const unsigned long *background);
void draw_rectARGB32(int x1, int y1, int x2, int y2, unsigned int attr,
                     int fill);
void draw_image_rect(int x, int y, int w, int h, const unsigned long *image);
void draw_image_object(int x, int y, int w, int h, const unsigned long *image, const unsigned long *background);

void draw_charARGB32(int x, int y, unsigned char ch, unsigned int attr);
void draw_stringARGB32(int x, int y, const char *str, unsigned int attr);
void draw_boxed_stringARGB32(int x, int y, const char *str, unsigned int attr);
void drawt_stringARGB32(int x, int y, const char *title, const char *str,
                        unsigned int title_attr, unsigned int str_attr);;
void update_position(int dx, int dy, int *offsetX, int *offsetY);
void clear_image(int x, int y, int w, int h, const unsigned long *background);

#endif
