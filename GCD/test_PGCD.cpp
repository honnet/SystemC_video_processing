#include "PGCD.h"
#define MAX_TESTS 200 //evite les boucles infinies


void next_cycle (sc_signal<bool> &signal_clk);
int recur_pgcd(int a, int b); //permet de verifier si le "calcul hard" est bon
int pgcdHARD, pgcdSOFT, cpt=0;

/////////////////////////////////////////////////
int sc_main(int argc, char ** argv) {
   sc_signal<bool> clk;
   sc_signal<bool> start;
   sc_signal<unsigned char> x;
   sc_signal<unsigned char> y;
   sc_signal<unsigned char> pgcd;
   sc_signal<bool> done;

   PGCD PGCD("PGCD");
   PGCD.clk(clk);
   PGCD.start(start);
   PGCD.x(x);
   PGCD.y(y);
   PGCD.pgcd(pgcd);
   PGCD.done(done);
   

   sc_trace_file *my_trace_file;
   my_trace_file = sc_create_vcd_trace_file ("PGCD_trace");
   sc_trace(my_trace_file, clk, "clk");
   sc_trace(my_trace_file, start, "start");
   sc_trace(my_trace_file, x, "x");
   sc_trace(my_trace_file, y, "y");
   sc_trace(my_trace_file, pgcd, "pgcd");
   sc_trace(my_trace_file, done, "done");

   for (int i=0; i<256; i++){
      for (int j=0; j<256; j++){ //on ne traite pas les cas avec
         //initialisation :
         x = i;
         y = j;
         start = 1;
         next_cycle(clk);
         start = 0;
         //calcul :
         for(int k=0; k<MAX_TESTS; k++) {
            pgcdHARD = (int)pgcd.read();
            pgcdSOFT = recur_pgcd(i,j);
            if (done == false)  next_cycle(clk);
            else if (pgcdHARD != pgcdSOFT) {
               cout << "ERREUR, on obtient " << pgcdHARD << " au lieu de " << pgcdSOFT;
               cout << " avec x=" << i << " et y=" << j << endl;
               cpt++;
            }
         }
      }
   }
   cout << endl << "nombre d'erreurs : " << cpt << endl;
   sc_close_vcd_trace_file (my_trace_file);

   

   /***********************************************************************/   
   x = 250;
   y = 255;
   start = 1;
   next_cycle(clk);
   start = 0;
   
   for(int i=0; i<MAX_TESTS; i++) {
      if (done==1) break;
      else next_cycle(clk);
   }
   cout << "done:" << (int)done << ", pgcd:" << (int)pgcd << endl << endl;
   return 0;
   /***********************************************************************/



   if (cpt==0) return 0;
   else return 1;
}


/////////////////////////////////////////////////
void next_cycle (sc_signal<bool> &signal_clk){
    signal_clk = false;
    sc_start (1, SC_NS);
    signal_clk = true;
    sc_start (1, SC_NS);
}


/////////////////////////////////////////////////
int recur_pgcd(int a, int b){
   // source : http://www.siteduzero.com/forum-83-283272-p1-calculateur-de-pgcd-par-wowfan10893.html#r2581594
   if (a==0 || b==0) return 0;
   while (a && (b %= a) && (a %= b)); // cryptocalcul !!! ( illisible mais fonctionnel ;-)
   return a + b;
}

