#include "../header/os.h"

// Initialize the command stack
CommandStack command_stack = {.top_index = -1};

// List of available commands
char *commands[] = {
    "os",       "help",  "clear", "history", "setcolor", "ref",
    "showinfo", "image", "video", "game",    (char *)0,
};

char *extended_commands[] = {
    "help setcolor",    "help ref",
    "help showinfo",    "help clear",
    "help history",     "help os",
    "help help",        "ref -uart",
    "showinfo -v",      "ref -uart -baud",
    "ref -uart -dbits", "ref -uart -sbits",
    "ref -uart -par",   "ref -uart -handshake",
    (char *)0,
};

// Print the OS information (welcome message)
void os_greet() {
  uart_puts("\n");

  // OS logo
  str_format(OS_INFO.ASCII_ART_LOGO, THEME.PRIMARY_COLOR);
  uart_puts("\n");

  // OS Information box
  print_in_box("OS Information");
  uart_puts("\n");

  // Format and print "ID" title
  str_format("ID           : ", THEME.PRIMARY_COLOR);
  str_format(OS_INFO.OS_ID, THEME.SECONDARY_COLOR);
  uart_puts("\n");

  // Format and print "OS Name" title
  str_format("OS Name      : ", THEME.PRIMARY_COLOR);
  str_format(OS_INFO.OS_NAME, THEME.SECONDARY_COLOR);
  uart_puts("\n");

  // Format and print "Version" title
  str_format("Version      : ", THEME.PRIMARY_COLOR);
  str_format(OS_INFO.OS_VERSION, THEME.SECONDARY_COLOR);
  uart_puts("\n");

  // Copyright
  print_in_box("Acknowledgement");
  uart_puts("\n");

  // Print school name (RMIT SSET)
  str_format("School       : ", THEME.PRIMARY_COLOR);
  str_format(OS_INFO.ACK_SCHOOL, THEME.SECONDARY_COLOR);
  uart_puts("\n");

  // Print course name (Embedded Systems 3)
  str_format("Course       : ", THEME.PRIMARY_COLOR);
  str_format(OS_INFO.ACK_COURSE, THEME.SECONDARY_COLOR);
  uart_puts("\n");

  // Print lecturer name (Mr. Linh T.D.)
  str_format("Lecturer     : ", THEME.PRIMARY_COLOR);
  str_format(OS_INFO.ACK_LECTURER, THEME.SECONDARY_COLOR);
  uart_puts("\n");

  // Print submitted by
  str_format("Submitted by : ", THEME.PRIMARY_COLOR);
  str_format(OS_INFO.ACK_SUBMITTED_BY, THEME.SECONDARY_COLOR);
  uart_puts("\n\n");

  // Print declaration
  str_format(OS_INFO.ACK_DECLARATION, THEME.SECONDARY_COLOR);
  uart_puts("\n");

  // Print OS logo
  str_format(OS_INFO.ASCII_ART_LOGO_TEXT, THEME.PRIMARY_COLOR);
  uart_puts("\n");

  // Print OS establishment year
  str_format("@2024. All rights reserved.", THEME.SECONDARY_COLOR);
  uart_puts("\n\n");
}

// As per limitations of bare-metal programming, the stack is implemented as an
// array of strings Add a command to the stack
void push_command(struct CommandStack *stack, char *command) {
  // Check if the stack is full
  if (stack->top_index == MAX_CMD_HISTORY - 1) {
    // Shift the stack to the left
    for (int i = 0; i < MAX_CMD_HISTORY - 1; i++) {
      strcpy(stack->command[i], stack->command[i + 1]);
    }
  } else {
    // Increment the top index
    stack->top_index++;
  }

  // Copy the command to the top of the stack
  strcpy(stack->command[stack->top_index], command);
}

// Remove the top command from the stack
void pop_command(struct CommandStack *self) {
  // Check if the stack is empty
  if (self->top_index == -1) {
    return;
  }

  // Decrement the top index
  self->top_index--;
}

