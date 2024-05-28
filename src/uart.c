#include "../header/uart.h"
#include "../header/gpio.h"
#include "../header/utils.h"

// 115200 baud rate configuration for UART
BaudRateConfig BAUD_RATE_CONFIG = {
    .ibrd = 26,
    .fbrd = 3,
};

// State of the UART
int IS_REINIT_UART = 0;      // UART reinitialization state
int DATA_BITS_CONFIG = 8;    // Data bits configuration (default 8 bits)
int STOP_BIT_CONFIG = 2;     // Stop bit configuration (default 2 bit)
int PARITY_CONFIG = 0;       // Parity configuration (default None)
int HANDSHAKE_CONFIG = 0;    // Handshake configuration (default None)
int IS_CONFIG_BAUD_RATE = 0; // Baud rate configuration state

// Function prototypes
void uart_show_log_management_title();

/**
 * Set baud rate and characteristics and map to GPIO
 */
void uart_init() {
  unsigned int r;

  /* Turn off UART0 */
  UART0_CR = 0x0;

  /* Setup GPIO pins 14 and 15 */

  /* Set GPIO14 and GPIO15 to be pl011 TX/RX which is ALT0	*/
  r = GPFSEL1;
  r &= ~((7 << 12) | (7 << 15)); // clear bits 17-12 (FSEL15, FSEL14)
  r |=
      (0b100 << 12) | (0b100 << 15); // Set value 0b100 (select ALT0: TXD0/RXD0)
  GPFSEL1 = r;

  /* enable GPIO 14, 15 */
#ifdef RPI3  // RPI3
  GPPUD = 0; // No pull up/down control
  // Toogle clock to flush GPIO setup
  r = 150;
  while (r--) {
    asm volatile("nop");
  } // waiting 150 cycles
  GPPUDCLK0 = (1 << 14) | (1 << 15); // enable clock for GPIO 14, 15
  r = 150;
  while (r--) {
    asm volatile("nop");
  } // waiting 150 cycles
  GPPUDCLK0 = 0; // flush GPIO setup

#else // RPI4
  r = GPIO_PUP_PDN_CNTRL_REG0;
  r &= ~((3 << 28) | (3 << 30)); // No resistor is selected for GPIO 14, 15
  GPIO_PUP_PDN_CNTRL_REG0 = r;
#endif

  /* Mask all interrupts. */
  UART0_IMSC = 0;

  /* Clear pending interrupts. */
  UART0_ICR = 0x7FF;

  /* Set integer & fractional part of Baud rate
  Divider = UART_CLOCK/(16 * Baud)
  Default UART_CLOCK = 48MHz (old firmware it was 3MHz);
  Integer part register UART0_IBRD  = integer part of Divider
  Fraction part register UART0_FBRD = (Fractional part * 64) + 0.5 */

  // 115200 baud
  UART0_IBRD = 26;
  UART0_FBRD = 3;

  /* Set up the Line Control Register */
  /* Enable FIFO */
  /* Set length to 8 bit */
  /* Defaults for other bit are No parity, 1 stop bit */
  UART0_LCRH = UART0_LCRH_FEN | UART0_LCRH_WLEN_8BIT;

  /* Enable UART0, receive, and transmit */
  UART0_CR = 0x301; // enable Tx, Rx, FIFO
}

/**
 * Send a character
 */
void uart_sendc(char c) {

  /* Check Flags Register */
  /* And wait until transmitter is not full */
  do {
    asm volatile("nop");
  } while (UART0_FR & UART0_FR_TXFF);

  /* Write our data byte out to the data register */
  UART0_DR = c;
}

/**
 * Receive a character
 */
char uart_getc() {
  char c = 0;

  /* Check Flags Register */
  /* Wait until Receiver is not empty
   * (at least one byte data in receive fifo)*/
  do {
    asm volatile("nop");
  } while (UART0_FR & UART0_FR_RXFE);

  /* read it and return */
  c = (unsigned char)(UART0_DR);

  /* convert carriage return to newline */
  return (c == '\r' ? '\n' : c);
}

/**
 * Display a string
 */
void uart_puts(char *s) {
  while (*s) {
    /* convert newline to carriage return + newline */
    if (*s == '\n')
      uart_sendc('\r');
    uart_sendc(*s++);
  }
}

void uart_logs(int command_index, char *log) {
  uart_puts("Command ");
  uart_dec(command_index);
  uart_puts(": ");
  uart_puts(log);
  uart_puts("\n");
}

/**
 * Display a value in hexadecimal format
 */
void uart_hex(unsigned int num) {
  uart_puts("0x");
  for (int pos = 28; pos >= 0; pos = pos - 4) {
    // Get highest 4-bit nibble
    char digit = (num >> pos) & 0xF;
    /* Convert to ASCII code */
    // 0-9 => '0'-'9', 10-15 => 'A'-'F'
    digit += (digit > 9) ? (-10 + 'A') : '0';
    uart_sendc(digit);
  }
}
/**
 * Display a value in decimal format
 */
