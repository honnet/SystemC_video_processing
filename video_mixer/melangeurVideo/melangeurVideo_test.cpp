#include "melangeurVideo.h"
#define N_TESTS 10
Pixel randPixel();

int sc_main(int argc, char *argv[]){
   sc_signal<Pixel> pixel1;
   sc_signal<Pixel> pixel2;
   sc_signal<Pixel> pixelOUT;

   sc_trace_file *my_trace_file;
   my_trace_file = sc_create_vcd_trace_file ("melangeurVideo_trace");
   sc_trace(my_trace_file, pixel1, "pixel1");
   sc_trace(my_trace_file, pixel2, "pixel2");
   sc_trace(my_trace_file, pixelOUT, "pixelOUT");

   melangeurVideo melangeurVideo("melangeurVideo");
   melangeurVideo.pixel1(pixel1);
   melangeurVideo.pixel2(pixel2);
   melangeurVideo.pixelOUT(pixelOUT);

   // variable internes :
   int i, cpt = 0;
   Pixel tmp1, tmp2, tmpOUT, hardOUT;
   
   // 10 tests :
   for (i=0; i<N_TESTS; i++){
      tmp1 = randPixel();
      tmp2 = randPixel();
      tmpOUT.R = tmp1.R/2 + tmp2.R/2;
      tmpOUT.G = tmp1.G/2 + tmp2.G/2;
      tmpOUT.B = tmp1.B/2 + tmp2.B/2;
      tmpOUT.A = tmp1.A/2 + tmp2.A/2;

      //interface avec le composant :
      pixel1.write( (Pixel)tmp1 );
      pixel2.write( (Pixel)tmp2 );
      sc_start (1, SC_NS);             // pas de mise à jour ?
      hardOUT = pixelOUT.read();

      //test le resultat :
      if ( tmpOUT == hardOUT )
         cout << ".";
      else {
         cout << "erreur du melange de " << tmp1 << " et de " << tmp2 << ", on obtient " << hardOUT << " au lieu de " << tmpOUT << endl;
         cpt++;
      }
   }
   cout << endl << "nombre d'erreurs : " << cpt << ", nombre de tests : " << N_TESTS << endl;
   sc_close_vcd_trace_file (my_trace_file);
   if (cpt==0) return 0;
   else return 1;
}


Pixel randPixel() {
   Pixel tmp;
   tmp.R = rand();
   tmp.G = rand();
   tmp.B = rand();
   tmp.A = rand();
   return tmp;
}