// Get the command at the top of the stack
void get_command(struct CommandStack *self) {
  // Check if the stack is empty
  if (self->top_index == -1) {
    return;
  }

  // Get the command at the top of the stack
  uart_puts(self->command[self->top_index]);
}

// Get all commands in the stack
void get_all_commands(struct CommandStack *stack) {
  // Check if the stack is empty
  if (stack->top_index == -1) {
    return;
  }

  // Print all commands in the stack
  for (int i = 0; i <= stack->top_index; i++) {
    uart_puts(stack->command[i]);
    uart_puts("\n");
  }
}

// Take a list of keys and values and initialize the values array with null
void initialize_values(char *values[MAX_ROWS][MAX_ROWS], int rows) {
  // Loop through the values array and initialize it with null
  for (int i = 0; i < MAX_ROWS; i++) {
    for (int j = 0; j < rows; j++) {
      values[i][j] = (char *)0;
    }
  }
}

// Show command execution status
void show_status(int status, char *msg) {
  // Initialize the color based on the status
  const char *color;

  // Define the color based on the status (0: success, 1: error)
  if (status == 0) {
    color = THEME.SUCCESS_COLOR;
  } else {
    color = THEME.ERROR_COLOR;
  }

  // Print the status message
  str_format("\n\n", THEME.SECONDARY_COLOR);
  str_format(msg, color);
  str_format("\n\n", THEME.SECONDARY_COLOR);
}

