#include "../header/image.h"
#include "../assets/fonts/font.h"
#include "../assets/images/image_resource.h"
#include "../header/uart.h"

void load_image() {
  int offset_x = 0, offset_y = 0;
  const unsigned long *image = epd_bitmap_allArray[0];
  framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT,
               IMAGE_WIDTH * (epd_bitmap_allArray_LEN), IMAGE_HEIGHT, offset_x,
               offset_y);
  draw_image(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, image);

  while (1) {
    char c = uart_getc();
    uart_sendc(c);
    switch (c) {
    case 'w':
      update_position(0, -1, &offset_x, &offset_y);
      break;
    case 's':
      update_position(0, 1, &offset_x, &offset_y);
      break;
    case 'a':
      update_position(-1, 0, &offset_x, &offset_y);
      break;
    case 'd':
      update_position(1, 0, &offset_x, &offset_y);
      break;
    default:
      break;
    }

    framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT,
                 IMAGE_WIDTH * (epd_bitmap_allArray_LEN), IMAGE_HEIGHT,
                 offset_x, offset_y);
  }
}

void update_position(int x_dir, int y_dir, int *offset_x, int *offset_y) {
  // Check if the new offset values are within the image bounds
  if (*offset_x + x_dir * SCROLL_STEP >= 0 &&
      *offset_x + x_dir * SCROLL_STEP <= IMAGE_WIDTH - SCREEN_WIDTH) {
    // Update the offset values
    *offset_x += x_dir * SCROLL_STEP;
  }

  // Check if the new offset values are within the image bounds
  if (*offset_y + y_dir * SCROLL_STEP >= 0 &&
      *offset_y + y_dir * SCROLL_STEP <= IMAGE_HEIGHT - SCREEN_HEIGHT) {
    // Update the offset values
    *offset_y += y_dir * SCROLL_STEP;
  }
}