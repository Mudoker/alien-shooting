#include "../header/utils.h"

// Function to convert a string to an integer
int tolower(int c) {
  if (c >= 'A' && c <= 'Z') {
    return c + ('a' - 'A');
  }
  return c;
}

// Function to compare two strings ignoring the case
int strcasecmp(const char *str1, const char *str2) {
  while (*str1 && *str2 && tolower(*str1) == tolower(*str2)) {
    str1++;
    str2++;
  }
  return tolower(*str1) - tolower(*str2);
}

// Function to compare two strings ignoring the case for n characters
int strncasecmp(const char *str1, const char *str2, int n) {
  while (n > 0 && *str1 && *str2 && tolower(*str1) == tolower(*str2)) {
    str1++;
    str2++;
    n--;
  }
  if (n == 0) {
    return 0;
  }
  return tolower(*str1) - tolower(*str2);
}

// Get length of a string
int len(const char *str) {
  int len = 0;
  while (str[len]) {
    len++;
  }
  return len;
}

// Concatenate two strings
void strcat(char *dest, const char *src) {
  while (*dest) {
    dest++;
  }
  while (*src) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
}

// Copy a string
void strcpy(char *dest, const char *src) {
  while (*src) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
}

// Function to convert integer to string
char *int_to_string(int num) {
  static char str[11];
  str[0] = '\0'; // Empty string
  int i = 0;
  if (num == 0) {
    str[i++] = '0';
  } else {
    if (num < 0) {
      str[i++] = '-';
      num = -num;
    }
    int j = 1000000000;
    while (num / j == 0) {
      j /= 10;
    }
    while (j > 0) {
      str[i++] = num / j + '0';
      num %= j;
      j /= 10;
    }
  }
  str[i] = '\0';
  return str;
}

// Function to convert integer to string
void int_to_string_2(int num, char *str) {
  int is_negative = 0;
  int temp_num = num;
  int length = 0;
  char buffer[1000];

  // Handle the special case of 0
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }

  // Check if the number is negative
  if (num < 0) {
    is_negative = 1;
    temp_num = -temp_num;
  }

  // Convert each digit to a character
  while (temp_num != 0) {
    buffer[length++] = (temp_num % 10) + '0';
    temp_num /= 10;
  }

  // Add the negative sign if necessary
  if (is_negative) {
    buffer[length++] = '-';
  }

  // Reverse the string
  for (int i = 0; i < length; i++) {
    str[i] = buffer[length - 1 - i];
  }
  str[length] = '\0'; // Null-terminate the string
}

// memcpy
void reallocate(void *dest, const void *src, int n) {
  char *csrc = (char *)src;
  char *cdest = (char *)dest;
  for (int i = 0; i < n; i++) {
    cdest[i] = csrc[i];
  }
}

// Function to format string with color and print it
void str_format(const char *str, const char *color_code) {
  // Initialize the formatted string
  static char formatted_str[MAX_STR_LEN];

  // Initialize the string
  formatted_str[0] = '\0';

  // Concatenate strings
  strcat(formatted_str, color_code);             // Add color code
  strcat(formatted_str, THEME.BACKGROUND_COLOR); // Add background color code
  strcat(formatted_str, str);                    // Add the string

  uart_puts(formatted_str); // Print the formatted string
}

// Print text in box
void print_in_box(char *str) {
  // Print the formatted string in a box
  uart_puts("\n");

  // Print the box corners
  str_format("+", THEME.SECONDARY_COLOR);

  // Print dashes
  for (int i = 0; i < len(str) + 2; i++) {
    str_format("-", THEME.SECONDARY_COLOR);
  }

  // Print the box corners
  str_format("+", THEME.SECONDARY_COLOR);

  uart_puts("\n");

  // Print the box sides
  str_format("| ", THEME.SECONDARY_COLOR);
  str_format(str, THEME.PRIMARY_COLOR);
  str_format(" |", THEME.SECONDARY_COLOR);

  uart_puts("\n");

  // Print the box corners
  str_format("+", THEME.SECONDARY_COLOR);

  // Print dashes
  for (int i = 0; i < len(str) + 2; i++) {
    str_format("-", THEME.SECONDARY_COLOR);
  }

  // Print the box corners
  str_format("+", THEME.SECONDARY_COLOR);
  uart_puts("\n");
}

