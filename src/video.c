#include "../header/video.h"
#include "../assets/video/video_resource.h"
#include "../header/framebf.h"
#include "../header/global.h"
#include "../header/mbox.h"
#include "../header/timer.h"
#include "../header/global.h"
#include "../assets/images/video_image_resource.h"

void video_mode()
{
  framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, 640, 640, 0, 0);
  draw_image_rect(0, 0, 640, 640, epd_bitmap_allArray_bg[0]);
  display_video(110, 250, VIDEO_WIDTH, VIDEO_HEIGHT, 30, epd_bitmap_allArray_video);
  // draw_image(110,250,420, 295, epd_bitmap_allArray_bg[0]);
}

void display_video(int x, int y, int w, int h, int num_frames, const unsigned long **video)
{
  for (int i = 0; i < VIDEO_LOOP; i++)
  {
    for (int frame = 0; frame < num_frames; frame++)
    {
      draw_image_rect(x, y, w, h, video[frame]);
      wait_msec(100500);
      // wait_msec(1000);
    }
  }
}
