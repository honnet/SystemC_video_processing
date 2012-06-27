// melangeurVideo.h, (possede deux bus separes de donnees)

#include "systemc.h"

class Pixel {
   public:
      unsigned char R, G, B, A; // A = transparence : '0' = transparent, '255' = opaque.

      Pixel(){};

      Pixel (const Pixel &pix) {
	      R = pix.R;
	      G = pix.G;
	      B = pix.B;
	      A = pix.A;
      };

      Pixel & operator=(const Pixel &pix) {
         R = pix.R;
         G = pix.G;
         B = pix.B;
         A = pix.A;
         return *this;
      };

      bool operator==(const Pixel &pix) const {
         if (pix.R==R && pix.G==G && pix.B==B && pix.A==A) return true;
         else return false;
      };
      
      friend ostream & operator << (ostream &o, const Pixel &pix) {
         o << "P(" << (int)pix.R << "," << (int)pix.G << "," << (int)pix.B << "," << (int)pix.A << ")";
      return o;
      };
      
      inline friend void sc_trace(sc_trace_file *tf, const Pixel &pix, const std::string & NAME ) {
         sc_trace(tf, pix.R, NAME + ".R");
         sc_trace(tf, pix.G, NAME + ".G");
         sc_trace(tf, pix.B, NAME + ".B");
         sc_trace(tf, pix.A, NAME + ".A");
      };
};

  
SC_MODULE(melangeurVideo)
{
   sc_in<Pixel> pixel1;
   sc_in<Pixel> pixel2;
   sc_out<Pixel> pixelOUT;

   void mix();

   SC_CTOR(melangeurVideo){
      SC_METHOD(mix);
      sensitive << pixel1 << pixel2;
   }
};

