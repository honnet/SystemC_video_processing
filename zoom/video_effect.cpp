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

#include <stdio.h>
#include "video_effect.h"

void VIDEO_EFFECT::gen_effet()
{
   //////////////////////////////////////////////////////////////////////////////////////
   // 0) reset :
   //////////////////////////////////////////////////////////////////////////////////////
   if(reset_n == false)
   {
      vref_in_delayed = false;
      href_in_delayed = false;
      x_in = 0;
      y_in = 0;
      x_out = 0;
      y_out = 0;
      cpt = 0;
      for (int i=0; i<BUF_SIZE; i++)
      {
         buffer_in[i] = 0;
         buffer_out[i] = 0;
      }
      acquisition_done = false;
      output_enabled = false;
   }
   else
   {
      //////////////////////////////////////////////////////////////////////////////////////
      // 1.a) synchro & coordonees en rapport avec l'entree :
      //////////////////////////////////////////////////////////////////////////////////////
      
      // sauvegarde de vref et href_in a chaque cycle de clk :
      vref_in_delayed = vref_in;
      href_in_delayed = href_in;

      // detection de front montant sur href :
      if (href_in && !href_in_delayed)
      {
         x_in = 0;                                             // raz de x_in en fin de ligne
         // detection de front montant sur vref :
         if (vref_in && !vref_in_delayed)
            y_in = 0;                                          // raz de y_in en fin d'image
         else
            y_in++;
      } 
      else
         x_in++;


      //////////////////////////////////////////////////////////////////////////////////////
      // 1.b) acquisition et sauvegarde des pixels en entree :
      //////////////////////////////////////////////////////////////////////////////////////
      
      // enregistrement des pixels uniquement dans la zone qui nous interesse :
      if ((x_in>=WIDTH/4) && (x_in<3*(WIDTH/4)) && (y_in>=HEIGHT/4) && (y_in<3*(HEIGHT/4)))
      {
         buffer_in[ x_in-WIDTH/4 + (y_in-HEIGHT/4)*(WIDTH/2) ] = pixel_in.read();
      }

      // fin d'acquisition ? (sinon on ne lance pas encore la sauvegarde)
      if (y_in == 3*HEIGHT/4)
      {
         acquisition_done = true; // restera true jusqu'a la fin !
         cpt = 0;
      }
         
      // si oui, on peut commencer : (on peut meme finir la sauvegarde en debut d'image suivante)
      if ( acquisition_done && (y_in>=3*(HEIGHT/4) || y_in<HEIGHT/4) )
      {
         // fait une sauvegarde a chaque clk.pos() : (on est pas des brutes non-plus...)
         if(cpt<BUF_SIZE)
         {
            buffer_out[cpt] = buffer_in[cpt];
            cpt++;
         }
         else // sauvegarde finie, le booleen ci-dessous permet de ne rien sortir avant la fin de la 1ere image
            output_enabled = true;  // restera true jusqu'a la fin !
      }


      //////////////////////////////////////////////////////////////////////////////////////
      // 2.a) synchro & coordonees en rapport avec la sortie :
      //////////////////////////////////////////////////////////////////////////////////////
      
      // regenere la synchro :
      if (output_enabled)
      {
         href_out = (y_out<HEIGHT) && (x_out<WIDTH);
         vref_out = (y_out<3);
         
         if (x_out == TOTAL_WIDTH-1)
         {
            x_out = 0;                                             // raz de x_out en fin de ligne
            if (y_out == TOTAL_HEIGHT-1)
               y_out = 0;                                          // raz de y_out en fin d'image
            else
               y_out++;
         } 
         else
            x_out++;
      }
      else
      {
         href_out = false;
         vref_out = false;
      }


      //////////////////////////////////////////////////////////////////////////////////////
      // 2.b) relecture avec effet zoom :
      //////////////////////////////////////////////////////////////////////////////////////

      // ...uniquement dans les parties actives :
      if (href_out && output_enabled)
      {
         pixel_out = buffer_out[x_out/2 + (y_out/2)*(WIDTH/2)];
      }
      
   }
}


