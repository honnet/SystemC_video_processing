// melangeurVideo.cpp

#include "melangeurVideo.h"

void melangeurVideo::mix(){
   Pixel tmp1, tmp2, tmpOUT;
   tmp1 = pixel1.read();
   tmp2 = pixel2.read();
   tmpOUT.R = tmp1.R/2 + tmp2.R/2;
   tmpOUT.G = tmp1.G/2 + tmp2.G/2;
   tmpOUT.B = tmp1.B/2 + tmp2.B/2;
   tmpOUT.A = tmp1.A/2 + tmp2.A/2;
   pixelOUT.write(tmpOUT);
}


