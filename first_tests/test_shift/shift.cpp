
   // shift.cpp

   #include "shift.h"

   // Conctructeur
   shifter::shifter(sc_module_name name)
       :sc_module(name)
   {
       SC_METHOD(shift);
       sensitive << clk.pos();
   }

   // Processus
   void shifter::shift()
   {
       int i;
       for(i=0; i<7; i++)
           regs[i+1] = regs[i];
       regs[0] = din;
       dout = regs[7];
   }




