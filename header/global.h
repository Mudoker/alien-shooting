// --------------------------------------GLOBAL_H-------------------------------------

// Header file for the global module
#ifndef GLOBAL_H
#define GLOBAL_H

// Terminal Guard
#define MAX_CMD_SIZE 200    // Maximum command size
#define MAX_STR_LEN 1000    // Maximum number of string length
#define MAX_ARG_SIZE 100    // Maximum number of arguments size
#define MAX_CMD_HISTORY 200 // Maximum number of command history

#define IMAGE_WIDTH 544  // Image width
#define IMAGE_HEIGHT 842 // Image height
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define SCROLL_STEP 4 // Scroll step

// User-defined data types
typedef enum { False = 0, True = 1 } boolean; // Boolean data type

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
