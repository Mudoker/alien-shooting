#include "../commands/os.h"
#include "../global/global.h"
#include "../helper/styler/styler.h"
#include "../helper/utils/utils.h"
#include "../uart/uart.h"

void clear_current_command() {
  // Clear the current command
  uart_puts("\033[2K\r");

  // Show prompt
  char *prompt = str_format("BrightOS> ", COLOR.YELLOW);
  uart_puts(prompt); // Reprint the colored prompt
}

void cli() {
  static char cli_buffer[MAX_CMD_SIZE] = {0};
  static int index = 0;
  static int is_new_command = 1;
  static CommandStack command_stack = {.top_index = -1};
  static int history_index = -1;
  static int was_down = 0;

  // Show prompt only if new command
  if (is_new_command) {
    uart_puts("\n");

    // Show prompt
    char *prompt = str_format("BrightOS> ", COLOR.YELLOW);
    uart_puts(prompt);

    is_new_command = 0;

    // Reset history index
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
      uart_puts("\b \b");
    }
  } else if (c == '+' || c == '_') {
    if (history_index == -1)
      history_index = command_stack.top_index;

    // Navigate command history
    if (c == '+' && history_index >= 0) {
      clear_current_command();

      if (was_down) {
        history_index = (history_index == 0) ? 0 : history_index - 1;
        copy(cli_buffer, command_stack.command[history_index]);
      } else {
        copy(cli_buffer, command_stack.command[history_index]);
        history_index = (history_index == 0) ? 0 : history_index - 1;
      }

      index = len(cli_buffer);
      uart_puts(cli_buffer);

    } else if (c == '_' && history_index <= command_stack.top_index) {
      was_down = 1;

      // Move forward in history (towards older commands)
      clear_current_command();

      history_index = (history_index == command_stack.top_index)
                          ? command_stack.top_index
                          : history_index + 1;

      copy(cli_buffer, command_stack.command[history_index]);
      index = len(cli_buffer);
      uart_puts(cli_buffer);
    }
  } else {
    // Get the command until newline
    if (c != '\n') {
      // Append the character to the buffer
      if (index < MAX_CMD_SIZE - 1) {
        cli_buffer[index] = c;
        index++;
        uart_sendc(c);

      } else {
        uart_puts("\nCommand too long. Please try again.\n");
        index = 0;
        is_new_command = 1;
      }
    } else {
      was_down = 0;
      // Add null terminator to the buffer
      cli_buffer[index] = '\0';
      push_command(&command_stack, cli_buffer);

      parse_command(cli_buffer);
      // // Compare and execute the command
      // if (is_equal(cli_buffer, "os") == 0) {
      //   os_greet();
      // } else if (is_equal(cli_buffer, "clr") == 0 ||
      //            is_equal(cli_buffer, "cls") == 0 ||
      //            is_equal(cli_buffer, "clear") == 0) {
      //   uart_puts("\033c"); // Full terminal reset
      
      if (is_equal(cli_buffer, "hist") == 0) {
        uart_puts("\n");
        get_all_commands(&command_stack);
      }

      // } else {
      //   uart_puts("\nInvalid command. Type 'help' to see available
      //   commands.");
      // }

      // Reset the buffer
      uart_puts("\n");
      index = 0;
      is_new_command = 1;
    }
  }
}

int main() {
  // set up serial console
  uart_init();

  // Welcome message
  //   os_greet();

  // OS loop
  while (1) {
    cli();
  }

  return 0;
}
