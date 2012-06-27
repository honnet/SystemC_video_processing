#ifndef image_h
#define image_h
#include <png.h>

typedef struct Image {
    int   width, height;
    unsigned char  *pixel;
} Image;

#ifdef __cplusplus
extern "C" {
#endif

    void   image_read(Image * image, char *filename);
    void   image_write(Image * image, char *filename);

#ifdef __cplusplus
}
#endif

#endif
