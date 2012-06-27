#include "ssram.h"

void next_cycle (sc_signal<bool> &signal_clk);


int sc_main(int argc, char *argv[])
{
   sc_signal<unsigned char > addr;
   sc_signal<bool> clk;
   sc_signal<bool> wen_bar;
   sc_signal<unsigned short > data_in;
   sc_signal<unsigned short > data_out;

   sc_trace_file *my_trace_file;
   my_trace_file = sc_create_vcd_trace_file ("ssram_trace");
   sc_trace(my_trace_file, clk, "clk");
   sc_trace(my_trace_file, wen_bar, "wen_bar");
   sc_trace(my_trace_file, addr, "addr");
   sc_trace(my_trace_file, data_in, "data_in");
   sc_trace(my_trace_file, data_out, "data_out");

   ssram ssram("ssram");
   ssram.clk(clk);
   ssram.wen_bar(wen_bar);
   ssram.addr(addr);
   ssram.data_in(data_in);
   ssram.data_out(data_out);

   // variable internes :
   int i, tmp, cpt;
   cpt=0;

   // remplissage de la memoire:
   wen_bar = 0;
   for (i=0; i<256; i++){
      addr = i; // on met quelque chose de prévisible pour pouvoir vérifier
      data_in = i;
      next_cycle(clk);
   }
   wen_bar = 1;

   // verification de la memoire:
   for (i=0; i<256; i++){
      addr = i;
      next_cycle(clk);
      tmp = data_out.read();
      if (tmp != i ) {
         cout << "erreur a l'addresse " << i << ", on obtient " << tmp << " au lieu de " << i << endl;
         cpt++;
      }
   }
   cout << endl << "nombre d'erreurs : " << cpt << endl;
   sc_close_vcd_trace_file (my_trace_file);
   return EXIT_SUCCESS;
}


void next_cycle (sc_signal<bool> &signal_clk)
{
   signal_clk = false;
   sc_start (1, SC_NS); // (1, SC_NS) => 1 Nano Seconde
   signal_clk = true;
   sc_start (1, SC_NS);
}


