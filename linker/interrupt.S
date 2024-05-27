// -----------------------------------interrupt.S -------------------------------------

.globl irq_init_vectors
irq_init_vectors:
    mrs x0, hcr_el2             // Read EL2 Hypervisor Configuration Register
    orr x0, x0,                 // Enable EL2 IRQ Routing
    msr hcr_el2, x0             // Write back to register

.globl irq_enable
irq_enable:
    msr daifclr, #2
    ret

.globl irq_disable
irq_disable:
    msr daifset, #2
    ret