// Display help menu
void show_help(char *command) {
  char *keys[] = {"Command", "Description"}; // Table headers
  char *values[MAX_ROWS][MAX_ROWS];          // Table values
  char *commands_desc[MAX_ROWS][MAX_ROWS];   // Command descriptions

  // Ref: Help command on Linuxcommand
  str_format("\n\nBrightOS, Version 1.0\n", THEME.SECONDARY_COLOR);
  str_format("These shell commands are defined internally. Type 'help' to see "
             "this list.\n",
             THEME.SECONDARY_COLOR);
  str_format("Type 'help name' to find out more about the function 'name'.\n",
             THEME.SECONDARY_COLOR);
  str_format("A star (*) next to a name means that the command is disabled.\n",
             THEME.SECONDARY_COLOR);

  initialize_values(values, 9);        // Initialize the values array
  initialize_values(commands_desc, 9); // Initialize the commands_desc array

  // Define the descriptions for each command
  commands_desc[0][0] = "Show OS information";
  commands_desc[1][0] = "Show help for a command";
  commands_desc[1][1] = "<command>: To get help for a specific command";
  commands_desc[1][2] = "\n** '?' can be used as an alias for 'help' command";
  commands_desc[1][3] = "\nE.g.: help setcolor\n";
  commands_desc[2][0] = "Clear the terminal";
  commands_desc[2][1] = "\n-f: Full clear (clear everything)";
  commands_desc[2][2] =
      "\n** 'cls' and 'clr' can be used as aliases for 'clear'";
  commands_desc[2][3] = "\nE.g.: clear -f";
  commands_desc[3][0] = "Show command histor";
  commands_desc[3][1] = "** 'hist' can be used as an alias for 'history'";
  commands_desc[3][1] = "\nE.g.: hist";
  commands_desc[4][0] = "Change color of OS";
  commands_desc[4][1] =
      "-[target]: b: background, t: text, os: os theme, "
      "pri: primary, sec: secondary, err: ERROR_COLOR, suc: SUCCESS_COLOR\n";
  commands_desc[4][2] =
      "-[color]: red, green, yellow, blue, purple, cyan, white, "
      "black, bright (os only), dark (os only), light (os only)";
  commands_desc[4][3] =
      "\nE.g.: setcolor -t red -b yellow -pri green -sec cyan";
  commands_desc[5][0] = "Show reference for a target";
  commands_desc[5][1] = "-[target]: uart";
  commands_desc[5][2] =
      "-baud/bdr [value]: set baud rate (Allowed values: 300,600, 1200, 2400, "
      "4800, 9600,14400, 19200, 38400, 57600, 115200, 230400, 460800, "
      "921600)\n";
  commands_desc[5][3] =
      "-dbits/dbs [value]: set data bits (Allowed values: 5, 6, 7, "
      "8)\n";
  commands_desc[5][4] =
      "-sbits/sbs [value]: set stop bits (Allowed values: 1, 2)\n";
  commands_desc[5][5] =
      "-par [value]: set parity (Allowed values: none, even, odd)\n";
  commands_desc[5][6] =
      "-handshake/hs/flow [value]: set handshake (Allowed values: 0: "
      "none, 1: CTS/RTS)\n";
  commands_desc[5][7] = "\nE.g.: ref -uart -baud 115200 -dbits 8 -sbits 1 -par "
                        "none -handshake 1";
  commands_desc[6][0] = "Show current device informatio";
  commands_desc[6][1] = "-v: show full information";
  commands_desc[6][2] = "\nE.g.: showinfo -v";
  commands_desc[7][0] = "Show image on the screen";
  commands_desc[7][1] = "None";
  commands_desc[7][2] = "\nE.g.: image";
  commands_desc[8][0] = "Show video on the screen";
  commands_desc[8][1] = "None";
  commands_desc[8][2] = "\nE.g.: video";
  commands_desc[9][0] = "Show game on the screen";
  commands_desc[9][1] = "None";
  commands_desc[9][2] = "\nE.g.: game";
  commands_desc[10][0] = (char *)0;

  // Display help menu
  uart_puts("\n");

  // Display commands in tabular format
  int num_rows = 0;

  // Display help for all commands
  if (is_equal(command, "all")) {
    // Loop through the commands and descriptions to extract the values
    for (int i = 0; commands[i] != (char *)0; i++) {
      values[i][0] = commands[i];
      num_rows++;
    }

    for (int i = 0; commands_desc[i][0] != (char *)0; i++) {
      values[i][1] = commands_desc[i][0];
    }
  } else {
    // Display help for a specific command
    int i;

    // Loop through the commands to find the command
    for (i = 0; commands[i] != (char *)0; i++) {
      // Check if the command is found
      if (is_equal(command, commands[i])) {
        // Extract the command and description
        values[0][0] = commands[i];
        values[0][1] = commands_desc[i][0];
        num_rows++;

        /*
        Loop through the descriptions to extract the values. One command can
        have multiple descriptions (flags)
        */
        for (int j = 1; commands_desc[i][j] != (char *)0; j++) {
          values[j][0] = "";
          values[j][1] = commands_desc[i][j];
          num_rows++;
        }
        break;
      }
    }

    // Check if the command is not found
    if (commands[i] == (char *)0) {
      show_status(1,
                  "Command not found. Type 'help' to see available commands.");
      return;
    }
  }

  // Display the table with the commands and descriptions
  tabulate(keys, 2, values, num_rows);

  uart_puts("\n");
}

// Auto-complete command
char *autocomplete_command(char *buffer) {
  // Check if the buffer is empty
  if (len(buffer) == 0) {
    return (char *)0;
  }

  // Check if the buffer starts with '?' and return "help" if true
  if (buffer[0] == '?') {
    buffer[0] = 'h';
    buffer[1] = 'e';
    buffer[2] = 'l';
    buffer[3] = 'p';
  }

  // Loop through the commands to find the matching command
  for (int i = 0; commands[i] != (char *)0; i++) {

    if (starts_with(commands[i], buffer)) {
      return commands[i];
    }
  }

  // Loop through the extended commands to find the matching command
  for (int i = 0; extended_commands[i] != (char *)0; i++) {
    if (starts_with(extended_commands[i], buffer)) {
      return extended_commands[i];
    }
  }

  // Return null if no command matches the buffer
  return (char *)0;
}

