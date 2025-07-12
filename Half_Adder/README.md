# Half Adder Simulation using Verilator and GTKWave

## 🔧 Project Overview

This project demonstrates the simulation of a **Half Adder** using Verilog HDL with **Verilator** as the simulator and **GTKWave** as the waveform viewer. It also includes a testbench written in C++ to verify the functionality.

---

## 🧠 What is a Half Adder?

A **Half Adder** is a basic combinational circuit in digital logic that adds two single-bit binary numbers. It has two inputs and two outputs:

- **Inputs:** A and B (1-bit each)
- **Outputs:** 
  - **Sum** (A XOR B)
  - **Carry** (A AND B)

### Truth Table

| A | B | Sum | Carry |
|---|---|-----|--------|
| 0 | 0 |  0  |   0    |
| 0 | 1 |  1  |   0    |
| 1 | 0 |  1  |   0    |
| 1 | 1 |  0  |   1    |

---

## 🖥️ Installation Commands

Follow the steps below to install Verilator and GTKWave:

```bash
sudo apt update && sudo apt install git make autoconf g++ flex help2man
git clone https://github.com/verilator/verilator.git
cd verilator
autoconf
./configure
make -j$(nproc)
sudo make install
verilator --version

# Add Verilator to PATH
echo 'export PATH=$PATH:$HOME/verilator/bin' >> ~/.bashrc
source ~/.bashrc

# Install GTKWave
sudo apt install gtkwave
```

---

## 📁 Project Files

### 1. Half Adder Verilog Code (`half_adder.v`)

```verilog
module half_adder (
  input wire a,
  input wire b,
  output wire sum,
  output wire carry
);
  assign sum = a ^ b;
  assign carry = a & b;
endmodule
```

---

### 2. Testbench Code (`tb_testbench.cpp`)

```cpp
#include "Vhalf_adder.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vhalf_adder* ha = new Vhalf_adder;
    
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    ha->trace(tfp, 99);
    tfp->open("wave.vcd");

    for (int i = 0; i < 4; ++i) {
        ha->a = (i >> 1) & 1;
        ha->b = i & 1;
        ha->eval();
        tfp->dump(i * 10);
        printf("A=%d B=%d | Sum=%d Carry=%d\n", ha->a, ha->b, ha->sum, ha->carry);
    }

    ha->eval();
    tfp->dump(40);
    tfp->close();

    delete ha;
    delete tfp;
    return 0;
}
```

---

## 🧪 Running the Simulation

### 1. Compile with Verilator:

```bash
verilator --cc half_adder.v --exe tb_testbench.cpp --trace
```

### 2. Build the Simulation:

```bash
make -C obj_dir -f Vhalf_adder.mk Vhalf_adder
```

### 3. Run the Simulation:

```bash
./obj_dir/Vhalf_adder
```

### 4. View Waveform:

```bash
gtkwave wave.vcd
```

---

## 💡 Notes

- The waveform file `wave.vcd` helps visualize how the Half Adder responds to each combination of inputs.
- This simulation uses **Verilator’s tracing feature** to generate the waveform data.

---

## 👤 Author

Muhammad Owais  
Project: Half Adder Simulation using Verilator  
System: Ubuntu/Linux with VS Code & Terminal
