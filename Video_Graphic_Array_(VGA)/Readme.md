# VGA Controller Simulation using Verilator, GTKWave, and SDL2

## Project Overview

This project demonstrates the simulation and visualization of a **VGA Controller** designed in **Verilog HDL**. It simulates a 800x600 resolution display system using:

- **Verilator**: To simulate the hardware logic.
- **GTKWave**: To view waveform output of the VGA signals.
- **SDL2**: To visualize real-time RGB output generated from pixel data in a simulated frame buffer.

The design reads RGB pixel data from **SRAM** and displays it during the active display region using VGA timing specifications.

---

## What is a VGA Controller?

A **VGA Controller** is a digital module that drives a VGA-compatible display by generating horizontal and vertical sync signals, and outputting RGB values based on the pixel's location.

### VGA 800x600 Timing Breakdown:

- **Resolution:** 800 (H) × 600 (V)
- **Horizontal Total:** 1056 pixels per line (display + porch + sync)
- **Vertical Total:** 628 lines per frame
- **Color Format:** 16-bit RGB (5 bits red, 6 bits green, 5 bits blue)

---

## Installation Commands

**SDL2** on Ubuntu/Linux:

```bash
# Install SDL2
sudo apt install libsdl2-dev
```

---
##  Project Files

 create a vga_controller_800x600.v verilog file and its two testbench's. tb_vga_gtkwave.cpp for GTKWave Output and vga_controller_800x600_sdl.cpp for SDL2 using Visual Studio Code
 
##  Running the Simulation With GTKWave

### 1. Compile with Verilator:

```bash
verilator -Wall --cc vga_controller_800x600.v --exe tb_vga_gtkwave.cpp --trace
```

### 2. Build the Simulation:

```bash
make -C obj_dir -f Vvga_controller.mk Vvga_controller
```

### 3. Run the Simulation:

```bash
./obj_dir/Vvga_controller
```

### 4. View Waveform:

```bash
gtkwave vga.vcd
```

---

---
##  Running the Simulation With SDL2

### 1. Compile with Verilator and SDL2 Support:

```bash
verilator -cc vga_controller_800x600.v \
  --exe vga_controller_800x600_sdl.cpp \
  --CFLAGS -I/usr/include/SDL2 \
  --LDFLAGS -lSDL2
```

### 2. Build the Simulation Executable:

```bash
make -C obj_dir -j -f Vvga_controller_800x600.mk Vvga_controller_800x600
```

### 3. Run the SDL2 Visualizer:

```bash
./obj_dir/Vvga_controller_800x600
```

##  Author

Muhammad Owais  
Project: Video Graphic Adaptor using Verilator,Gtkwave and SDL2  
System: Ubuntu/Linux with VS Code & Terminal






