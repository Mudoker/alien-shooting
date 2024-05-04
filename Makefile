#--------------------------------------Makefile-------------------------------------
GAME_DIR = ./src/game
BUILD_DIR = ./build

CFILES = $(wildcard ./src/*.c)
OFILES = $(CFILES:./src/%.c=./build/%.o)

GAMECFILES = $(wildcard $(GAME_DIR)/*.c)
GAMEOFILES = $(GAMECFILES:$(GAME_DIR)/%.c=$(BUILD_DIR)/%.o)

GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib

all: clean kernel8.img run

./build/boot.o: ./linker/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

./build/%.o: ./src/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(GAME_DIR)/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: ./build/boot.o $(OFILES) $(GAMEOFILES)
	aarch64-none-elf-ld -nostdlib ./build/boot.o $(OFILES) $(GAMEOFILES) -T ./linker/link.ld -o kernel8.elf
	aarch64-none-elf-objcopy -O binary kernel8.elf kernel8.img

clean:
	del *.img *.elf .\build\*.o

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio