# --- Toolchain ---
TOOLCHAIN := riscv64-unknown-elf-
CC       := $(TOOLCHAIN)gcc
LD       := $(TOOLCHAIN)ld
OBJCOPY  := $(TOOLCHAIN)objcopy
OBJDUMP  := $(TOOLCHAIN)objdump
AS       := $(TOOLCHAIN)as

# --- Project layout ---
SRC_DIR := ./
LINKER  := $(SRC_DIR)/dtekv-script.lds 
# Keep full paths so objects are unique and predictable
SOURCES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.S)
OBJECTS := $(SOURCES:.c=.o)
OBJECTS := $(OBJECTS:.S=.o)

# --- Flags ---
CFLAGS  := -Wall -nostdlib -O3 -march=rv32imzicsr -mabi=ilp32 -fno-builtin
LDFLAGS := -T $(LINKER) -nostdlib -static

.PHONY: build clean run
build: clean main.bin

main.elf: $(OBJECTS)
	$(LD) -o $@ $(LDFLAGS) $(filter-out %boot.o, $(OBJECTS))

# Compilation rules (emit objects next to sources)
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.S
	$(CC) -c $(CFLAGS) -o $@ $<

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@
	$(OBJDUMP) -D $< > $<.txt

clean:
	rm -f *.o *.elf *.bin *.txt