// Tabulate keys and values
void tabulate(char *keys[], int numKeys, char *values[][MAX_ROWS],
              int numValues) {

  // Initialize the maximum length of each column
  int maxColLength[MAX_COLS] = {8};

  // Calculate the maximum length of each column
  for (int i = 0; i < numValues; i++) {
    for (int j = 0; j < numKeys && values[i][j] != (char *)0; j++) {
      int colLen = len(values[i][j]);
      if (colLen > maxColLength[j]) {
        maxColLength[j] = colLen;
      }
    }
  }

  // Print keys
  for (int i = 0; i < numKeys; i++) {
    // Print keys for current row
    str_format(keys[i], THEME.PRIMARY_COLOR);

    // Adjust spacing based on the maximum length of the column
    for (int j = 0; j < maxColLength[i] - len(keys[i]) + 12;
         j++) { // Added 4 spaces for padding
      uart_puts(" ");
    }
  }

  uart_puts("\n\n");

  // Print values
  for (int i = 0; i < numValues; i++) {
    // Format values based on the key
    // If the key is "Parity" or "Handshake", format the values
    if (is_equal(values[i][0], "Parity")) {
      // Convert the values from 0, 1, 2 to None, Odd, Even
      if (is_equal(values[i][1], "0")) {
        values[i][1] = "None";
      } else if (is_equal(values[i][1], "1")) {
        values[i][1] = "Odd";
      } else if (is_equal(values[i][1], "2")) {
        values[i][1] = "Even";
      }
    } else if (is_equal(values[i][0], "Handshake")) {
      // Convert the values from 0, 1 to None and RTS/CTS
      if (is_equal(values[i][1], "0")) {
        values[i][1] = "None";
      } else if (is_equal(values[i][1], "1")) {
        values[i][1] = "RTS/CTS";
      } else {
        values[i][1] = "Invalid";
      }
    }

    // Print values for current row
    for (int j = 0; j < numKeys && values[i][j] != (char *)0; j++) {
      str_format(values[i][j], THEME.SECONDARY_COLOR);

      // Adjust spacing based on the maximum length of the column
      for (int k = 0; k < maxColLength[j] - len(values[i][j]) + 12;
           k++) { // Added 4 spaces for padding
        uart_puts(" ");
      }
    }

    uart_puts("\n");
  }
}

// Check if the string starts with the prefix
int starts_with(char *str, char *prefix) {
  if (str == (char *)0 || prefix == (char *)0 || len(str) < len(prefix))
    return 0;

  // Check if the string starts with the prefix
  while (*prefix) {
    if (*prefix != *str) {
      return 0;
    }
    prefix++;
    str++;
  }

  return 1;
}

// Convert a string to an integer
int string_to_int(char *charArray) {
  int result = 0; // Initialize the result
  int sign = 1;   // Positive by default

  // Check for negative sign
  if (*charArray == '-') {
    sign = -1;
    charArray++; // Move past the negative sign
  }

  // Iterate through the characters until the null terminator is reached
  while (*charArray != '\0') {
    // Convert character to digit
    int digit = *charArray - '0';

    // Ensure it's a valid digit
    if (digit >= 0 && digit <= 9) {
      result = result * 10 + digit;
    } else {
      // Invalid character encountered
      uart_puts("Error: Invalid character in integer string\n");
      return 0;
    }

    // Move to the next character
    charArray++;
  }

  // Apply sign
  result *= sign;

  return result;
}

