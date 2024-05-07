// Constants
#define MAX_EQUIPMENTS 10
#define MAX_STR_LENGTH 50

#define GAME_WIDTH 800
#define GAME_HEIGHT 600

typedef enum { False = 0, True = 1 } boolean;

typedef struct Position {
  int x; // X coordinate
  int y; // Y coordinate
} Position;

typedef struct Size {
  int width;  // Width
  int height; // Height
} Size;
