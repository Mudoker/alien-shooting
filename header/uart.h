// --------------------------------------UART-------------------------------------

// This file contains the definitions for the UART functions and the UART
#ifndef UART_H
#define UART_H

// #include "global.h"
#include "gpio.h"

// PL011 UART (UART0) registers
#define UART0_BASE (MMIO_BASE + 0x201000)

// DR = Data register
#define UART0_DR (*(volatile unsigned int *)(UART0_BASE + 0x00))

// RSRECR = Receive status register/error clear register
#define UART0_RSRECR (*(volatile unsigned int *)(UART0_BASE + 0x04))

// FR = Flags Register
#define UART0_FR (*(volatile unsigned int *)(UART0_BASE + 0x18))
// TXFE = Transmit FIFO empty
#define UART0_FR_TXFE (1 << 7)
// RXFF = Receive FIFO full
#define UART0_FR_RXFF (1 << 6)
// TXFF = Transmit FIFO full
#define UART0_FR_TXFF (1 << 5)
// RXFE = Receive FIFO empty
#define UART0_FR_RXFE (1 << 4)
// BUSY = UART is busy transmitting
#define UART0_FR_BUSY (1 << 3)
// Inverted version of nUARTCTS value
#define UART0_FR_CTS (1 << 0)

// ILPR = Infrared, disabled on BC2835
#define UART0_ILPR (*(volatile unsigned int *)(UART0_BASE + 0x20))

// IBRD = Integer part of Baud Rate Divisor
#define UART0_IBRD (*(volatile unsigned int *)(UART0_BASE + 0x24))

// FBRD = Fractional part of Baud Rate Divisor
#define UART0_FBRD (*(volatile unsigned int *)(UART0_BASE + 0x28))

// LCRH = Line Control Register
#define UART0_LCRH (*(volatile unsigned int *)(UART0_BASE + 0x2C))
// SPS = Stick Parity Select (0=disabled)
#define UART0_LCRH_SPS (1 << 7)
// WLEN = word length
#define UART0_LCRH_WLEN_5BIT (0 << 5) /* 5 bits */
#define UART0_LCRH_WLEN_6BIT (1 << 5) /* 6 bits */
#define UART0_LCRH_WLEN_7BIT (2 << 5) /* 7 bits */
#define UART0_LCRH_WLEN_8BIT (3 << 5) /* 8 bits */
// FEN = FIFO Enable
#define UART0_LCRH_FEN (1 << 4)
#define UART0_LCRH_STP2 (1 << 3) /* STP2 = enable 2 stop bits */
#define UART0_LCRH_EPS (1 << 2)  /* EPS  = even parity select */
#define UART0_LCRH_PEN (1 << 1)  /* PEN  = parity enable */
#define UART0_LCRH_BRK (1 << 0)  /* BRK  = send break after next character */

// CR = Control Register
#define UART0_CR (*(volatile unsigned int *)(UART0_BASE + 0x30))
#define UART0_CR_CTSEN (1 << 15) /*   15 = CTSEN = CTS Flow Enable */
#define UART0_CR_RTSEN (1 << 14) /*   14 = RTSEN = RTS Flow Enable */
#define UART0_CR_RTS (1 << 11)   /*   11 = RTS = Request to Send */
#define UART0_CR_RXE (1 << 9)    /*    9 = RXE = Receive Enable */
#define UART0_CR_TXE (1 << 8)    /*    8 = TXE = Transmit Enable */
#define UART0_CR_LBE (1 << 7)    /*    7 = LBE = Loopback Enable */
#define UART0_CR_UARTEN (1 << 0) /*    0 = UARTEN = UART Enable */

// IFLS = FIFO Level Select
#define UART0_IFLS (*(volatile unsigned int *)(UART0_BASE + 0x34))

// IMSRC = Interrupt Mask Set/Clear
#define UART0_IMSC (*(volatile unsigned int *)(UART0_BASE + 0x38))

// RIS = Raw Interrupt Status
#define UART0_IMSC_OE (1 << 10) /* OERIS = Overrun Interrupt Raw Status */
#define UART0_IMSC_BE (1 << 9)  /* BERIS = Break Interrupt Raw Status*/
#define UART0_IMSC_PE (1 << 8)  /* PERIS = Parity Interrupt Raw Status */
#define UART0_IMSC_FE (1 << 7)  /* FERIS = Framing Interrupt Raw Status */
#define UART0_IMSC_RT (1 << 6)  /* RTRIS = Receivce Timeout Raw Status */
#define UART0_IMSC_TX (1 << 5)  /* TXRIS = Transmit Interrupt Raw Status */
#define UART0_IMSC_RX (1 << 4)  /* RXRIS = Receive Raw Status */
#define UART0_IMSC_CTS (1 << 1)

// CTSRIS = nUARTCTS Raw Status
#define UART0_RIS (*(volatile unsigned int *)(UART0_BASE + 0x3C))

// MIS = Masked Interrupt Status
#define UART0_MIS (*(volatile unsigned int *)(UART0_BASE + 0x40))

// ICR = Interrupt Clear Register
#define UART0_ICR (*(volatile unsigned int *)(UART0_BASE + 0x44))

// DMACR = DMA Control Register
//  This is disabled on the BCM2835
#define UART0_DMACR (*(volatile unsigned int *)(UART0_BASE + 0x48))

// ITCR = Test Control Register
#define UART0_ITCR (*(volatile unsigned int *)(UART0_BASE + 0x80))

// ITIP = Test Control Register
#define UART0_ITIP (*(volatile unsigned int *)(UART0_BASE + 0x84))

// ITOP = Test Control Register
#define UART0_ITOP (*(volatile unsigned int *)(UART0_BASE + 0x88))

// TDR = Test Data Register
#define UART0_TDR (*(volatile unsigned int *)(UART0_BASE + 0x8C))

// Define the UART clock speed
#define UART_CLK 48000000

// Baud rate configuration
typedef struct {
  unsigned int ibrd; // Integer baud rate divisor
  unsigned int fbrd; // Fractional baud rate divisor
} BaudRateConfig;

// UART0 initialization
extern BaudRateConfig BAUD_RATE_CONFIG; // Baud rate configuration
extern int DATA_BITS_CONFIG;            // Data bits configuration
extern int STOP_BIT_CONFIG;             // Stop bit configuration
extern int PARITY_CONFIG;               // Parity configuration
extern int HANDSHAKE_CONFIG;            // Handshake configuration
extern int IS_REINIT_UART;              // UART reinitialization state
extern int IS_CONFIG_BAUD_RATE; // Flag to check if the baud rate is configured

// Function prototypes
void uart_init();              // Initialize UART
void uart_sendc(char c);       // Send a character
char uart_getc();              // Get a character
void uart_puts(char *s);       // Send a string
void uart_hex(unsigned int d); // Print a hex number
void uart_dec(int num);        // Print a decimal number
unsigned int uart_isReadByteReady();
unsigned char getUart();
void uart_alert(char *alert);
void uart_logs(int command_index, char *log, char *c, int is_positive);
void uart_show_info();

#endif
