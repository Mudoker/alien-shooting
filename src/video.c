#include "../header/video.h"
#include "../assets/video/video_resource.h"
#include "../header/framebf.h"
#include "../header/uart.h"
#include "../header/mbox.h"
#include "../header/timer.h"
#include "../header/global.h"

void video_mode()
{
    framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, VIDEO_WIDTH, VIDEO_HEIGHT,0,0);
    display_video(0, 0, VIDEO_WIDTH, VIDEO_HEIGHT, 45, epd_bitmap_allArray_video);
}

void display_video(int x, int y, int w, int h, int num_frames, const unsigned long **video)
{
    for (int i = 0; i < VIDEO_LOOP; i++)
    {
        for (int frame = 0; frame < num_frames; frame++)
        {
            draw_image(x, y, w, h, video[frame]);
            wait_msec(100500);
        }
    }
}
