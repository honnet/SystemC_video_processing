////////////////////////////////////////////////////////////////////////////////
// File : video_out.h
// Author : Cedric Honnet
// Date : 17/03/2010
//
// Creer des images PNG à partir d'un flux vidéo CCIR 601
// 
/////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "video_out.h"

#define max(x,y) (x>y ? x:y)


/***************************************************************************
 *      gen_images()
 ***************************************************************************/

void VIDEO_OUT::gen_images()
{
    while(1)
    {
        if(reset_n == false)
        {
            current_image_number = 0;
            cpt_v = 0;
            cpt_h = 0;
            cpt_pixels = 0;
        }
        else
        {
            if (href && !href_old) {         // detecte un front montant sur href
               image.width = max(cpt_h, image.width); // sauvegarde la largeur de l'image
               cpt_h = 0;
               cpt_v++;
            }
            if (vref && !vref_old) {         // detecte un front montant sur vref => nouvelle image !
               
               if (current_image_number > 0){
                  image.height = cpt_v;      // sauvegarde la hauteur de l'image
                  //cout << "\n\n ******** VIDEO_OUT: cpt_h=" << cpt_h << ", cpt_v=" << cpt_v << endl;                                // !!!!!!!!!!!!!!
                  write_image();             // on sauvegarde l'image qu'on vient de finir
                  }
               cpt_v = 0;
               cpt_pixels = 0;
               current_image_number ++;      // incremente en prevision de la prochaine image
            } else {
               // Si on est dans la fenêtre active, on ecrit le pixel courant
               if (href) {
                  // incremente selon clk (et href) :
                  cpt_h ++;
                  cpt_pixels ++;
                  image.pixel[cpt_pixels] = pixel_in.read(); // on aurait pu utiliser cpt_h+cpt_v*image.width mais width est inconnu au debut
               }
            }
        }
    // a chaque front d'horloge (meme si reset) :
    vref_old = vref; // sauvegarde l'etat de vref pour pouvoir detecter un front montant
    href_old = href; // sauvegarde l'etat de href pour pouvoir detecter un front montant

   // Puis on attend le prochain front
    wait();
   }
}
    

        
/***********************************
 *	misc methods
 ***********************************/


void VIDEO_OUT::write_image()
{
    char name[2048]; // grmpf, il vaudrait mieux faire un malloc...

    // Calcul du nom de la prochaine image.
    sprintf(name, "%s%02d.png", base_name, current_image_number-1); // car 

    // Ecriture proprement dite de l'image PNG a l'aide de la libpng
    fprintf(stderr, "Ecriture de l'image %s\n", name);
    //fprintf(stderr, "\n\nVIDEO_OUT: w=%d, h=%d\n\n\n", image.width, image.height);                                                    // !!!!!!!!!!!!!!
    image_write(&image, name);
    fprintf(stderr, "...Done\n");
}

