////////////////////////////////////////////////////////////////////////////////
// File : video_effect.h
// Author : Cédric Honnet
// Date : 17/03/2010
//
// filtre moyenneur sur 8 pixels voisins
//
/////////////////////////////////////////////////////////////////////////

#ifndef VIDEO_EFFECT_H
#define VIDEO_EFFECT_H

#define BUF_SIZE (720*2 + 3) // il faut memoriser 2 lignes et 3 pixels pour le moyenneur

#include "image.h"
#include <systemc.h>


////////////////////////////////////////
//	structure definition
////////////////////////////////////////

SC_MODULE(VIDEO_EFFECT){

   ////////////////////////////////////////////////////
   //	methods and structural parameters
   ////////////////////////////////////////////////////

   void gen_effet();

   //ports d'entrée
   sc_in<bool> clk;
   sc_in<bool> reset_n;
   sc_in<bool> href_in;
   sc_in<bool> vref_in;
   sc_in<unsigned char> pixel_in;

   //ports de sortie
   sc_out<bool> href_out;
   sc_out<bool> vref_out;
   sc_out<unsigned char> pixel_out;

   // variables internes :
   unsigned char buffer[BUF_SIZE];
   bool vref_old[2];
   bool href_old[3];

   ////////////////////////////////////////////////////
   //	constructor
   ////////////////////////////////////////////////////

   SC_CTOR(VIDEO_EFFECT)
   {
       SC_METHOD(gen_effet);
       sensitive << clk.pos();
       sensitive << reset_n.neg();
       dont_initialize();
       fprintf(stderr, "Successful Instanciation of VIDEO_EFFECT module \n");
   }

};

#endif

