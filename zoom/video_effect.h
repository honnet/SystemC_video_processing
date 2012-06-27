///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File : video_effect.h
// Author : Cédric Honnet
// Date : 17/03/2010
//
// Zoom 2x
//
// l'idee est de simplifier le code le plus possible, en voila quelques principes :
// 1) on enregistre toute la partie a afficher
// 2) on attend la fin de l'image pour commencer a envoyer le zoom de ce qu'on vient d'enregistrer
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef VIDEO_EFFECT_H
#define VIDEO_EFFECT_H

#define HEIGHT       576
#define WIDTH        720
#define TOTAL_HEIGHT 625
#define TOTAL_WIDTH  874
#define BUF_SIZE     ((WIDTH/2) * (HEIGHT/2)) // = 103680

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
   sc_signal<bool> vref_in_delayed, href_in_delayed;        // signaux de syncho retardes d'une periode de clk
   unsigned int x_in, y_in, x_out, y_out, cpt;              // "coordonnees" des pixels et compteur de recopie
   unsigned char buffer_out[BUF_SIZE], buffer_in[BUF_SIZE]; // buffer_in enregistre puis on le copie dans buffer_out
   bool output_enabled, acquisition_done;                   // permet de ne rien sortir avant la 1ere image
   
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





