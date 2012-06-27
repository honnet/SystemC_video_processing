////////////////////////////////////////////////////////////////////////////////
// File : video_out.h
// Author : Cedric Honnet
// Date : 17/03/2010
//
// Créer des images PNG à partir d'un flux vidéo CCIR 601
//
////////////////////////////////////////////////////////////////////////////////

#ifndef VIDEO_OUT_H
#define VIDEO_OUT_H

#include <systemc.h>
#include "image.h"


////////////////////////////////////////
//	structure definition
////////////////////////////////////////

SC_MODULE(VIDEO_OUT) {

// IO PORTS

    sc_in<bool>          clk;
    sc_in<bool>          reset_n;

    sc_in<bool>          href;
    sc_in<bool>          vref;

    sc_in<unsigned char> pixel_in;

    // pas de sortie, on ecrit juste dans un fichier !

////////////////////////////////////////////////////
//	constructor
////////////////////////////////////////////////////

// on peut aussi mettre la meilleur qualité HDMI (4096×2160) :
#define WITH_MAX     1000
#define HEIGHT_MAX   1000


    SC_CTOR(VIDEO_OUT)
        {

            SC_THREAD (gen_images);
            sensitive << clk.pos();
            sensitive << reset_n.neg();
            dont_initialize();

            base_name = "output";

            current_image_number = 0;
            image.pixel = NULL;

            image.pixel = (unsigned char *)malloc((WITH_MAX * HEIGHT_MAX) * sizeof(unsigned char));
            assert(image.pixel != NULL);
            image.width = 0;
            image.height = 0;

            fprintf(stderr, "Successful Instanciation of VIDEO_OUT module \n");
        }

////////////////////////////////////////////////////
//	methods and structural parameters
////////////////////////////////////////////////////



  private:
    void gen_images();

    void write_image();

    const char *        base_name;              // nom de base des images d'entree
    int                 current_image_number;   // numero de l'image courante

    Image               image;

    sc_signal<bool>     vref_old;               // permet de detecter un front de vref
    sc_signal<bool>     href_old;               // permet de detecter un front de href
    int cpt_v, cpt_h, cpt_pixels;               // compte les lignes, colonnes et les pixels
                                                // permet de traiter des images de toute taille
};

#endif

