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
