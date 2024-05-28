#include "global.h"
#include "gpio.h"
#include "uart.h"

#define MAX_ROWS 20
#define MAX_COLS 5

int tolower(int c);
int strcasecmp(const char *str1, const char *str2);
int strncasecmp(const char *str1, const char *str2, int n);
int is_equal(char *str1, char *str2);
int len(const char *str);
void strcat(char *dest, const char *src);
char *int_to_string(int num);
void strcpy(char *dest, const char *src);
void reallocate(void *dest, const void *src, int n);
void str_format(const char *str, const char *color);
void print_in_box(char *str);
void tabulate(char *keys[], int numKeys, char *values[][MAX_ROWS],
              int numValues);
int starts_with(char *str, char *prefix);
int string_to_int(char *str);
void mac_address_format(unsigned int num1, unsigned int num2,
                        char *mac_address); // Format MAC address
char *
hex_to_string(unsigned int num); // Convert a number to a hexadecimal string
