#include "../header/mbox.h"

// A properly aligned buffer
volatile unsigned int __attribute__((aligned(16))) mBuf[36];

// Read from the mailbox
unsigned int mailbox_read(unsigned char channel) {
  // Receiving message is buffer_addr & channel number
  unsigned int res;
  // Make sure that the message is from the right channel
  do {
    // Make sure there is mail to receive
    do {
      asm volatile("nop");
    } while (MBOX0_STATUS & MBOX_EMPTY);
    // Get the message
    res = MBOX0_READ;
  } while ((res & 0xF) != channel);
  return res;
}

// Write to the mailbox
void mailbox_send(unsigned int msg, unsigned char channel) {
  // Make sure that the mailbox is not full
  do {
    asm volatile("nop");
  } while (MBOX1_STATUS & MBOX_FULL);
  // send the message
  MBOX1_WRITE = msg;
}

// Make a mailbox call
int mbox_call(unsigned int buffer_addr, unsigned char channel) {
  // Prepare Data (address of Message Buffer)
  unsigned int msg = (buffer_addr & ~0xF) | (channel & 0xF);
  mailbox_send(msg, channel);
  // Wait for the response
  if (msg == mailbox_read(channel)) {
    /* is it a valid successful response (Response Code) ? */
    if (mBuf[1] == MBOX_RESPONSE)
      return (mBuf[1] == MBOX_RESPONSE);
  }
  return 0;
}