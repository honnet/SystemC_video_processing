#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "image.h"


void image_read(Image * image, char *filename)
{
    FILE           *file;
    png_structp     png_ptr;
    png_infop       info_ptr;
    png_uint_32     width, height;
    int             bit_depth, color_type; 
    png_bytep      *row_pointers;
    int             i;  
    
    if(image->pixel)
        free(image->pixel);
    image->pixel = NULL;

    file = fopen(filename, "rb");
    assert(file != NULL);

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    assert(png_ptr != NULL);

    info_ptr = png_create_info_struct(png_ptr);
    assert(info_ptr != NULL);

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
        fclose(file);
        exit(-1);
    }

    png_init_io(png_ptr, file);

    png_read_info(png_ptr, info_ptr);
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
             NULL, NULL, NULL);
    assert(bit_depth == 8);
    if(color_type != PNG_COLOR_TYPE_GRAY) {
        fprintf(stderr, "Erreur sur le format de l'image d'entrée.\n");
        fprintf(stderr, "Le seul format PNG supporté est : niveaux de gris, 8bpp, sans canal alpha\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
        fclose(file);
        exit(-1);
    }

    image->width = width;
    image->height = height;
    image->pixel = (unsigned char *)malloc(width * height * sizeof(unsigned char));
    assert(image->pixel != NULL);

    row_pointers = png_malloc(png_ptr, height * sizeof(png_bytep));
    assert(row_pointers != NULL);
    for (i = 0; i < height; i++)
        row_pointers[i] = (png_bytep)(&image->pixel[i*width]);
    png_set_rows(png_ptr, info_ptr, row_pointers);

    png_read_image(png_ptr, row_pointers);

    png_free(png_ptr, row_pointers);

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    fclose(file);
}



void image_write(Image * image, char *filename)
{
    FILE           *file;
    png_structp     png_ptr;
    png_infop       info_ptr;
    png_bytep      *row_pointers;
    int             i; 

    file = fopen(filename, "wb");
    assert(file != NULL);

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    assert(png_ptr != NULL);

    info_ptr = png_create_info_struct(png_ptr);
    assert(info_ptr != NULL);

    assert(setjmp(png_jmpbuf(png_ptr)) == 0);

    png_init_io(png_ptr, file);

    png_set_IHDR(png_ptr, info_ptr, image->width, image->height, 8,
             PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
             PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    row_pointers = png_malloc(png_ptr, image->height * sizeof(png_bytep));
    assert(row_pointers != NULL);
    for (i = 0; i < image->height; i++)
        row_pointers[i] = (png_bytep)(&image->pixel[i*image->width]);
    png_set_rows(png_ptr, info_ptr, row_pointers);

    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    png_free(png_ptr, row_pointers);

    png_destroy_write_struct(&png_ptr, &info_ptr);

    fclose(file);
}
