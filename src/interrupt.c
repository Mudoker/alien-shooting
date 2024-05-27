#include "../header/interrupt.h"

void enable_system_timer1_irq() {
#ifdef RPI3
    INTERRUPT_ENABLE_IRQS_1 |= SYS_TIMER_1_IRQ;
#else
    IRQ0_SET_EN_0 |= SYS_TIMER_1_IRQ;
#endif
}

void disable_system_timer1_irq() {
#ifdef RPI3
    INTERRUPT_DISABLE_IRQS_1 |= SYS_TIMER_1_IRQ;
#else
    IRQ0_CLR_EN_0 |= SYS_TIMER_1_IRQ;
#endif
}

void enable_system_timer3_irq() {
#ifdef RPI3
    INTERRUPT_ENABLE_IRQS_1 |= SYS_TIMER_3_IRQ;
#else
    IRQ0_SET_EN_0 |= SYS_TIMER_3_IRQ;
#endif
}

void disable_system_timer3_irq() {
#ifdef RPI3
    INTERRUPT_DISABLE_IRQS_1 |= SYS_TIMER_3_IRQ;
#else
    IRQ0_CLR_EN_0 |= SYS_TIMER_3_IRQ;
#endif
}

void enable_uart0_irq() {
#ifdef RPI3
    INTERRUPT_ENABLE_IRQS_2 |= UART0_IRQ;
#else
    IRQ0_SET_EN_1 |= UART0_IRQ;
#endif
}

void disable_uart0_irq() {
#ifdef RPI3
    INTERRUPT_DISABLE_IRQS_2 |= UART0_IRQ;
#else
    IRQ0_CLR_EN_1 |= UART0_IRQ;
#endif
}

void handle_irq_elx(void) {
    unsigned int irq_pending;

#ifdef RPI3
    irq_pending = INTERRUPT_IRQ_PENDING_2;
#else
    irq_pending = INTERRUPT_IRQ_PENDING_1;
#endif

    if (irq_pending & UART0_IRQ) {
        // handle_uart0();
        irq_pending &= ~UART0_IRQ;
    }

#ifdef RPI3
    irq_pending = INTERRUPT_IRQ_PENDING_1;
#else
    irq_pending = INTERRUPT_IRQ_PENDING_0;
#endif

    if (irq_pending & SYS_TIMER_1_IRQ) {
        handle_timer1();
        irq_pending &= ~SYS_TIMER_1_IRQ;
    }

    if (irq_pending & SYS_TIMER_3_IRQ) {
        handle_timer3();
        irq_pending &= ~SYS_TIMER_3_IRQ;
    }
}
