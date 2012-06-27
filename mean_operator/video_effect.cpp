///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File : video_effect.h
// Author : Cédric Honnet
// Date : 17/03/2010
//
// filtre moyenneur sur 8 pixels voisins
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "video_effect.h"


void VIDEO_EFFECT::gen_effet()
{
   //////////////////////////////////////////////////////////////////////////////////////
   // reset :
   //////////////////////////////////////////////////////////////////////////////////////
   if(reset_n == false)
   {
      href_out = 0;
      vref_out = 0;

      vref_old[0] = 0;
      vref_old[1] = 0;

      href_old[0] = 0;
      href_old[1] = 0;
      href_old[2] = 0;

      pixel_out = 0;
      for (int i=0; i<BUF_SIZE; i++) buffer[i]=0;
   }
   else
   {
      //////////////////////////////////////////////////////////////////////////////////////
      // synchro :
      //////////////////////////////////////////////////////////////////////////////////////
      // sauvegarde vref_in a chaque nouvelle ligne (pour le regenerer avec 2 lignes de retard) :
      if (href_in.read() & ~href_old[0]){
         vref_old[1] = vref_old[0];
         vref_old[0] = vref_in.read();
      }

      // sauvegarde href_in a chaque cycle (pour le regenerer avec 3 colonnes de retard) :
      href_old[2] = href_old[1];
      href_old[1] = href_old[0];
      href_old[0] = href_in;

      // regenere la synchro avec la ligne de retard et la colonne de retard :
      vref_out = vref_old[1];
      href_out = href_old[2];

      //////////////////////////////////////////////////////////////////////////////////////
      // moyenne :
      //////////////////////////////////////////////////////////////////////////////////////

      if (href_old[2]) // uniquement dans les parties actives :
      {
         // copie la moyenne sur 8 pixels voisins en sortie : (division effectuee par 3 decalage a droite)
         pixel_out = // ligne precedente :
                     (buffer[720*0 + 0] >> 3) +
                     (buffer[720*0 + 1] >> 3) +
                     (buffer[720*0 + 2] >> 3) +
                     // ligne courrante :
                     (buffer[720*1 + 0] >> 3) +
                     //SANS le pixel du milieu
                     (buffer[720*1 + 2] >> 3) +
                     // ligne suivante :
                     (buffer[720*2 + 0] >> 3) +
                     (buffer[720*2 + 1] >> 3) +
                     (buffer[720*2 + 2] >> 3) ;

         // decale le buffer d'un pixel et charge le nouveau pixel :
         for (int i=0; i<BUF_SIZE-1; i++) buffer [i+1] = buffer [i];
         buffer [0] = pixel_in;
      }

      //////////////////////////////////////////////////////////////////////////////////////
   }
}


