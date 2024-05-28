#include "../header/interrupt.h"
#include "../header/timer.h"

void init_interrupts(void) {
  // Enable system timer 1 and 3 interrupts
  init_sys_timer1();
  init_sys_timer3();

  // Enable UART0 interrupt
  enable_uart0_irq();
}

// Enable system timer 1 interrupt
void enable_system_timer1_irq(void) {
  INTERRUPT_ENABLE_IRQS_1 |= SYS_TIMER_IRQ_1;
}

// Disable system timer 1 interrupt
void disable_system_timer1_irq(void) {
  INTERRUPT_DISABLE_IRQS_1 |= SYS_TIMER_IRQ_1;
}

// Enable system timer 3 interrupt
void enable_system_timer3_irq(void) {
  INTERRUPT_ENABLE_IRQS_1 |= SYS_TIMER_IRQ_3;
}

// Disable system timer 3 interrupt
void disable_system_timer3_irq(void) {
  INTERRUPT_DISABLE_IRQS_1 |= SYS_TIMER_IRQ_3;
}

// Enable UART0 interrupt
void enable_uart0_irq(void) { INTERRUPT_ENABLE_IRQS_2 |= UART0_IRQ; }

// Disable UART0 interrupt
void disable_uart0_irq(void) { INTERRUPT_DISABLE_IRQS_2 |= UART0_IRQ; }

void handle_irq_elx(void) {
  unsigned int irq_pending;

  // Check for pending interrupts on IRQ_PENDING_1
  irq_pending = IRQ_PENDING_1;
  if (irq_pending & SYS_TIMER_IRQ_1) {
    handle_sys_timer1();
    // Clear the interrupt after handling
    IRQ_PENDING_1 |= SYS_TIMER_IRQ_1;
  }

  if (irq_pending & SYS_TIMER_IRQ_3) {
    handle_sys_timer3();
    // Clear the interrupt after handling
    IRQ_PENDING_1 |= SYS_TIMER_IRQ_3;
  }

  // Check for pending interrupts on IRQ_BASIC_PENDING
  irq_pending = IRQ_BASIC_PENDING;
  if (irq_pending & UART0_IRQ) {
    // handle_uart0();
    // Clear the interrupt after handling
    IRQ_BASIC_PENDING |= UART0_IRQ;
  }
}
