// shift.cpp

#include "shift.h"
   // constructeur : prend en argument le nom du module, qui servira lors de la génération des chronogrammes
   shift::shift(sc_module_name name) : sc_module(name) {
      SC_METHOD(process);
      sensitive << clock.pos();
   };

   // processus :
   void shift::process() {
      if (reset==false) {
         for (int i=0; i<8; i++) regs[i] = 0;
      }
      else { //ordre non important mais je prefere commencer par la fin par principe :
         out.write(regs[7]);
         for (int i=0; i<7; i++) regs[i+1] = regs[i];
         regs[0] = in.read();
      }
   }

/////////////////////////////////////////
// test-bench :

int sc_main(int argc, char ** argv) {
   
   return 0;
}

