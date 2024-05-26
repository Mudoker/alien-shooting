// Constants
#define MAX_EQUIPMENTS 10
#define MAX_STR_LENGTH 50

#define GAME_WIDTH 500
#define GAME_HEIGHT 640

typedef enum { False = 0, True = 1 } boolean;

// Forward declaration
struct Position;
struct Size;

// Core structs
typedef struct Position {
  int x; // X coordinate
  int y; // Y coordinate
} Position;

typedef struct Size {
  int width;  // Width
  int height; // Height
} Size;

typedef struct Button {
  int x;      // X coordinate
  int y;      // Y coordinate
  int width;  // Width
  int height; // Height
  char *text; // Text
} Button;
