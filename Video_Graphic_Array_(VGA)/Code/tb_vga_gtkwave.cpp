#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vvga_controller_800x600.h"

vluint64_t main_time = 0;
double sc_time_stamp() { return main_time; }

int main() {
    int argc = 1;
    const char* argv[] = {"tb_vga_gtkwave"};
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vvga_controller_800x600* top = new Vvga_controller_800x600;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("vga.vcd");

    // Apply reset
    top->reset = 1;
    for (int i = 0; i < 5; ++i) {
        top->clk = 0; top->eval(); tfp->dump(main_time++);
        top->clk = 1; top->eval(); tfp->dump(main_time++);
    }
    top->reset = 0;

    // Main simulation loop
    while (main_time < 20'000'000) {
        top->clk = 0; top->eval(); tfp->dump(main_time++);

        uint16_t v = top->vc;
        uint16_t sram_data = (v < 150) ? 0xF800 :
                             (v < 300) ? 0x07E0 :
                             (v < 450) ? 0x001F : 0xFFFF;

        top->sram_data = sram_data;

        top->clk = 1; top->eval(); tfp->dump(main_time++);
    }

    tfp->close();
    delete tfp;
    delete top;
    return 0;
}

