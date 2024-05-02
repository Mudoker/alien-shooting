#include "./styler.h"

// Function to format string with color and print it
void str_format(const char *str, const char *color_code) {
  // Initialize the formatted string
  static char formatted_str[MAX_STR_LEN];

  // Initialize the string
  formatted_str[0] = '\0';

  // Concatenate strings
  concat(formatted_str, color_code);             // Add color code
  concat(formatted_str, THEME.BACKGROUND_COLOR); // Add background color code
  concat(formatted_str, str);                    // Add the string

  uart_puts(formatted_str); // Print the formatted string
}

// Print text in box
void print_in_box(char *str) {}

// Tabulate keys and values
void tabulate(char *keys[], int numKeys, char *values[][MAX_ROWS],
              int numValues) {}
