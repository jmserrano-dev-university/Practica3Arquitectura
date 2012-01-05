#include <stdio.h>
#include <stdlib.h>

#ifndef __IMGS_H__
#define __IMGS_H__

class imgs{
public:
    imgs();
    ~imgs();

    int loadPgm ( const char *fName, unsigned char **buffer, unsigned int *ancho,
                  unsigned int *alto, unsigned int *max );

    int loadPpm ( const char *fName, unsigned char **buffer, unsigned int *ancho,
                  unsigned int *alto, unsigned int *max );

    int savePgm ( const char *fName, unsigned char *buffer, unsigned int ancho,
                  unsigned int alto, unsigned int max );

    int savePpm ( const char *fName, unsigned char *buffer, unsigned int ancho,
                  unsigned int alto, unsigned int max );
};

#endif


