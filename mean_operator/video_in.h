////////////////////////////////////////////////////////////////////////////////
// File : video_in.h
// Author : Alexis Polti
// Date : 12/03/2008
// This program is released under the GNU Public License
// Copyright : ENST
//
// Ce module modélise le fonctionnement d'une source vidéo.
// 
// On lui donne un nom de base (ex:"img_src_"), et il transmet successivement
// img_src_0.png, img_src_1.png, etc. S'il ne trouve pas une image, il recommence
// à l'index 0.
// 
/////////////////////////////////////////////////////////////////////////
#ifndef VIDEO_IN_H
#define VIDEO_IN_H

#include <systemc.h>
#include "image.h"


////////////////////////////////////////        
//	structure definition
////////////////////////////////////////

SC_MODULE(VIDEO_IN) {
    
// IO PORTS
    
    sc_in<bool>           clk;
    sc_in<bool>           reset_n;
    
    sc_out<bool>          href;
    sc_out<bool>          vref;
    
    sc_out<unsigned char> pixel_out;
    
    
////////////////////////////////////////////////////
//	constructor
////////////////////////////////////////////////////

    SC_CTOR(VIDEO_IN)
        {

            SC_THREAD (gen_sorties);
            sensitive << clk.pos();
            sensitive << reset_n.neg();
            dont_initialize();

            base_name = "wallace";
            
            current_image_number = 0;
            image.pixel = NULL;
            read_image();

            fprintf(stderr, "Successful Instanciation of VIDEO_IN module \n");
            
        }

////////////////////////////////////////////////////
//	methods and structural parameters
////////////////////////////////////////////////////
    

    
  private:
    void gen_sorties();    

    void read_image();
    
    const char *        base_name;              // nom de base des images d'entree
    int                 current_image_number;   // numero de l'image courante

    Image               image;

};

#endif

