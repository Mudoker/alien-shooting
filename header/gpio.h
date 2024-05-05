// --------------------------------------GPIO-------------------------------------

// Raspberry Pi 3 GPIO Registers
#define RPI3
#ifdef RPI3 //RPI3
    #define MMIO_BASE       0x3F000000
#else //RPI4
    #define MMIO_BASE       0xFE000000
#endif

// GPIO Function Select 0
#define GPFSEL0 (*(volatile unsigned int *)(MMIO_BASE + 0x00200000))
// GPIO Function Select 1
#define GPFSEL1 (*(volatile unsigned int *)(MMIO_BASE + 0x00200004))
// GPIO Function Select 2
#define GPFSEL2 (*(volatile unsigned int *)(MMIO_BASE + 0x00200008))
// GPIO Function Select 3
#define GPFSEL3 (*(volatile unsigned int *)(MMIO_BASE + 0x0020000C))
// GPIO Function Select 4
#define GPFSEL4 (*(volatile unsigned int *)(MMIO_BASE + 0x00200010))
// GPIO Function Select 5
#define GPFSEL5 (*(volatile unsigned int *)(MMIO_BASE + 0x00200014))
// GPIO Pin Output Set 0
#define GPSET0 (*(volatile unsigned int *)(MMIO_BASE + 0x0020001C))
// GPIO Pin Output Set 1
#define GPSET1 (*(volatile unsigned int *)(MMIO_BASE + 0x00200020))
// GPIO Pin Output Clear 0
#define GPCLR0 (*(volatile unsigned int *)(MMIO_BASE + 0x00200028))
// GPIO Pin Level 0
#define GPLEV0 (*(volatile unsigned int *)(MMIO_BASE + 0x00200034))
// GPIO Pin Level 1
#define GPLEV1 (*(volatile unsigned int *)(MMIO_BASE + 0x00200038))
// GPIO Pin Event Detect Status 0
#define GPEDS0 (*(volatile unsigned int *)(MMIO_BASE + 0x00200040))
// GPIO Pin Event Detect Status 1
#define GPEDS1 (*(volatile unsigned int *)(MMIO_BASE + 0x00200044))
// GPIO Pin High Detect Enable 0
#define GPHEN0 (*(volatile unsigned int *)(MMIO_BASE + 0x00200064))
// GPIO Pin High Detect Enable 1
#define GPHEN1 (*(volatile unsigned int *)(MMIO_BASE + 0x00200068))
// GPIO Pin Pull-up/down Enable
#define GPPUD (*(volatile unsigned int *)(MMIO_BASE + 0x00200094))
// GPIO Pin Pull-up/down Enable Clock 0
#define GPPUDCLK0 (*(volatile unsigned int *)(MMIO_BASE + 0x00200098))
// GPIO Pin Pull-up/down Enable Clock 1
#define GPPUDCLK1 (*(volatile unsigned int *)(MMIO_BASE + 0x0020009C))

//RBP4 only
#define GPIO_PUP_PDN_CNTRL_REG0    (* (volatile unsigned int*)(MMIO_BASE+0x002000E4))
#define GPIO_PUP_PDN_CNTRL_REG1    (* (volatile unsigned int*)(MMIO_BASE+0x002000E8))
#define GPIO_PUP_PDN_CNTRL_REG2    (* (volatile unsigned int*)(MMIO_BASE+0x002000EC))
#define GPIO_PUP_PDN_CNTRL_REG3    (* (volatile unsigned int*)(MMIO_BASE+0x002000F0))

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;
typedef volatile uint32_t reg32;