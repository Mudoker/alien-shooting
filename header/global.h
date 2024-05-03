// --------------------------------------GLOBAL_H-------------------------------------

// Header file for the global module
#ifndef GLOBAL_H
#define GLOBAL_H

// Terminal Guard
#define MAX_CMD_SIZE 200    // Maximum command size
#define MAX_STR_LEN 1000    // Maximum number of string length
#define MAX_ARG_SIZE 100    // Maximum number of arguments size
#define MAX_CMD_HISTORY 200 // Maximum number of command history

#define IMAGE_WIDTH 544     // Image width
#define IMAGE_HEIGHT 842    // Image height
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

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
typedef enum { False = 0, True = 1 } boolean; // Boolean data type

// OS trademark structure
typedef struct {
  // OS information
  const char *ASCII_ART_LOGO;      // OS logo
  const char *ASCII_ART_LOGO_TEXT; // OS logo small
  const char *OS_NAME;             // OS name
  const char *OS_ID;               // OS id
  const char *OS_VERSION;          // OS version
  const char *CREATED_AT;          // OS created date
  const char *UPDATED_AT;          // OS updated date
  const char *PROMPT;              // Prompt symbol (Default: BrightOS>)

  // Author
  const char *AUTHOR_NAME;       // Author name
  const char *AUTHOR_USERNAME;   // Author username
  const char *AUTHOR_EMAIL;      // Author email
  const char *AUTHOR_SID;        // Author student id
  const char *AUTHOR_GITHUB_URL; // Author github

  // Acknowledgement
  const char *ACK_SCHOOL;       // School name
  const char *ACK_COURSE;       // Course name
  const char *ACK_LECTURER;     // Lecturer name
  const char *ACK_SUBMITTED_BY; // Submitted by
  const char *ACK_DECLARATION;  // Declaration
} Information;

typedef struct {
  char *PRIMARY_COLOR;    // Primary color (Default: Yellow)
  char *SECONDARY_COLOR;  // Secondary color (Default: White)
  char *BACKGROUND_COLOR; // Background color (Default: Black)
  char *SUCCESS_COLOR;    // Success (Default: Green)
  char *ERROR_COLOR;      // Error (Default: Red)
} Theme;

// Global variables and structures
extern Information OS_INFO; // OS trademark information
extern Theme THEME;         // Theme configuration

#endif