// Convert a string to a hexadecimal integer
void mac_address_format(unsigned int num1, unsigned int num2,
                        char *mac_address) {
  // Extract bytes from the integers
  unsigned char byte1 = (num1 >> 24) & 0xFF;
  unsigned char byte2 = (num1 >> 16) & 0xFF;
  unsigned char byte3 = (num1 >> 8) & 0xFF;
  unsigned char byte4 = num1 & 0xFF;
  unsigned char byte5 = (num2 >> 8) & 0xFF;
  unsigned char byte6 = num2 & 0xFF;

  // Convert bytes to hexadecimal representation
  mac_address[0] =
      (byte4 >> 4) < 10 ? (byte4 >> 4) + '0' : (byte4 >> 4) - 10 + 'A';
  mac_address[1] =
      (byte4 & 0x0F) < 10 ? (byte4 & 0x0F) + '0' : (byte4 & 0x0F) - 10 + 'A';
  mac_address[2] = ':';
  mac_address[3] =
      (byte3 >> 4) < 10 ? (byte3 >> 4) + '0' : (byte3 >> 4) - 10 + 'A';
  mac_address[4] =
      (byte3 & 0x0F) < 10 ? (byte3 & 0x0F) + '0' : (byte3 & 0x0F) - 10 + 'A';
  mac_address[5] = ':';
  mac_address[6] =
      (byte2 >> 4) < 10 ? (byte2 >> 4) + '0' : (byte2 >> 4) - 10 + 'A';
  mac_address[7] =
      (byte2 & 0x0F) < 10 ? (byte2 & 0x0F) + '0' : (byte2 & 0x0F) - 10 + 'A';
  mac_address[8] = ':';
  mac_address[9] =
      (byte1 >> 4) < 10 ? (byte1 >> 4) + '0' : (byte1 >> 4) - 10 + 'A';
  mac_address[10] =
      (byte1 & 0x0F) < 10 ? (byte1 & 0x0F) + '0' : (byte1 & 0x0F) - 10 + 'A';
  mac_address[11] = ':';
  mac_address[12] =
      (byte6 >> 4) < 10 ? (byte6 >> 4) + '0' : (byte6 >> 4) - 10 + 'A';
  mac_address[13] =
      (byte6 & 0x0F) < 10 ? (byte6 & 0x0F) + '0' : (byte6 & 0x0F) - 10 + 'A';
  mac_address[14] = ':';
  mac_address[15] =
      (byte5 >> 4) < 10 ? (byte5 >> 4) + '0' : (byte5 >> 4) - 10 + 'A';
  mac_address[16] =
      (byte5 & 0x0F) < 10 ? (byte5 & 0x0F) + '0' : (byte5 & 0x0F) - 10 + 'A';
  mac_address[17] = '\0'; // Null-terminate the string
}

// Convert an integer to a hexadecimal string
char *hex_to_string(unsigned int number) {
  // Initialize the result buffer
  static char result[MAX_STR_LEN];
  int i = 0;

  do {
    // Get the least significant digit
    int digit = number % 16;

    // Convert digit to character and store it in the result buffer
    result[i++] = (digit < 10) ? (char)(digit + '0') : (char)(digit - 10 + 'A');

    // Move to the next digit
    number /= 16;
  } while (number != 0);

  // Reverse the string
  int j;
  char temp;
  for (j = 0; j < i / 2; j++) {
    temp = result[j];
    result[j] = result[i - j - 1];
    result[i - j - 1] = temp;
  }

  // Add null terminator
  result[i] = '\0';

  return result;
}

// Compare two strings
int is_equal(char *str1, char *str2) {
  // Loop through the strings and compare each character
  while (*str1 && *str2) {
    // Check if the characters are not equal
    if (*str1 != *str2) {
      return 0;
    }
    str1++;
    str2++;
  }

  // Check if both strings have ended simultaneously
  if (*str1 == '\0' && *str2 == '\0') {
    return 1;
  }

  return 0;
}
