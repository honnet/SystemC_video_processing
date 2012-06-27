/**********************************************************************
 * File : system.cpp
 * Date : 17/03/2010
 * Author : Cedric Honnet
 *
 * Testbench pour video_in ET video_out
 **********************************************************************/

#include <systemc.h>
#include "image.h"
#include "video_in.h"
#include "video_out.h"
#include "video_effect.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


////////////////////////////////////////////////////
//	MAIN
////////////////////////////////////////////////////

int sc_main (int argc, char *argv[])
{
    int	ncycles;
    sc_time pix_period(74, SC_NS);

    if (argc == 2) {
//	MAIN
        ncycles = atoi(argv[1]);
    } else{
        printf("\n");
        printf("The number of simulation cycles must be defined in the command line (-1 for unlimited)\n\n");
        exit(1);
    }


   ///////////////////////////////////////////////////////
   //      Declaration des signaux
   //////////////////////////////////////////////////////

   sc_clock                 clk("Clock", pix_period);
   sc_signal<bool>          reset_n;

   sc_signal<bool>           signal_href_in,   signal_href_out;
   sc_signal<bool>           signal_vref_in,   signal_vref_out;
   sc_signal<unsigned char> signal_pixel_in,  signal_pixel_out;

   /////////////////////////////////////////////////////////
   //	Instanciation des composants
   /////////////////////////////////////////////////////////

   VIDEO_IN video_in("VIDEO_IN");
   VIDEO_EFFECT video_effect("VIDEO_EFFECT");
   VIDEO_OUT video_out("VIDEO_OUT");


   //////////////////////////////////////////////////////////
   //	Connexion des composants
   //////////////////////////////////////////////////////////

   video_in.clk        (clk);       // in (qu'on genere ici)
   video_in.reset_n    (reset_n);   // in (qu'on genere ici)
   video_in.href       (signal_href_in);     // out (fait pour video_effect)
   video_in.vref       (signal_vref_in);     // out (fait pour video_effect)
   video_in.pixel_out  (signal_pixel_in);    // out (fait pour video_effect)

   video_effect.clk        (clk);
   video_effect.reset_n    (reset_n);
   video_effect.href_in    (signal_href_in);   //in
   video_effect.vref_in    (signal_vref_in);   //in
   video_effect.pixel_in   (signal_pixel_in);  //in
   video_effect.href_out   (signal_href_out);      //out
   video_effect.vref_out   (signal_vref_out);      //out
   video_effect.pixel_out  (signal_pixel_out);     //out

   video_out.clk       (clk);       // in (qu'on genere ici)
   video_out.reset_n   (reset_n);   // in (qu'on genere ici)
   video_out.href      (signal_href_out);     //    in (fait par video_effect)
   video_out.vref      (signal_vref_out);     //    in (fait par video_effect
   video_out.pixel_in  (signal_pixel_out);    //    in (fait par video_effect)

   // open trace file
   sc_trace_file *my_trace_file;
   my_trace_file = sc_create_vcd_trace_file ("simulation_trace");

   // chronogrammes signaux CLK et NRESET
   sc_trace(my_trace_file, clk,         "clk");
   sc_trace(my_trace_file, reset_n,      "reset_n");

   // chronogrammes video
   sc_trace(my_trace_file, video_effect.href_in,  "href_in");
   sc_trace(my_trace_file, video_effect.vref_in,  "vref_in");
   sc_trace(my_trace_file, video_effect.pixel_in, "pixel_in");
   sc_trace(my_trace_file, video_effect.href_out, "href_out");
   sc_trace(my_trace_file, video_effect.vref_out, "vref_out");
   sc_trace(my_trace_file, video_effect.pixel_out,"pixel_out");

   /* Initialisation de la simulation */
   reset_n = false;
   sc_start(pix_period);
   reset_n = true;
   sc_start(pix_period);

   /* Generation d'un reset */
   reset_n = false;
   sc_start(pix_period);
   reset_n = true;
   sc_start(pix_period);

   /* Lancement de la simulation */
   int i=0;
   while(1) {

         /* Si on a atteint le nombre de cycles demandés, on s'arrête */
         if(ncycles > 0)
            if(i >= ncycles)
               break;
         sc_start(pix_period);
         i++;


   } // end simulation loop

   // Close trace file
   sc_close_vcd_trace_file (my_trace_file);


   return EXIT_SUCCESS;

};