// Parse flags from the input, passing by reference the flags array making it
// can be used outside the function without returning it
int parse_flags(char *input, char *flags[], int max_flags, int min_flags) {
  int i = 0;                                    // Index for the input string
  int j = 0;                                    // Index for the flag string
  int k = 0;                                    // Index for the flags array
  int flag_count = 0;                           // Count of flags
  char flag_buffer[MAX_CMD_SIZE][MAX_CMD_SIZE]; // Buffer to store flags

  // Initialize the flag buffer
  for (int i = 0; i < MAX_CMD_SIZE; i++) {
    for (int j = 0; j < MAX_CMD_SIZE; j++) {
      flag_buffer[i][j] = '\0';
    }
  }

  // Extract the flags from the input
  while (input[i] != '\0' && k < MAX_CMD_SIZE) {
    // If a flag is found (starts with '-')
    if (input[i] == '-') {
      i++;          // Skip the '-'
      j = 0;        // Reset j for a new flag
      flag_count++; // Increment the flag count

      // Extract the flag
      while (input[i] != '\0' && input[i + 1] != '-' && j < MAX_CMD_SIZE - 1) {
        flag_buffer[k][j++] = input[i++];
      }

      flag_buffer[k][j] = '\0';  // Null-terminate the flag string
      flags[k] = flag_buffer[k]; // Store the flag in the flags array
      k++;                       // Increment index for the flags array
    }
    i++;
  }

  // Check if the number of flags exceeds the maximum allowed flags
  if (flag_count > max_flags) {
    show_status(
        1, "Too many flags. Type 'help <command>' to see available flags.");
    return 0;
  }

  // Check if the number of flags is less than the minimum required flags
  if (flag_count < min_flags) {
    show_status(1,
                "Too few flags. Type 'help <command>' to see available flags.");
    return 0;
  }

  // Return the number of flags
  return flag_count;
}

// Parse target from the flags (e.g., -t red)
void parse_target(char *flag, char *target, char *option) {
  // Extract the target and option
  int k = 0;

  // Extract the target
  while (flag[k] != '\0' && flag[k] != ' ') {
    target[k] = flag[k];
    k++;
  }
  target[k] = '\0'; // Null-terminate the target

  // Skip spaces after target
  while (flag[k] == ' ') {
    k++;
  }

  // Extract the option
  int l = 0;
  while (flag[k] != '\0') {
    option[l++] = flag[k++];
  }

  option[l] = '\0'; // Null-terminate the option
}

// Parse the color from the flags and return the color code
char *to_color(char *flag, int type) {
  // If the type is 0, it is a text color, if it is 1, it is a background color
  if (type == 0) {
    if (is_equal(flag, "red"))
      return RED;
    else if (is_equal(flag, "green"))
      return GREEN;
    else if (is_equal(flag, "yellow"))
      return YELLOW;
    else if (is_equal(flag, "blue"))
      return BLUE;
    else if (is_equal(flag, "purple"))
      return PURPLE;
    else if (is_equal(flag, "cyan"))
      return CYAN;
    else if (is_equal(flag, "white"))
      return WHITE;
    else if (is_equal(flag, "black"))
      return BLACK;
  } else {
    if (is_equal(flag, "red"))
      return RED_BG;
    else if (is_equal(flag, "green"))
      return GREEN_BG;
    else if (is_equal(flag, "yellow"))
      return YELLOW_BG;
    else if (is_equal(flag, "blue"))
      return BLUE_BG;
    else if (is_equal(flag, "purple"))
      return PURPLE_BG;
    else if (is_equal(flag, "cyan"))
      return CYAN_BG;
    else if (is_equal(flag, "white"))
      return WHITE_BG;
    else if (is_equal(flag, "black"))
      return BLACK_BG;
    else if (is_equal(flag, "clear"))
      return CLEAR;
  }

  // ERROR_COLOR message
  show_status(1, "Invalid  Type 'help setcolor' to see available colors.");

  return (char *)0;
}

