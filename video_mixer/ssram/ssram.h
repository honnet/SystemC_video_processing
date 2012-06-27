// ssram.h, (possede deux bus séparés de données)

#include "systemc.h"

SC_MODULE(ssram)
{
   sc_in<bool> clk;
   sc_in<bool> wen_bar; // actif à l'état bas
   sc_in<unsigned char > addr;  // au moins 16bits
   sc_in<unsigned short > data_in;
   sc_out<unsigned short > data_out;

   void read_data();
   void write_data();

   unsigned short ram_data[256];

   SC_CTOR(ssram){
      SC_METHOD(read_data);
      sensitive << clk.pos();
      
      SC_METHOD(write_data);
      sensitive << clk.pos();
   }
};

