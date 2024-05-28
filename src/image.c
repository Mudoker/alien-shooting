#include "../header/image.h"
#include "../assets/images/image_resource.h"
#include "../header/uart.h"

void load_image() {
  int offset_x = 0, offset_y = 0;
  const unsigned long *image = epd_bitmap_Linh_Tran[0];
  framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT, offset_x,
               offset_y);
  draw_image_rect(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, image);

  while (1) {
    char c = uart_getc();
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
    case 'x':
      uart_puts("\n\nExiting image mode\n\n");
      return;
    default:
      break;
    }

    framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT,
                 offset_x, offset_y);
  }
}
