// PGCD.h
#include "systemc.h"
  
SC_MODULE(PGCD)
{
   sc_in<bool> clk;
   sc_in<bool> start;            // start est mis à 1 pendant un cycle. On échantilonne x et y si start==1, puis on commence à calculer le PGCD.
   sc_in<unsigned char> x;
   sc_in<unsigned char> y;

   sc_out<unsigned char> pgcd;
   sc_out<bool> done;            // done vaut 0 en général, et 1 pendant un cycle quand le PGCD a été calculé (le PGCD est mis en sortie à ce moment)

   void process();
   unsigned char reg_x, reg_y, var_max, var_min, var_diff;
   /*
   void FSM();
   sc_signal<unsigned char> state;
   */
   SC_CTOR(PGCD){
      SC_METHOD(process);
      sensitive << clk.pos();
   /*
      SC_METHOD(FSM);
      sensitive << clk.pos();
   */
   }
};

