#--------------------------------------Makefile-------------------------------------
CFILES = $(wildcard ./src/*.c)

OFILES = $(CFILES:./src/%.c=./build/%.o)

GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib

all: cleanWin kernel8.img runWin
mac: cleanMac kernel8.img runMac
win: cleanWin kernel8.img runWin
./build/boot.o: ./linker/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

./build/%.o: ./src/%.c 
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: ./build/boot.o $(OFILES)
	aarch64-none-elf-ld -nostdlib ./build/boot.o $(OFILES) -T ./linker/link.ld -o kernel8.elf
	aarch64-none-elf-objcopy -O binary kernel8.elf kernel8.img

cleanMac:
	rm -rf *.img *.elf ./build/*.o
cleanWin:
	del *.img *.elf .\build\*.o

runMac:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio
runWin:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio