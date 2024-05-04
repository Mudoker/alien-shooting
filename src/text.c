#include "../header/text.h"

void load_inf() {
  int offset_x = 0, offset_y = 0;

  framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, TEXT_AREA_HEIGHT, TEXT_AREA_HEIGHT,
               offset_x, offset_y);

  draw_boxed_stringARGB32(0, 12, "OS Information", 0xFFFF00);

  int offset = 1.5 * FONT_HEIGHT + 24;

  drawt_stringARGB32(8, offset, "OS Name: ", OS_INFO.OS_NAME, 0xFFFF00,
                     0xFFFFFF);

  drawt_stringARGB32(8, offset + FONT_HEIGHT,
                     "OS Version: ", OS_INFO.OS_VERSION, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 2 * FONT_HEIGHT,
                     "OS Created At: ", OS_INFO.CREATED_AT, 0xFFFF00, 0xFFFFFF);

  draw_boxed_stringARGB32(0, offset + 4 * FONT_HEIGHT, "Team Member", 0xFFFF00);

  offset += 5 * FONT_HEIGHT + 24;

  drawt_stringARGB32(8, offset, "Development Team: ", TEAM_X.TEAM_NAME, 0xFFFF00,
                     0xFFFFFF);

  drawt_stringARGB32(8, offset + FONT_HEIGHT, "Team ID: ", TEAM_X.TEAM_ID,
                     0xFFFF00, 0xFFFFFF);

  draw_boxed_stringARGB32(0, offset + 3 * FONT_HEIGHT, "Team Members", 0xFFFF00);

  offset += 4 * FONT_HEIGHT + 24;

  drawt_stringARGB32(8, offset, "Name: ", TEAM_X.MEMBERS[0].NAME, 0xFFFF00,
                     0xFF0000);

  drawt_stringARGB32(8, offset + FONT_HEIGHT, "SID: ", TEAM_X.MEMBERS[0].SID, 0xFFFF00,
                     0xFFFFFF);

  drawt_stringARGB32(8, offset + 2 * FONT_HEIGHT, "Github: ", TEAM_X.MEMBERS[0].GITHUB, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 3 * FONT_HEIGHT, "Contribution: ", TEAM_X.MEMBERS[0].CONTRIBUTION, 0xFFFF00, 0xFFFFFF);

  offset += 4 * FONT_HEIGHT + 24;

  drawt_stringARGB32(8, offset, "Name: ", TEAM_X.MEMBERS[1].NAME, 0xFFFF00,
                     0x0000FF);

  drawt_stringARGB32(8, offset + FONT_HEIGHT, "SID: ", TEAM_X.MEMBERS[1].SID, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 2 * FONT_HEIGHT, "Github: ", TEAM_X.MEMBERS[1].GITHUB, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 3 * FONT_HEIGHT, "Contribution: ", TEAM_X.MEMBERS[1].CONTRIBUTION, 0xFFFF00, 0xFFFFFF);

  offset += 4 * FONT_HEIGHT + 24;

  drawt_stringARGB32(8, offset, "Name: ", TEAM_X.MEMBERS[2].NAME, 0xFFFF00,
                     0x00FF00);

  drawt_stringARGB32(8, offset + FONT_HEIGHT, "SID: ", TEAM_X.MEMBERS[2].SID, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 2 * FONT_HEIGHT, "Github: ", TEAM_X.MEMBERS[2].GITHUB, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 3 * FONT_HEIGHT, "Contribution: ", TEAM_X.MEMBERS[2].CONTRIBUTION, 0xFFFF00, 0xFFFFFF);

  offset += 4 * FONT_HEIGHT + 24;

  drawt_stringARGB32(8, offset, "Name: ", TEAM_X.MEMBERS[3].NAME, 0xFFFF00,
                     0xFFFFFF);

  drawt_stringARGB32(8, offset + FONT_HEIGHT, "SID: ", TEAM_X.MEMBERS[3].SID, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 2 * FONT_HEIGHT, "Github: ", TEAM_X.MEMBERS[3].GITHUB, 0xFFFF00, 0xFFFFFF);

  drawt_stringARGB32(8, offset + 3 * FONT_HEIGHT, "Contribution: ", TEAM_X.MEMBERS[3].CONTRIBUTION, 0xFFFF00, 0xFFFFFF);
}