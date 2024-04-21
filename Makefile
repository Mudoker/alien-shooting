#--------------------------------------Makefile-------------------------------------
CFILES = $(wildcard ./src/*.c)
#CFILES = "./src/kernel.c"

OFILES = $(CFILES:./src/%.c=./build/%.o)
#OFILES = "./build/kernel.o"

GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib
LDFLAGS = -nostdlib

all: clean kernel8.img run

#Check UART0 or UART1 define from make process
# To build uart1, type "make UART1=1"
# To build uart0, type "make UART0=1"

#UART0 = 1

# ifdef UART0
# UARTTYPE = 0
# else #UART1
# UARTTYPE = 1
# endif

#Create UART0 or UART1 preprocessing define
#Syntax: add -DVAR to compiler's flag will create #define VAR
GCCFLAGS += -DUART$(UARTTYPE)

#GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -DUART1
#The makefile will generate the #define UART1

./build/boot.o: ./src/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

./build/uart.o:
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/uart/uart.c -o $@

./build/%.o: ./src/%.c
#./build/kernel.o: ./src/kernel.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: ./build/boot.o ./build/uart.o $(OFILES)
	@echo UART$(UARTTYPE) IS BUILDING !!!
	aarch64-none-elf-ld $(LDFLAGS) ./build/boot.o ./build/uart.o $(OFILES)  -T ./src/link.ld -o ./build/kernel8.elf
	aarch64-none-elf-objcopy -O binary ./build/kernel8.elf kernel8.img

clean:
	del *.img .\build\*.elf .\build\*.o

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio
