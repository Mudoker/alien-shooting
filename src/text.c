#include "../header/text.h"
#include "../assets/images/app_logo.h"

void load_inf() {
  int offset_x = 0, offset_y = 0;

  framebf_clear(0x00000000);
  framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT,
               offset_x, offset_y);

  draw_image_rect(0, 0, 136, 103, epd_bitmap_logoallArray[0]);

  draw_boxed_stringARGB32(0, 12 + 120, "OS Information", 0xFFFF00);

  int offset = 1.5 * FONT_HEIGHT + 24 + 120;

  drawt_stringARGB32(8, offset, "OS Name: ", OS_INFO.OS_NAME, 0xFFFF00,
                     0xFFFFFF);

  drawt_stringARGB32(8, offset + FONT_HEIGHT,
                     "OS Version: ", OS_INFO.OS_VERSION, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 2 * FONT_HEIGHT,
                     "OS Created At: ", OS_INFO.CREATED_AT, 0xFFFF00, 0xFFFFFF);

  draw_boxed_stringARGB32(0, offset + 4 * FONT_HEIGHT, "Team Member", 0xFFFF00);

  offset += 5 * FONT_HEIGHT + 24;

  drawt_stringARGB32(8, offset, "Development Team: ", TEAM_X.TEAM_NAME,
                     0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + FONT_HEIGHT, "Team ID: ", TEAM_X.TEAM_ID,
                     0xFFFF00, 0xFFFFFF);

  draw_boxed_stringARGB32(0, offset + 3 * FONT_HEIGHT, "Team Members",
                          0xFFFF00);

  offset += 4 * FONT_HEIGHT + 24;

  drawt_stringARGB32(8, offset, "Name: ", TEAM_X.MEMBERS[0].NAME, 0xFFFF00,
                     0xFF0000);

  drawt_stringARGB32(8, offset + FONT_HEIGHT, "SID: ", TEAM_X.MEMBERS[0].SID,
                     0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 2 * FONT_HEIGHT,
                     "Github: ", TEAM_X.MEMBERS[0].GITHUB, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 3 * FONT_HEIGHT,
                     "Contribution: ", TEAM_X.MEMBERS[0].CONTRIBUTION, 0xFFFF00,
                     0xFFFFFF);

  offset += 4 * FONT_HEIGHT + 24;

  drawt_stringARGB32(8, offset, "Name: ", TEAM_X.MEMBERS[1].NAME, 0xFFFF00,
                     0x87CEEB);

  drawt_stringARGB32(8, offset + FONT_HEIGHT, "SID: ", TEAM_X.MEMBERS[1].SID,
                     0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 2 * FONT_HEIGHT,
                     "Github: ", TEAM_X.MEMBERS[1].GITHUB, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 3 * FONT_HEIGHT,
                     "Contribution: ", TEAM_X.MEMBERS[1].CONTRIBUTION, 0xFFFF00,
                     0xFFFFFF);

  offset += 4 * FONT_HEIGHT + 24;

  drawt_stringARGB32(8, offset, "Name: ", TEAM_X.MEMBERS[2].NAME, 0xFFFF00,
                     0x00FF00);

  drawt_stringARGB32(8, offset + FONT_HEIGHT, "SID: ", TEAM_X.MEMBERS[2].SID,
                     0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 2 * FONT_HEIGHT,
                     "Github: ", TEAM_X.MEMBERS[2].GITHUB, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 3 * FONT_HEIGHT,
                     "Contribution: ", TEAM_X.MEMBERS[2].CONTRIBUTION, 0xFFFF00,
                     0xFFFFFF);

  offset += 4 * FONT_HEIGHT + 24;

  drawt_stringARGB32(8, offset, "Name: ", TEAM_X.MEMBERS[3].NAME, 0xFFFF00,
                     0xFFC0CB);

  drawt_stringARGB32(8, offset + FONT_HEIGHT, "SID: ", TEAM_X.MEMBERS[3].SID,
                     0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 2 * FONT_HEIGHT,
                     "Github: ", TEAM_X.MEMBERS[3].GITHUB, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 3 * FONT_HEIGHT,
                     "Contribution: ", TEAM_X.MEMBERS[3].CONTRIBUTION, 0xFFFF00,
                     0xFFFFFF);

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
      uart_puts("\n\nExiting text mode\n\n");
      return;
    default:
      break;
    }

    framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT,
                 offset_x, offset_y);
  }
}
