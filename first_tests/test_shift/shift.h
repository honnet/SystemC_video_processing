// shift.h

#include "systemc.h"

SC_MODULE(shifter)
{
    // Ports
    sc_in<bool> clk;

    sc_in<bool> din;
    sc_out<bool> dout;

    // Variable interne
    sc_signal<bool> regs[8];

    // Processus principal
    void shift();

    // Constructeur
    shifter(sc_module_name name);

    SC_HAS_PROCESS(shifter);

};


