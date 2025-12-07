Pacman Project - IS1500

Authors:
David Thunström
Mathias Jonasson

Prerequisites:
To compile this project, you need the RISC-V GNU Toolchain installed and available in your system path.
Specifically, the following tools are required:
- riscv32-unknown-elf-gcc
- riscv32-unknown-elf-ld
- riscv32-unknown-elf-objcopy
- riscv32-unknown-elf-objdump

Note: if you have the 64 bit toolchain you only need to replace the 32 in "TOOLCHAIN := riscv32-unknown-elf-
" with 64 in the Makefile.


Compilation:
1. Open a terminal in the project root directory.
2. Run the following command:
   make

This will compile the source code and generate the binary file (.bin).

Output:
The compiled binary will be located at:
build/main.bin

Step by step guide (UNIX):
lsusb (make sure Altera Blaster shows up)
jtagconfig (if this hangs, run "killall jtagd")
cd dtekv-tools
./dtekv-run ../build/main.bin

Game:
To start, pause and restart use the button on the board.
To move the player use the first two switches from the right. 