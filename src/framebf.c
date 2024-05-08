#include "../header/framebf.h"
#include "../assets/fonts/normal_font.h"
#include "../header/uart.h"

// Use RGBA32 (32 bits for each pixel)
#define COLOR_DEPTH 32
// Pixel Order: BGR in memory order (little endian --> RGB in byte order)
#define PIXEL_ORDER 0
// Screen info
unsigned int width, height, pitch;
/* Frame buffer address
 * (declare as pointer of unsigned char to access each byte) */
unsigned char *fb;

void framebf_init(int pw, int ph, int vw, int vh, int offsetX, int offsetY) {
  mBuf[0] = 35 * 4; // Length of message in bytes
  mBuf[1] = MBOX_REQUEST;

  mBuf[2] = MBOX_TAG_SETPHYWH; // Set physical width-height
  mBuf[3] = 8;                 // Value size in bytes
  mBuf[4] = 0;                 // REQUEST CODE = 0
  mBuf[5] = pw;                // Value(width)
  mBuf[6] = ph;                // Value(height)

  mBuf[7] = MBOX_TAG_SETVIRTWH; // Set virtual width-height
  mBuf[8] = 8;
  mBuf[9] = 0;
  mBuf[10] = vw;
  mBuf[11] = vh;

  mBuf[12] = MBOX_TAG_SETVIRTOFF; // Set virtual offset
  mBuf[13] = 8;
  mBuf[14] = 0;
  mBuf[15] = offsetX; // x offset
  mBuf[16] = offsetY; // y offset

  mBuf[17] = MBOX_TAG_SETDEPTH; // Set color depth
  mBuf[18] = 4;
  mBuf[19] = 0;
  mBuf[20] = COLOR_DEPTH; // Bits per pixel

  mBuf[21] = MBOX_TAG_SETPXLORDR; // Set pixel order
  mBuf[22] = 4;
  mBuf[23] = 0;
  mBuf[24] = PIXEL_ORDER;

  mBuf[25] = MBOX_TAG_GETFB; // Get frame buffer
  mBuf[26] = 8;
  mBuf[27] = 0;
  mBuf[28] = 16; // alignment in 16 bytes
  mBuf[29] = 0;  // will return Frame Buffer size in bytes

  mBuf[30] = MBOX_TAG_GETPITCH; // Get pitch
  mBuf[31] = 4;
  mBuf[32] = 0;
  mBuf[33] = 0; // Will get pitch value here
  mBuf[34] = MBOX_TAG_LAST;
  // Call Mailbox
  if (mbox_call(ADDR(mBuf), MBOX_CH_PROP) // mailbox call is successful ?
      && mBuf[20] == COLOR_DEPTH          // got correct color depth ?
      && mBuf[24] == PIXEL_ORDER          // got correct pixel order ?
      && mBuf[28] != 0 // got a valid address for frame buffer ?
  ) {
    /* Convert GPU address to ARM address (clear higher address bits)
     * Frame Buffer is located in RAM memory, which VideoCore MMU
     * maps it to bus address space starting at 0xC0000000.
     * Software accessing RAM directly use physical addresses
     * (based at 0x00000000)
     */
    mBuf[28] &= 0x3FFFFFFF;
    // Access frame buffer as 1 byte per each address
    fb = (unsigned char *)((unsigned long)mBuf[28]);
    // uart_puts("Got allocated Frame Buffer at RAM physical address: ");
    // uart_hex(mBuf[28]);
    // uart_puts("\n");
    // uart_puts("Frame Buffer Size (bytes): ");
    // uart_dec(mBuf[29]);
    // uart_puts("\n");
    width = mBuf[5];  // Actual physical width
    height = mBuf[6]; // Actual physical height
    pitch = mBuf[33]; // Number of bytes per line
  } else {
    uart_puts("Unable to get a frame buffer with provided setting\n");
  }
}
void draw_pixelARGB32(int x, int y, unsigned int attr) {
  int offs = (y * pitch) + ((COLOR_DEPTH / 8) * x);
  /* //Access and assign each byte
   *(fb + offs ) = (attr >> 0 ) & 0xFF; //BLUE
   *(fb + offs + 1) = (attr >> 8 ) & 0xFF; //GREEN
   *(fb + offs + 2) = (attr >> 16) & 0xFF; //RED
   *(fb + offs + 3) = (attr >> 24) & 0xFF; //ALPHA
   */
  // Access 32-bit together
  *((unsigned int *)(fb + offs)) = attr;
}
void draw_rectARGB32(int x1, int y1, int x2, int y2, unsigned int attr,
                     int fill) {
  for (int y = y1; y <= y2; y++)
    for (int x = x1; x <= x2; x++) {
      if ((x == x1 || x == x2) || (y == y1 || y == y2))
        draw_pixelARGB32(x, y, attr);
      else if (fill)
        draw_pixelARGB32(x, y, attr);
    }
}

void draw_image(int x, int y, int w, int h, const unsigned long *image) {
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      draw_pixelARGB32(x + i, y + j, image[(x + i) + (y + j) * w]);
    }
  }
}

void draw_charARGB32(int x, int y, unsigned char ch, unsigned int attr) {
  for (int j = 0; j < FONT_HEIGHT; j++) {
    for (int i = 0; i < FONT_WIDTH; i++) {
      if ((font[ch][j] >> i) & 1) {
        draw_pixelARGB32(x + i, y + j, attr);
      }
    }
  }
}

void draw_stringARGB32(int x, int y, const char *str, unsigned int attr) {
  int i = 0;
  while (str[i] != '\0') {
    draw_charARGB32(x + i * FONT_WIDTH, y, str[i], attr);
    i++;
  }
}

void drawt_stringARGB32(int x, int y, const char *title, const char *str,
                        unsigned int title_attr, unsigned int str_attr) {
  draw_stringARGB32(x, y, title, title_attr);
  draw_stringARGB32(x + len(title) * FONT_WIDTH, y, str, str_attr);
}

void draw_boxed_stringARGB32(int x, int y, const char *str, unsigned int attr) {
  // Calculate the width and height of the box
  int str_length = len(str);
  int box_width = (str_length * FONT_WIDTH) + 16; // Add 16 for padding
  int box_height = FONT_HEIGHT + 24;              // Add 24 for padding

  // Draw top and bottom horizontal lines of the box
  for (int i = 0; i < box_width; i++) {
    draw_pixelARGB32(x + i, y, attr);                  // Top line
    draw_pixelARGB32(x + i, y + box_height - 1, attr); // Bottom line
  }

  // Draw left and right vertical lines of the box
  for (int j = 0; j < box_height; j++) {
    draw_pixelARGB32(x, y + j, attr);                 // Left line
    draw_pixelARGB32(x + box_width - 1, y + j, attr); // Right line
  }

  // Draw the string inside the box
  draw_stringARGB32(x + 8, y + 12, str, attr);
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
