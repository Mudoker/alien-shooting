// --------------------------------------GLOBAL_H-------------------------------------

// Header file for the global module
#ifndef GLOBAL_H
#define GLOBAL_H

// Terminal Guard
#define MAX_CMD_SIZE 200    // Maximum command size
#define MAX_STR_LEN 1000    // Maximum number of string length
#define MAX_ARG_SIZE 100    // Maximum number of arguments size
#define MAX_CMD_HISTORY 200 // Maximum number of command history

#define IMAGE_WIDTH 816  // Image width
#define IMAGE_HEIGHT 1263 // Image height

#define SCREEN_WIDTH 780 // Screen width
#define SCREEN_HEIGHT 900 // Screen height

#define VIDEO_HEIGHT 240 // Video height
#define VIDEO_WIDTH 320 // Video width

#define NUM_FRAMES 45 // Number of frames
#define VIDEO_LOOP 10 // Video loop

#define NULL ((void *)0)
#define SCROLL_STEP 4

// Text color codes
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BLACK "\033[0;30m"
#define RED_BG "\033[41m"

// Background color codes
#define GREEN_BG "\033[42m"
#define YELLOW_BG "\033[43m"
#define BLUE_BG "\033[44m"
#define PURPLE_BG "\033[45m"
#define CYAN_BG "\033[46m"
#define WHITE_BG "\033[47m"
#define BLACK_BG "\033[40m"
#define CLEAR "\x1b[49m"

// User-defined data types
// typedef enum { False = 0, True = 1 } boolean; // Boolean data type

// OS trademark structure
typedef struct {
  // OS information
  const char *OS_NAME;    // OS name
  const char *OS_ID;      // OS id
  const char *OS_VERSION; // OS version
  const char *CREATED_AT; // OS created date
  const char *UPDATED_AT; // OS updated date
  const char *PROMPT;     // Prompt symbol (Default: BrightOS>)
} Information;

// Member information structure
typedef struct {
  const char *NAME;         // Member name
  const char *SID;          // Member ID
  const char *GITHUB;       // Member GitHub
  const char *CONTRIBUTION; // Member contribution
} Member;

// Team information structure
typedef struct {
  const char *TEAM_NAME;        // Team name
  const char *TEAM_ID;          // Team ID
  const char *TEAM_DESCRIPTION; // Team description
  const Member MEMBERS[4];      // Team members
} Team;

// Global variables and structures
extern Information OS_INFO; // OS trademark information
extern Team TEAM_X;         // Team X information

#endif
