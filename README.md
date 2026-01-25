# Pacman for DTEK-V (RISC-V)

A hardware-based Pacman clone developed for the **DTEK-V platform (RISC-V)** as part of the course *Computer Organization and Components (IS1500)* at KTH Royal Institute of Technology. 

The project focuses on embedded systems programming with restricted resources, featuring low-level hardware interfacing and real-time synchronization.

## 🕹 Features
* **Full Gameplay Loop:** Includes a start menu, pause functionality, and a game-over screen.
* **Real-time Graphics:** Custom VGA-output rendering the maze, "kernels" (points), and entities on an external screen.
* **Ghost AI:** Automated ghost movement across the entire board.
* **Hardware Interfacing:** Input handled via onboard switches and buttons with tactile response.
* **Collision Logic:** Robust handling of tile-based movement and edge cases, including screen-wrap (tunnel) mechanics.

## 🛠 Technical Details
* **Platform:** DTEK-V (Embedded RISC-V system).
* **Languages:** Mainly **C**, with **RISC-V Assembly** used for critical low-level functions (e.g., `boot.S` for interrupt initialization).
* **Synchronization:** Utilizes the internal hardware timer and **interrupts** to ensure consistent frame updates and game logic timing.
* **Input Handling:** Combines **polling** of hardware switches for movement and push-buttons for system states (start/pause).

## 🚀 Getting Started

### Prerequisites
You need the **RISC-V GNU Toolchain** installed and available in your system path.
* `riscv32-unknown-elf-gcc`
* `riscv32-unknown-elf-ld`
* `riscv32-unknown-elf-objcopy`

*Note: If using a 64-bit toolchain, update the `TOOLCHAIN` variable in the `Makefile` to `riscv64-unknown-elf-`.*

### Compilation
1. Open a terminal in the project root.
2. Run:
   ```bash
   make
The binary will be generated at build/main.bin.

# Verify connection
lsusb | grep "Altera"
jtagconfig

# Run on hardware
cd dtekv-tools
./dtekv-run ../build/main.bin

## 🎮 Controls
* **Start/Pause/Restart:** Use the push button on the board.
* **Movement:** Controlled via the first two hardware switches from the right.

## 🧠 Development & Methodology
The project was developed primarily through Pair Programming (90%), utilizing an iterative testing process to catch logical errors early. We placed a strong emphasis on verification of edge cases, such as collision detection near maze corners and entity behavior during screen-wrapping.

Structuring the project into modular components (graphics.c, game.c, etc.) was key to managing the complexity of the VGA-output and memory-efficient game state.

## 👥 Authors
* Mathias Jonasson
* David Thunström
