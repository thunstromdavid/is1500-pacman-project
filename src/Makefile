# --- Toolchain ---
TOOLCHAIN := riscv32-unknown-elf-
CC       := $(TOOLCHAIN)gcc
LD       := $(TOOLCHAIN)ld
OBJCOPY  := $(TOOLCHAIN)objcopy
OBJDUMP  := $(TOOLCHAIN)objdump
AS       := $(TOOLCHAIN)as

# --- Project layout ---
SRC_DIR := ./
LINKER  := $(SRC_DIR)/dtekv-script.lds   # <-- move this up here
SOURCES := $(shell find $(SRC_DIR) -name '*.c' -or -name '*.S')
OBJECTS := $(addsuffix .o, $(basename $(notdir $(SOURCES))))

# --- Flags ---
CFLAGS  := -Wall -nostdlib -O3 -march=rv32imzicsr -mabi=ilp32 -fno-builtin
LDFLAGS := -T $(LINKER) -nostdlib -static

.PHONY: build clean run
build: clean main.bin

main.elf:
	$(CC) -c $(CFLAGS) $(SOURCES)
	# If you need boot.o first, uncomment the next line and comment the one after.
	# $(LD) -o $@ $(LDFLAGS) boot.o $(filter-out boot.o, $(OBJECTS))
	$(LD) -o $@ $(LDFLAGS) $(filter-out boot.o, $(OBJECTS))

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@
	$(OBJDUMP) -D $< > $<.txt

clean:
	rm -f *.o *.elf *.bin *.txt