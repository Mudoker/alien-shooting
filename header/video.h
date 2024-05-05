
// #define VID_HEIGHT 720
// #define VID_WIDTH 1280
// #define VID_SCREEN_WIDTH 1280
// #define VID_SCREEN_HEIGHT 720
// #define NUM_FRAMES 120
// #define VIDEO_LOOP 10

#define VID_HEIGHT 240
#define VID_WIDTH 320
#define VID_SCREEN_WIDTH 320
#define VID_SCREEN_HEIGHT 240
#define NUM_FRAMES 45
#define VIDEO_LOOP 10

void video_mode();
void display_video(int x, int y, int w, int h, int num_frames, const unsigned long **video);