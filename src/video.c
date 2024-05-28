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
  framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, cinema_bg_width, cinema_bg_height, 0, 0);
  draw_image_rect(0, 0, cinema_bg_width, cinema_bg_height, cinemaallArray[0]);
  display_video(paddingLeft, paddingTop, VIDEO_WIDTH, VIDEO_HEIGHT, 30, epd_bitmap_allArray_video);
}

void display_video(int x, int y, int w, int h, int num_frames, const unsigned long **video)
{
  for (int i = 0; i < VIDEO_LOOP; i++)
  {
    for (int frame = 0; frame < 30; frame++)
    {
        draw_image_rect(x, y, w, h, video[frame]);
        wait_msec(100);
    }
  }
}