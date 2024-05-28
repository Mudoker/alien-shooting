// #include "explosion.h"
// #include "../../assets/games/explosion/explosion.h"
// #include "../../header/framebf.h"
// #include "../../header/global.h"
// #include "../../header/mbox.h"
// #include "../../header/timer.h"
// #include "../../header/global.h"
// #include "../../assets/games/background.h"

// void explosion()
// {
//   framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, cinema_bg_width, cinema_bg_height, 0, 0);
//   display_explosion(paddingLeft, paddingTop, 90, 90, 30, epd_bitmap_explosion_allArray);
// }

// void display_explosion(int x, int y, int w, int h, int num_frames, const unsigned long **video)
// {
//   for (int i = 0; i < VIDEO_LOOP; i++)
//   {
//     for (int frame = 0; frame < num_frames; frame++)
//     {
//       draw_image(x, y, w, h, video[frame]);
//       wait_msec(100500);
//     }
//   }
//   clear_image(x, y, w, h, epd_bitmap_background);
// }