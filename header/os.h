// --------------------------------------OS_COMMAND-------------------------------------

// Header file for the OS command module
#ifndef OS_COMMAND
#define OS_COMMAND

#include "./global.h"
#include "./mbox.h"
#include "./uart.h"
#include "./utils.h"

// Struct to store command stack
typedef struct CommandStack {
  char command[MAX_CMD_HISTORY][MAX_CMD_SIZE];
  int top_index;
} CommandStack;

// Function prototypes
void os_greet();                   // Welcome message
void show_help(char *command);     // Show help menu
void parse_command(char *command); // Parse the command

// Command stack methods
void push_command(struct CommandStack *stack, char *command); // Push command
void pop_command(struct CommandStack *stack);                 // Pop command
void get_command(struct CommandStack *stack);                 // Get command
void get_all_commands(struct CommandStack *stack); // Get all commands

// Command methods
char *autocomplete_command(char *buffer); // Autocomplete command

// Command stack
extern CommandStack command_stack;

#endif
