#include "../header/uart.h"
#include "../header/gpio.h"
#include "../header/utils.h"

/**
 * Set baud rate and characteristics and map to GPIO
 */
void uart_init()
{
	unsigned int r;

	/* Turn off UART0 */
	UART0_CR = 0x0;

	/* Setup GPIO pins 14 and 15 */

	/* Set GPIO14 and GPIO15 to be pl011 TX/RX which is ALT0	*/
	r = GPFSEL1;
	r &= ~((7 << 12) | (7 << 15));		// clear bits 17-12 (FSEL15, FSEL14)
	r |= (0b100 << 12) | (0b100 << 15); // Set value 0b100 (select ALT0: TXD0/RXD0)
	GPFSEL1 = r;

	/* enable GPIO 14, 15 */
#ifdef RPI3	   // RPI3
	GPPUD = 0; // No pull up/down control
	// Toogle clock to flush GPIO setup
	r = 150;
	while (r--)
	{
		asm volatile("nop");
	} // waiting 150 cycles
	GPPUDCLK0 = (1 << 14) | (1 << 15); // enable clock for GPIO 14, 15
	r = 150;
	while (r--)
	{
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
void uart_sendc(char c)
{

	/* Check Flags Register */
	/* And wait until transmitter is not full */
	do
	{
		asm volatile("nop");
	} while (UART0_FR & UART0_FR_TXFF);

	/* Write our data byte out to the data register */
	UART0_DR = c;
}

/**
 * Receive a character
 */
char uart_getc()
{
	char c = 0;

	/* Check Flags Register */
	/* Wait until Receiver is not empty
	 * (at least one byte data in receive fifo)*/
	do
	{
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
void uart_puts(char *s)
{
	while (*s)
	{
		/* convert newline to carriage return + newline */
		if (*s == '\n')
			uart_sendc('\r');
		uart_sendc(*s++);
	}
}

void uart_logs(int command_index, char *log)
{
	uart_puts("Command ");
	uart_dec(command_index);
	uart_puts(": ");
	uart_puts(log);
	uart_puts("\n");
}

/**
 * Display a value in hexadecimal format
 */
void uart_hex(unsigned int num)
{
	uart_puts("0x");
	for (int pos = 28; pos >= 0; pos = pos - 4)
	{
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
void uart_dec(int num)
{
	// A string to store the digit characters
	char str[33] = "";
	// Calculate the number of digits
	int len = 1;
	int temp = num;
	while (temp >= 10)
	{
		len++;
		temp = temp / 10;
	}
	// Store into the string and print out
	for (int i = 0; i < len; i++)
	{
		int digit = num % 10; // get last digit
		num = num / 10;		  // remove last digit from the number
		str[len - (i + 1)] = digit + '0';
	}
	str[len] = '\0';
	uart_puts(str);
}

// Check if the user has just inputted a new key
unsigned int uart_isReadByteReady()
{
	return !(UART0_FR & UART0_FR_RXFE);
}

/* New function: Check and return if no new character, don't wait */
unsigned char getUart()
{
	unsigned char ch = 0;
	if (uart_isReadByteReady())
		ch = uart_getc();
	return ch;
}

void uart_show_info()
{
	uart_show_log_management_title();

	uart_puts("UART CONFIGURATION\n");

	// Baud rate
	uart_puts("Approximate baud rate: ");
	int baud_rate = calculate_baud_rate();
	uart_dec(baud_rate);

	// TODO: Data bits

	// TODO: Stop bits

	// TODO: Parity

	// TODO: Handshaking mode

	// TODO: Timer Interrupt

	uart_puts("\n\n");
}

int calculate_baud_rate()
{
	// Reconstruct the baud rate divisor
	float baud_divisor = UART0_IBRD + (UART0_FBRD / 64.0f);

	// Calculate the baud rate
	int baud_rate = (int)(UART_CLK / (16.0f * baud_divisor));

	return baud_rate;
}

void uart_show_log_management_title()
{
	uart_puts(
		"\n\n    #     #        ###  #######  #     #       #####   #     #  #######  #######  #######  ###  #     #   #####          \n"
		"   # #    #         #   #        ##    #      #     #  #     #  #     #  #     #     #      #   ##    #  #     #         \n"
		"  #   #   #         #   #        # #   #      #        #     #  #     #  #     #     #      #   # #   #  #               \n"
		" #     #  #         #   #####    #  #  #       #####   #######  #     #  #     #     #      #   #  #  #  #  ####         \n"
		" #######  #         #   #        #   # #            #  #     #  #     #  #     #     #      #   #   # #  #     #         \n"
		" #     #  #         #   #        #    ##      #     #  #     #  #     #  #     #     #      #   #    ##  #     #         \n"
		" #     #  #######  ###  #######  #     #       #####   #     #  #######  #######     #     ###  #     #   #####          \n"
		"                                                                                                                        \n"
		" #        #######   #####       #     #     #     #     #     #      #####   #######  #     #  #######  #     #  ####### \n"
		" #        #     #  #     #      ##   ##    # #    ##    #    # #    #     #  #        ##   ##  #        ##    #     #    \n"
		" #        #     #  #            # # # #   #   #   # #   #   #   #   #        #        # # # #  #        # #   #     #    \n"
		" #        #     #  #  ####      #  #  #  #     #  #  #  #  #     #  #  ####  #####    #  #  #  #####    #  #  #     #    \n"
		" #        #     #  #     #      #     #  #######  #   # #  #######  #     #  #        #     #  #        #   # #     #    \n"
		" #        #     #  #     #      #     #  #     #  #    ##  #     #  #     #  #        #     #  #        #    ##     #    \n"
		" #######  #######   #####       #     #  #     #  #     #  #     #   #####   #######  #     #  #######  #     #     #    \n"
		"                                                                                                                        \n\n");
}
