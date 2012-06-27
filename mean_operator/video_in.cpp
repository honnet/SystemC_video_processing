////////////////////////////////////////////////////////////////////////////////
// File : video_in.h
// Author : Alexis Polti
// Date : 12/03/2008
// This program is released under the GNU Public License
// Copyright : ENST
//
// This component models a video input source 
// 
/////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "video_in.h"


/***************************************************************************
 *      gen_sorties()
 ***************************************************************************/

void VIDEO_IN::gen_sorties()
{
    while(1)
    {
        if(reset_n == false)
        {
          reset:
            // Reset : on remet tous les paramètres à zéro
            if(current_image_number !=0)
            {
                current_image_number = 0;
                read_image();
            }
            pixel_out = 0;
            href = false;
            vref = false;
            
            // Puis on attend le prochain coup d'horloge, ou un reset
            wait();
        }
        else
        {
            int i,j;
            for(i=0; i<625; i++)
                for(j=0; j<874; j++)
                {
                    // Si on est dans la fenêtre active, on sort le pixel courant
                    // Rappel : une trame video fait 874*625, l'image active est de 720*576
                    if((i<576) && (j<720))
                        pixel_out = image.pixel[i*image.width+j];
                    else
                        pixel_out = 0;
                    
                    // Generation de HREF
                    // HREF est actif pendant la sortie des pixels actifs
                    href = (i<576) && (j<720);
                    
                    // Generation de VREF
                    // VREF est actif pendant les 3 premières lignes d'une image
                    vref = (i<3);

                    // Puis on attend le prochain coup d'horloge, ou un reset
                    wait();
                    
                    // Si on est reveillé par un reset, on revient à la case départ
                    // (les goto sont dans ce genre de cas bien pratique...)
                    if(reset_n == false)
                        goto reset;
                }
            
            // On a fini une image, on passe à la suivante
           current_image_number ++;
           read_image();         
        }
    }
}



/***********************************
 *	misc methods
 ***********************************/


void VIDEO_IN::read_image()
{
    char name[2048]; // grmpf, il vaudrait mieux faire un malloc...
    FILE *fin;

    // Calcul du nom de la prochaine image.
    // Si ce nom ne correspond a aucun fichier, on remet l'index a zero
    sprintf(name, "%s%02d.png", base_name, current_image_number);
    fin = fopen(name, "rb");
    if(fin == NULL)
    {
        current_image_number = 0;
        sprintf(name, "%s%02d.png", base_name, current_image_number);
        fin = fopen(name, "rb");
        if(fin == NULL) {
            fprintf(stderr, "VIDEO_IN read_image : impossible d'ouvrir l'image source %s\n", name);
            exit(-1);
        }
    }
    fclose(fin);

    // Lecture proprement dite de l'image PNG a l'aide de la libpng
    fprintf(stderr, "Ouverture de l'image %s\n", name);
    image_read(&image, name);
    
    // L'image est lue et chargée en mémoire.
    // On vérifie quand même que l'image lue a la bonne taille (720*576)
    if((image.width != 720) || (image.height != 576))
    {
        fprintf(stderr, "VIDEO_IN : l'image %s n'a pas les bonnes dimensions (720*576)\n", name);
        exit(-1);
    }
    
    fprintf(stderr, "...Done\n");


}
