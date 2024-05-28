#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "gpio.h"

// Base MMIO address
#define MMIO_BASE 0x3F000000

// Interrupt controller base address
#define INTERRUPT_BASE (MMIO_BASE + 0xB000)

// Interrupt controller registers for RPI3
#define IRQ_BASIC_PENDING (*(volatile unsigned int *)(INTERRUPT_BASE + 0x200))
#define IRQ_PENDING_1 (*(volatile unsigned int *)(INTERRUPT_BASE + 0x204))
#define IRQ_PENDING_2 (*(volatile unsigned int *)(INTERRUPT_BASE + 0x208))
#define FIQ_CONTROL (*(volatile unsigned int *)(INTERRUPT_BASE + 0x20C))
#define INTERRUPT_ENABLE_IRQS_1                                                \
  (*(volatile unsigned int *)(INTERRUPT_BASE + 0x210))
#define INTERRUPT_ENABLE_IRQS_2                                                \
  (*(volatile unsigned int *)(INTERRUPT_BASE + 0x214))
#define ENABLE_BASIC_IRQS (*(volatile unsigned int *)(INTERRUPT_BASE + 0x218))
#define INTERRUPT_DISABLE_IRQS_1                                               \
  (*(volatile unsigned int *)(INTERRUPT_BASE + 0x21C))
#define INTERRUPT_DISABLE_IRQS_2                                               \
  (*(volatile unsigned int *)(INTERRUPT_BASE + 0x220))
#define DISABLE_BASIC_IRQS (*(volatile unsigned int *)(INTERRUPT_BASE + 0x224))

// IRQ definitions
#define SYS_TIMER_IRQ_0 (1 << 0)
#define SYS_TIMER_IRQ_1 (1 << 1)
#define SYS_TIMER_IRQ_2 (1 << 2)
#define SYS_TIMER_IRQ_3 (1 << 3)
#define UART0_IRQ (1 << 25)

// Assembly functions
void init_interrupts(void);
void enable_interrupts(void);
void disable_interrupts(void);

// IRQ handlers
void enable_system_timer1_irq(void);
void disable_system_timer1_irq(void);
void enable_system_timer3_irq(void);
void disable_system_timer3_irq(void);
void enable_uart0_irq(void);
void disable_uart0_irq(void);
void handle_irq_elx(void);

#endif // INTERRUPT_H