void uart_dec(int num) {
  // A string to store the digit characters
  char str[33] = "";
  // Calculate the number of digits
  int len = 1;
  int temp = num;
  while (temp >= 10) {
    len++;
    temp = temp / 10;
  }
  // Store into the string and print out
  for (int i = 0; i < len; i++) {
    int digit = num % 10; // get last digit
    num = num / 10;       // remove last digit from the number
    str[len - (i + 1)] = digit + '0';
  }
  str[len] = '\0';
  uart_puts(str);
}

// Check if the user has just inputted a new key
unsigned int uart_isReadByteReady() { return !(UART0_FR & UART0_FR_RXFE); }

/* New function: Check and return if no new character, don't wait */
unsigned char getUart() {
  unsigned char ch = 0;
  if (uart_isReadByteReady())
    ch = uart_getc();
  return ch;
}

void uart_show_info() {
  uart_show_log_management_title();

  uart_puts("UART CONFIGURATION\n"
            "===============================\n"
            "| Setting            | Value   |\n"
            "-------------------------------\n"
            "| UART Port          | UART0   |\n"
            "| Baud rate          | 115200  |\n"
            "| Data bits          | 8       |\n"
            "| Stop bits          | 1       |\n"
            "| Parity             | None    |\n"
            "| Handshaking mode   | On      |\n"
            "===============================\n\n");

  // TODO: Timer Interrupt
}

void uart_show_log_management_title() {
  uart_puts("\n\n    #     #        ###  #######  #     #       #####   #     "
            "#  #######  #######  #######  ###  #     #   #####          \n"
            "   # #    #         #   #        ##    #      #     #  #     #  # "
            "    #  #     #     #      #   ##    #  #     #         \n"
            "  #   #   #         #   #        # #   #      #        #     #  # "
            "    #  #     #     #      #   # #   #  #               \n"
            " #     #  #         #   #####    #  #  #       #####   #######  # "
            "    #  #     #     #      #   #  #  #  #  ####         \n"
            " #######  #         #   #        #   # #            #  #     #  # "
            "    #  #     #     #      #   #   # #  #     #         \n"
            " #     #  #         #   #        #    ##      #     #  #     #  # "
            "    #  #     #     #      #   #    ##  #     #         \n"
            " #     #  #######  ###  #######  #     #       #####   #     #  "
            "#######  #######     #     ###  #     #   #####          \n"
            "                                                                  "
            "                                                      \n"
            " #        #######   #####       #     #     #     #     #     #   "
            "   #####   #######  #     #  #######  #     #  ####### \n"
            " #        #     #  #     #      ##   ##    # #    ##    #    # #  "
            "  #     #  #        ##   ##  #        ##    #     #    \n"
            " #        #     #  #            # # # #   #   #   # #   #   #   # "
            "  #        #        # # # #  #        # #   #     #    \n"
            " #        #     #  #  ####      #  #  #  #     #  #  #  #  #     "
            "#  #  ####  #####    #  #  #  #####    #  #  #     #    \n"
            " #        #     #  #     #      #     #  #######  #   # #  "
            "#######  #     #  #        #     #  #        #   # #     #    \n"
            " #        #     #  #     #      #     #  #     #  #    ##  #     "
            "#  #     #  #        #     #  #        #    ##     #    \n"
            " #######  #######   #####       #     #  #     #  #     #  #     "
            "#   #####   #######  #     #  #######  #     #     #    \n"
            "                                                                  "
            "                                                      \n\n");
}

// Calculate baud rate
BaudRateConfig get_baud_rate(int baud_rate) {
  // Define valid baud rates
  const int VALID_BAUD[] = {
      300,   600,   1200,  2400,   4800,   9600,   14400,
      19200, 38400, 57600, 921600, 230400, 460800, 115200,
  };

  BaudRateConfig config;

  // Validate baud rate
  for (int i = 0; i <= 13; i++) {
    if (baud_rate == VALID_BAUD[i]) {
      uart_puts("\n\nBaud rate set to ");
      uart_dec(baud_rate);
      uart_puts("\n");
      break;
    }

    // Give warning if baud rate is invalid
    if (i == 13) {
      // Return default baud rate
      str_format("\n\nInvalid baud rate \n", THEME.ERROR_COLOR);

      str_format("Supported values: 300, 1200, 2400, 4800, 9600, "
                 "19200, 38400, 57600, 115200, 230400, 460800, 921600\n\n",
                 THEME.SECONDARY_COLOR);

      str_format("Reverting... \n", THEME.ERROR_COLOR);

      // Set default baud rate
      config = BAUD_RATE_CONFIG;
      return config;
    }
  }

  // Calculate Divider
  float divider = (float)UART_CLK / (16.0f * baud_rate);

  // Calculate integer and fractional parts of Divider
  int integerPart = (int)divider;
  float fractionalPart = divider - integerPart;

  // Calculate the integer part of the baud rate divisor
  config.ibrd = integerPart;

  // Calculate the fractional part of the baud rate divisor
  config.fbrd = (int)(fractionalPart * 64 + 0.5);

  return config;
}
