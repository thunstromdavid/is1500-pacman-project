# --- Toolchain ---
TOOLCHAIN := riscv64-unknown-elf-
CC       := $(TOOLCHAIN)gcc
LD       := $(TOOLCHAIN)ld
OBJCOPY  := $(TOOLCHAIN)objcopy
OBJDUMP  := $(TOOLCHAIN)objdump
AS       := $(TOOLCHAIN)as

# --- Project layout ---
SRC_DIR := ./
# 
# *** Path to Linker Script ***
# This path points to the linker script in the current directory.
#
LINKER  := ./dtekv-script.lds
SOURCES := $(shell find $(SRC_DIR) -name '*.c' -or -name '*.S')
OBJECTS := $(addsuffix .o, $(basename $(notdir $(SOURCES))))

# --- Flags ---
CFLAGS  := -Wall -nostdlib -O3 -march=rv32imzicsr -mabi=ilp32 -fno-builtin
# LDFLAGS now correctly uses the LINKER variable
LDFLAGS := -T $(LINKER) -nostdlib -static

.PHONY: build clean run
build: clean main.bin

main.elf:
	$(CC) -c $(CFLAGS) $(SOURCES)
#
# *** FIX for 'Multiple Definition' Error ***
#
# Your linker script 'dtekv-script.lds' already includes 'boot.o'
# using the 'STARTUP(boot.o)' command.
#
# The line below filters 'boot.o' from the object list, so it isn't
# added twice. This fixes the error.
#
	# $(LD) -o $@ $(LDFLAGS) boot.o $(filter-out boot.o, $(OBJECTS))
	$(LD) -o $@ $(LDFLAGS) $(filter-out boot.o, $(OBJECTS))

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@
	$(OBJDUMP) -D $< > $<.txt

clean:
	rm -f *.o *.elf *.bin *.txt

TOOL_DIR ?= ./tools
run: main.bin
	make -C $(TOOL_DIR) "FILE_TO_RUN=$(CURDIR)/$<"