// shift.h

#include "systemc.h"

SC_MODULE(shift){
   // in :
   sc_in <bool> clock;
   sc_in <bool> reset;
   sc_in <bool> in;
   // out :
   sc_out<bool> out;

   // variable interne de type bit vector (au lieu de "sc_signal"), permet de décaler ainsi : regs.range(1,7) = regs.range(0,6);
   //sc_bv<8> regs;

   // variable interne, version classique :
   sc_signal<bool> regs[8];
   
   // processus_principal
   void process();
   
   // constructeurs : prend en argument le nom du module, qui servira lors du debug, et passe ce nom au contructeur de la classe de base.
   shift(sc_module_name name);
   // La macro SC_CTOR n'étant pas utilisée ici, on doit utiliser la macro SC_HAS_PROCESS pour spécifier que ce module a un processus :
   SC_HAS_PROCESS(shift);
};