// Parse and execute command
void parse_command(char *input) {
  // Initialize variables
  char command[MAX_CMD_SIZE];
  int i, j;

  // Extract command from input
  for (i = 0; input[i] != '\0' && input[i] != ' '; i++) {
    command[i] = input[i];
  }
  command[i] = '\0'; // Null-terminate the command

  // Skip spaces after command
  while (input[i] == ' ') {
    i++;
  }

  // Check for various commands
  if (is_equal(command, "help") || is_equal(command, "?")) {
    // Extract the command to get help for
    char help_command[MAX_CMD_SIZE];
    j = 0;

    // Extract the help command from the input
    while (input[i] != '\0') {
      help_command[j++] = input[i++];
    }

    // Null-terminate the help command
    help_command[j] = '\0';

    // If help command is empty, treat as "all"
    if (len(help_command) == 0) {
      show_help("all");
    } else {
      show_help(help_command);
    }
  } else if (is_equal(command, "os")) {
    // Show OS information
    os_greet();
  } else if (is_equal(command, "clr") || is_equal(command, "cls") ||
             is_equal(command, "clear")) {

    // Parse the flags
    char *flags[MAX_CMD_SIZE];

    // Initialize the flags array
    for (int i = 0; i < MAX_CMD_SIZE; i++) {
      flags[i] = (char *)0;
    }

    // Define the minimum and maximum flags required for the setcolor command
    int MIN_FLAGS = 0;
    int MAX_FLAGS = 1;

    // Parse the flags
    parse_flags(&input[i], flags, MAX_FLAGS, MIN_FLAGS);

    // If no flags are provided, clear the terminal
    if (flags == (char **)0) {
      // Clear the terminal
      uart_puts("\033[2J \033[1;1H");
      return;
    }

    if (flags[0] == (char *)0) {
      // clear the terminal (by default if no flags are provided)
      uart_puts("\033[2J \033[1;1H");
      return;
    }

    // Check for the flags provided (e.g., -f for full clear)
    if (is_equal(flags[0], "f")) {
      // Clear everything from the terminal
      uart_puts("\033c");
      return;
    }

    // ERROR_COLOR message
    show_status(1, "Invalid flag. Type 'help clear' to see available flags.");
  } else if (is_equal(command, "history") || is_equal(command, "hist")) {
    // Show command history
    print_in_box("Command History");
    get_all_commands(&command_stack);
  } else if (is_equal(command, "setcolor")) {
    // Extract the flags
    char *flags[MAX_CMD_SIZE];

    // Initialize the flags array
    for (int i = 0; i < MAX_CMD_SIZE; i++) {
      flags[i] = (char *)0;
    }

    // Define the minimum and maximum flags required for the setcolor command
    int MIN_FLAGS = 1;
    int MAX_FLAGS = 3;

    // Parse the flags
    int flag_count = parse_flags(&input[i], flags, MAX_FLAGS, MIN_FLAGS);
    if (flag_count == 0) {
      return;
    }

    // Initialize the color option
    if (flags == (char **)0) {
      return;
    }

    // Store the color option
    char *color_option = (char *)0;

    // Loop through the flags and set the colors and execute the each flag
    // sequencially.
    for (int i = 0; i < flag_count; i++) {
      // If the flag is null, break the loop
      if (flags[i] == (char *)0) {
        break;
      }

      // Extract the target and option from the flag (e.g., target: -t, value:
      // red)
      char target[MAX_CMD_SIZE];
      char option[MAX_CMD_SIZE];

      // Parse the target and option
      parse_target(flags[i], target, option);

      // Check for the target and set the color
      if (is_equal(target, "b")) {
        // b flag requires only color and will set the background color
        color_option = to_color(option, 1);

        // If the color option is null or invalid, return from the function
        if (color_option == (char *)0) {
          return;
        }

        // Set the background color
        THEME.BACKGROUND_COLOR = color_option;

      } else if (is_equal(target, "t")) {

        // t flag requires only color and will set the text color
        color_option = to_color(option, 0);

        // If the color option is null or invalid, return from the function
        if (color_option == (char *)0) {
          return;
        }

        // Set the text color
        THEME.PRIMARY_COLOR = color_option;
        THEME.SECONDARY_COLOR = color_option;
      } else if (is_equal(target, "os")) {
        // For the os flag, set the OS theme
        if (is_equal(option, "bright")) {
          THEME.PRIMARY_COLOR = YELLOW;
          THEME.SECONDARY_COLOR = WHITE;
          THEME.BACKGROUND_COLOR = CLEAR;
          THEME.SUCCESS_COLOR = GREEN;
          THEME.ERROR_COLOR = RED;
        } else if (is_equal(option, "dark")) {
          THEME.PRIMARY_COLOR = CYAN;
          THEME.SECONDARY_COLOR = WHITE;
          THEME.BACKGROUND_COLOR = BLACK_BG;
          THEME.SUCCESS_COLOR = GREEN;
          THEME.ERROR_COLOR = RED;
        } else if (is_equal(option, "light")) {
          THEME.PRIMARY_COLOR = BLUE;
          THEME.SECONDARY_COLOR = BLACK;
          THEME.BACKGROUND_COLOR = WHITE_BG;
          THEME.SUCCESS_COLOR = GREEN;
          THEME.ERROR_COLOR = RED;
        } else {
          show_status(
              1,
              "Invalid theme. Type 'help setcolor' to see available themes.");
          return;
        }
      } else if (is_equal(target, "pri")) { // Set primary color
        color_option = to_color(option, 0); // Get the color option

        if (color_option == (char *)0) {
          return;
        }

        THEME.PRIMARY_COLOR = color_option;
      } else if (is_equal(target, "sec")) { // Set secondary color
        color_option = to_color(option, 0); // Get the color option

        if (color_option == (char *)0) {
          return;
        }

        THEME.SECONDARY_COLOR = color_option;
      } else if (is_equal(target, "err")) { // Set error color
        color_option = to_color(option, 0); // Get the color option

        if (color_option == (char *)0) {
          return;
        }

        THEME.ERROR_COLOR = color_option;
      } else if (is_equal(target, "suc")) { // Set success color
        color_option = to_color(option, 0); // Get the color option

        if (color_option == (char *)0) {
          return;
        }

        THEME.SUCCESS_COLOR = color_option;
      } else {
        show_status(
            1,
            "Invalid command. Type 'help setcolor' to see available targets.");
        return;
      }
    }

    // SUCCESS_COLOR message
    show_status(0, "Color set successfully.");
  } else if (is_equal(command, "ref")) {
    // Extract the flags
    char *flags[MAX_CMD_SIZE];

    // Initialize the flags array
    for (int i = 0; i < MAX_CMD_SIZE; i++) {
      flags[i] = (char *)0;
    }

    // Define the minimum and maximum flags required for the setcolor
    // command
    const int MIN_FLAGS = 2;
    const int MAX_FLAGS = 10;

    // Parse the flags
    parse_flags(&input[i], flags, MAX_FLAGS, MIN_FLAGS);
    if (flags == (char **)0) {
      return;
    }

    // Check for the flags provided
    if (is_equal(flags[0], "uart")) {
      // Loop through the flags and set the UART configuration
      for (int i = 1; i < MAX_FLAGS; i++) {
        if (flags[i] == (char *)0) {
          break;
        }

        // Extract the target and option from the flag (e.g., target: -baud,
        // value: 115200)
        char target[MAX_CMD_SIZE];
        char option[MAX_CMD_SIZE];

        // Parse the target and option
        parse_target(flags[i], target, option);

        // Check for the target and set the UART configuration
        if (option == (char *)0) {
          show_status(
              1, "Invalid value. Type 'help ref' to see available targets.");
          return;
        }

        // If the target is baud, set the baud rate
        if (is_equal(target, "baud") || is_equal(target, "bdr")) {
          BaudRateConfig baud_rate = get_baud_rate(string_to_int(option));

          uart_puts("\n");

          str_format("Baud Rate Configuration\n", THEME.PRIMARY_COLOR);

          // Convert the baud rate to a string and display it
          str_format("IBRD: ", THEME.PRIMARY_COLOR);
          char *ibrd = int_to_string(baud_rate.ibrd);
          str_format(ibrd, THEME.SECONDARY_COLOR);

          uart_puts("\n");

          str_format("FBRD: ", THEME.PRIMARY_COLOR);
          char *fbrd = int_to_string(baud_rate.fbrd);
          str_format(fbrd, THEME.SECONDARY_COLOR);

          uart_puts("\n");

          BAUD_RATE_CONFIG.ibrd = baud_rate.ibrd;
          BAUD_RATE_CONFIG.fbrd = baud_rate.fbrd;
          IS_CONFIG_BAUD_RATE = 1;

          // SUCCESS_COLOR message
          show_status(0, "Baud rate set successfully.");
          IS_REINIT_UART = 1;
        } else if (is_equal(target, "dbits") || is_equal(target, "dbs")) {
          int val = string_to_int(option);

          // Data bits must be between 5 and 8
          if (DATA_BITS_CONFIG < 5 || DATA_BITS_CONFIG > 8) {
            show_status(
                1, "Invalid data bits. Data bits must be between 5 and 8.");
            return;
          }
          DATA_BITS_CONFIG = val;

          // SUCCESS_COLOR message
          show_status(0, "Data bits set successfully.");
          IS_REINIT_UART = 1;
        } else if (is_equal(target, "sbits") || is_equal(target, "sbs")) {
          int val = string_to_int(option);

          if (val != 1 && val != 2) {
            show_status(1,
                        "Invalid stop bits. Stop bits must be either 1 or 2.");
            return;
          }

          STOP_BIT_CONFIG = val;

          // SUCCESS_COLOR message
          show_status(0, "Stop bits set successfully.");
          IS_REINIT_UART = 1;
        } else if (is_equal(target, "par")) {
          // Check for the parity option if null
          if (option == (char *)0) {
            show_status(
                1, "Invalid parity. Parity must be either none, even or odd.");
            return;
          }

          // Get the parity value
          int val = string_to_int(option);

          // Check for the parity value
          if (val < 0 || val > 2) {
            show_status(1, "Invalid parity. Parity must be either none (0), "
                           "odd (1) or even (2).");
            return;
          }

          PARITY_CONFIG = val;

          // Succss message
          show_status(0, "Parity set successfully.");
          IS_REINIT_UART = 1;
        } else if (is_equal(target, "handshake") || is_equal(target, "hs") ||
                   is_equal(target, "flow")) {
          // Check for the handshake option if null
          if (option == (char *)0) {
            show_status(1, "Invalid handshake. Handshake must be either "
                           "CTS/RTS (1) or none (0) ");
            return;
          }

          // Get the handshake value
          int val = string_to_int(option);

          // Check for the handshake value (0: none, 1: CTS/RTS, 2+: Not
          // allowed)
          if (val < 0 || val > 1) {
            show_status(1, "Invalid handshake. Handshake must be either "
                           "CTS/RTS (1) or none (0)");
            return;
          }

          // SUCCESS_COLOR message
          HANDSHAKE_CONFIG = string_to_int(option);
          show_status(0, "Handshake set successfully.");
          IS_REINIT_UART = 1;
        } else {
          show_status(
              1, "Invalid command. Type 'help ref' to see available targets.");
          return;
        }
      }
    } else {
      show_status(1,
                  "Invalid command. Type 'help ref' to see available targets.");
      return;
    }
  } else if (is_equal(command, "showinfo")) { // Show device information
    uart_puts("\n\n");

    // Extract the flags
    char *flags[MAX_CMD_SIZE];

    // Initialize the flags array
    for (int i = 0; i < MAX_CMD_SIZE; i++) {
      flags[i] = (char *)0;
    }

    // Define the minimum and maximum flags required for the setcolor
    // command
    const int MIN_FLAGS = 0;
    const int MAX_FLAGS = 1;

    // Parse the flags
    parse_flags(&input[i], flags, MAX_FLAGS, MIN_FLAGS);

    // Tabulate the device information
    char *keys[] = {"Board", "Value"};
    char *values[MAX_ROWS][MAX_ROWS];

    // Initialize the values array
    initialize_values(values, 2);

    // Get MAC Address
    mBuf[0] = 12 * 4;       // Buffer size in bytes
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = 0x00010003;   // TAG Identifier: Get Mac Address
    mBuf[3] = 8;
    mBuf[4] = 0;
    mBuf[5] = 0;
    mBuf[6] = 0; // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[7] = MBOX_TAG_LAST;
    char mac_address[18];

    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
      // Convert the MAC Address to a string
      mac_address_format(mBuf[5], mBuf[6], mac_address);

      // Store the MAC Address in the values array
      values[0][0] = "MAC Address";
      values[0][1] = mac_address;
    } else {
      show_status(1, "Failed to query MAC Address.");
    }

    // Get revision number
    mBuf[0] = 7 * 4;        // Buffer size in bytes
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = 0x00010002;   // TAG Identifier: Get Board Revision
    mBuf[3] = 4;
    mBuf[4] = 0;
    mBuf[5] = 0; // clear output buffer (response data are mBuf[5])
    mBuf[6] = MBOX_TAG_LAST;

    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
      // Store the Board Revision Number in the values array
      values[1][0] = "Board Revision Number";
      values[1][1] = hex_to_string(mBuf[5]);
    } else {
      show_status(1, "Failed to query Board Revision.");
    }

    // Display the device information in tabular format
    tabulate(keys, 2, values, 2);

    // Check for the flags provided (e.g., -v for full information)
    if (is_equal(flags[0], "v")) {
      // Display the full device information (e.g., MAC Address, Board Revision,
      // UART Configuration)
      char *keys[] = {"Uart", "Value"};
      char *values[MAX_ROWS][MAX_ROWS];

      // Initialize the values array
      initialize_values(values, 6);

      // Get uart baud rate
      values[0][0] = "UART Baud Rate (IBRD)";
      char *ibrd = int_to_string(BAUD_RATE_CONFIG.ibrd);
      values[0][1] = ibrd;

      values[1][0] = "UART Baud Rate (FBRD)";
      char *fbrd = int_to_string(BAUD_RATE_CONFIG.fbrd);
      values[1][1] = fbrd;

      // Get uart data bits
      values[2][0] = "Data Bits";
      char *dbits = int_to_string(DATA_BITS_CONFIG);
      values[2][1] = dbits;

      // Get uart stop bits
      values[3][0] = "Stop Bits";
      char *sbits = int_to_string(STOP_BIT_CONFIG);
      values[3][1] = sbits;

      // Get uart parity
      values[4][0] = "Parity";
      char *parity = int_to_string(PARITY_CONFIG);
      values[4][1] = parity;

      // Get uart handshake
      values[5][0] = "Handshake";
      char *handshake = int_to_string(HANDSHAKE_CONFIG);
      values[5][1] = handshake;

      uart_puts("\n");

      // Display the UART configuration in tabular format
      tabulate(keys, 2, values, 6);
      return;
    }
  } else {
    show_status(1, "Command not found. Type 'help' to see available commands.");
  }
}
