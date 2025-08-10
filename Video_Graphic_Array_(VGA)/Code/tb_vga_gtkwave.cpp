#include <verilated.h>
#include "verilated_vcd_c.h"
#include "Vvga_controller.h"

Vvga_controller* top;
vluint64_t main_time = 0;

double sc_time_stamp() { return main_time; }

uint16_t generate_pixel_data(uint16_t v) {
    if (v < 150) return 0xF800; // Red
    if (v < 300) return 0x07E0; // Green
    if (v < 450) return 0x001F; // Blue
    return 0xFFFF;              // White
}

int main() {
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top = new Vvga_controller;

    top->trace(tfp, 99);
    tfp->open("vga.vcd");

    uint16_t sram[800 * 600] = {0};

    // Reset
    top->clk = 0;
    top->reset = 1;
    for (int i = 0; i < 5; i++) {
        top->clk = 0; top->eval(); tfp->dump(main_time++);
        top->clk = 1; top->eval(); tfp->dump(main_time++);
    }
    top->reset = 0;

    while (!Verilated::gotFinish() && main_time < 2'000'000) {
        top->clk = 0;
        top->eval();
        tfp->dump(main_time++);

        sram[top->sram_address] = generate_pixel_data(top->vc);
        top->sram_data = sram[top->sram_address];

        top->clk = 1;
        top->eval();
        tfp->dump(main_time++);
    }

    tfp->close();
    delete tfp;
    delete top;
    return 0;
}
