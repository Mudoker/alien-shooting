
#include "../header/game/game.h"
#include "../header/global.h"
#include "../header/image.h"
#include "../header/interrupt.h"
#include "../header/os.h"
#include "../header/text.h"
#include "../header/timer.h"
#include "../header/uart.h"
#include "../header/utils.h"
#include "../header/video.h"

// Clear the current command and show the prompt
void clear_current_command() {
  // ANSI escape code to clear the current line
  uart_puts("\033[2K\r");

  // Show prompt
  str_format("BrightOS> ", THEME.PRIMARY_COLOR);
}

// CLI function to get the command from the user
void cli() {
  static char cli_buffer[MAX_CMD_SIZE]; // Buffer to store the command
  static int index = 0;                 // Index to keep track of the buffer
  static int is_new_command = 1; // Flag to check if a new command is entered
  static int history_index = -1; // Index to keep track of command history
  static int was_down = 0; // Check if the current move up after a move down

  // Show prompt only if new command
  if (is_new_command) {
    // Clear the buffer
    for (int i = 0; i < MAX_CMD_SIZE; i++) {
      cli_buffer[i] = '\0';
    }

    str_format("BrightOS> ", THEME.PRIMARY_COLOR);

    // Wait until the TX FIFO is empty
    while (!(UART0_FR & UART0_FR_TXFE)) {
      // Wait until the TX FIFO is empty
    }

    // Check if UART configuration is needed
    if (IS_REINIT_UART == 1) {
      index = len(cli_buffer); // Set the index to the end of the buffer

      /*
      I observed that the UART configuration is not working properly if there
      is no newline character after the uart initialization. To fix this, I
      added a newline character after the UART initialization. Although
      unexpected behavior might be seen on QEMU, it works fine on real
      hardware.
      */
      if (IS_CONFIG_BAUD_RATE == 1) {
        str_format("\n", THEME.SUCCESS_COLOR); // Print a newline
        str_format(" ", THEME.PRIMARY_COLOR);  // Print a space
      }

      // Reinitialize UART
      uart_init();

      // Reset the flag
      IS_REINIT_UART = 0;
    }
    is_new_command = 0;
    history_index = -1;
  }

  // Get command from user
  char c = uart_getc();
  if (c == '\b') {
    // Prevent deleting the prompt
    if (index > 0) {
      // Update the buffer and index
      index--;
      cli_buffer[index] = '\0';

      // Move the cursor back, print a space, and move the cursor back again
      uart_puts("\b \b");
    }
  } else if (c == '\t') { // Tab key pressed
    // Autocomplete command
    char *completed_command = autocomplete_command(cli_buffer);

    // If a command is completed, update the buffer and index
    if (completed_command != (char *)0) {
      // Clear the current command
      clear_current_command();

      // Copy the completed command to the buffer
      strcpy(cli_buffer, completed_command);

      // Move the cursor to the end of the buffer
      index = len(cli_buffer);

      // Print the completed command
      uart_puts(cli_buffer);
    }
  } else if (c == '+' || c == '_') {
    /*
    Set the history index to the top index if it is -1 (no command entered or
    haven't navigated history)
    */
    if (history_index == -1)
      history_index = command_stack.top_index;

    // Move backward in history (towards older commands)
    if (c == '_' && history_index >= 0) {
      clear_current_command();

      // If was_down is true, then the current command is already in the buffer
      if (was_down) {
        // If the history index is at the top, then set the buffer to empty
        history_index = (history_index == 0) ? 0 : history_index - 1;
        strcpy(cli_buffer, command_stack.command[history_index]);
      } else {
        // Copy the current command to the buffer
        strcpy(cli_buffer, command_stack.command[history_index]);
        history_index = (history_index == 0) ? 0 : history_index - 1;
      }

      // Move the cursor to the end of the buffer
      index = len(cli_buffer);
      str_format(cli_buffer, THEME.SECONDARY_COLOR); // Print the command
    } else if (c == '+' && history_index <= command_stack.top_index) {
      // Set the flag to true as this is a move down
      was_down = 1;

      // Move forward in history (towards newer commands)
      clear_current_command();

      history_index++;

      // If the history index is at the top, then add an empty buffer, allowing
      // user to enter a new command
      if (history_index > command_stack.top_index) {
        strcpy(cli_buffer, "");
      } else {
        strcpy(cli_buffer, command_stack.command[history_index]);
      }

      // Move the cursor to the end of the buffer
      index = len(cli_buffer);

      // Print the command
      str_format(cli_buffer, THEME.SECONDARY_COLOR);
    }
  } else if (c != '\n') {
    // Append the character to the buffer
    if (index < MAX_CMD_SIZE - 1) {
      cli_buffer[index] = c;
      index++;

      // Convert character to string and print
      char str[2] = {c, '\0'};
      str_format(str, THEME.SECONDARY_COLOR);
    } else {
      str_format("Command too long\n", THEME.ERROR_COLOR);
      index = 0;
      is_new_command = 1;
    }
  } else if (c == '\n') {
    // Reset the flag
    was_down = 0;

    // Add null terminator to the buffer
    cli_buffer[index] = '\0';

    // Push the command to the history stack
    push_command(&command_stack, cli_buffer);

    // Parse the command from the buffer and execute
    parse_command(cli_buffer);

    // Reset the flag and index
    index = 0;
    is_new_command = 1;
  }
}

int main() {
  uart_init();       // Initialize UART
  os_greet();        // Show welcome message
  init_interrupts(); // Initialize interrupts

  while (True) {
    uart_puts(THEME.BACKGROUND_COLOR); // Set background color
    cli();                             // Get command from user
  }

  return 0;
}

// int main() {
//   uart_init();       // Initialize UART
//   init_interrupts(); // Initialize interrupts

//   while (1) {
//     handle_irq_elx(); // Handle pending interrupts
//   }

//   return 0;
// }
