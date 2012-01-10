#include "imgs.h"

imgs::imgs(){
    
}

imgs::~imgs(){
    
}
// ----------------------------------------------------------------------
/**Carga una imagen en escala de grises desde un fichero PGM binario
   @param fName nombre del fichero con la imagen
   @param buffer almacenará un array con los valores de gris de la imagen.
                 Si hay algún error, apuntará a NULL
   @param ancho, alto almacenarán las dimensiones de la imagen
   @param max almacenará el valor máximo de intensidad de gris
   @retval 1 si no hay problemas
   @retval 0 en otro caso */
// ----------------------------------------------------------------------
int imgs::loadPgm ( const char *fName, unsigned char **buffer, unsigned int *ancho,
              unsigned int *alto, unsigned int *max )
{
   FILE *f;
   char auxBuf[256];

   *buffer = NULL;

   if ( ( f = fopen ( fName, "rb" ) ) == NULL )         /* Abre el fichero */
   {
      printf ( "loadPgm: error al abrir el fichero\n" );
      return ( 0 );
   }
   
   /* Lee el número mágico */
   if ( fgets ( auxBuf, 256, f ) == NULL )
   {
      printf ( "loadPgm: error al leer el fichero\n" );
      fclose ( f );
      return ( 0 );
   }
   
   if ( ( auxBuf[0] != 'P' ) || ( auxBuf[1] != '5' ) || ( auxBuf[2] != '\n' ) )
   {
      printf ( "loadPgm: el fichero no es un PGM válido\n" );
      fclose ( f );
      return ( 0 );
   }

   /* Opcionalmente, puede haber una línea de comentario en el fichero,
      empezando por "#". Si no la hay, intenta cargar las dimensiones de la
      imagen */
   if ( fgets ( auxBuf, 256, f ) == NULL )
   {
      printf ( "loadPgm: error al leer el fichero\n" );
      fclose ( f );
      return ( 0 );
   }

   if ( auxBuf[0] == '#' )
   {
      /* Descarta la línea y toma la siguiente para leer las dimensiones */
      if ( fgets ( auxBuf, 256, f ) == NULL )
      {
         printf ( "loadPgm: error al leer el fichero\n" );
         fclose ( f );
         return ( 0 );
      }
   }
   
   /* Lee las dimensiones */
   if ( sscanf ( auxBuf, "%d %d\n", ancho, alto ) != 2 )
   {
      printf ( "loadPgm: error al buscar las dimensiones\n" );
      fclose ( f );
      return ( 0 );
   }

   /* Lee el valor máximo de intensidad de gris */
   if ( fgets ( auxBuf, 256, f ) == NULL )
   {
      printf ( "loadPgm: error al leer el fichero\n" );
      fclose ( f );
      return ( 0 );
   }

   if ( sscanf ( auxBuf, "%d\n", max ) != 1 )
   {
      printf ( "loadPgm: error al buscar el valor máximo de intensidad\n" );
      fclose ( f );
      return ( 0 );
   }

   /* Reserva memoria para guardar la imagen */
   *buffer = (unsigned char *) malloc ( *ancho * *alto );
   if ( *buffer == NULL )
   {
      printf ( "loadPgm: error reservando memoria\n" );
      fclose ( f );
      return ( 0 );
   }

   /* Lee los bytes */
   if ( fread ( *buffer, 1, *ancho * *alto, f ) != *ancho * *alto )
   {
      printf ( "loadPgm: error al leer el fichero\n" );
      fclose ( f );
      return ( 0 );
   }
   
   fclose ( f );
   return ( 1 );
}


// ----------------------------------------------------------------------
/**Carga una imagen en formato RGB desde un fichero PPM binario
   @param fName nombre del fichero con la imagen
   @param buffer almacenará un array con los valores de color de la imagen.
                 Si hay algún error, apuntará a NULL
   @param ancho, alto almacenarán las dimensiones de la imagen
   @param max almacenará el valor máximo de intensidad de color
   @retval 1 si no hay problemas
   @retval 0 en otro caso */
// ----------------------------------------------------------------------
int imgs::loadPpm ( const char *fName, unsigned char **buffer, unsigned int *ancho,
              unsigned int *alto, unsigned int *max )
{
   FILE *f;
   char auxBuf[256];
   
   *buffer = NULL;
   
   if ( ( f = fopen ( fName, "rb" ) ) == NULL )         /* Abre el fichero */
   {
      printf ( "loadPpm: error al abrir el fichero\n" );
      return ( 0 );
   }
   
   /* Lee el número mágico */
   if ( fgets ( auxBuf, 256, f ) == NULL )
   {
      printf ( "loadPpm: error al leer el fichero\n" );
      fclose ( f );
      return ( 0 );
   }
   printf ( "%s\n", auxBuf );
   if ( ( auxBuf[0] != 'P' ) || ( auxBuf[1] != '6' ) || ( auxBuf[2] != '\n' ) )
   {
      printf ( "loadPpm: el fichero no es un PPM válido\n" );
      fclose ( f );
      return ( 0 );
   }

   /* Opcionalmente, puede haber una línea de comentario en el fichero,
      empezando por "#". Si no la hay, intenta cargar las dimensiones de la
      imagen */
   if ( fgets ( auxBuf, 256, f ) == NULL )
   {
      printf ( "loadPpm: error al leer el fichero\n" );
      fclose ( f );
      return ( 0 );
   }

   if ( auxBuf[0] == '#' )
   {
      /* Descarta la línea y toma la siguiente para leer las dimensiones */
      if ( fgets ( auxBuf, 256, f ) == NULL )
      {
         printf ( "loadPpm: error al leer el fichero\n" );
         fclose ( f );
         return ( 0 );
      }
   }
   
   /* Lee las dimensiones */
   if ( sscanf ( auxBuf, "%d %d\n", ancho, alto ) != 2 )
   {
      printf ( "loadPpm: error al buscar las dimensiones\n" );
      fclose ( f );
      return ( 0 );
   }

   /* Lee el valor máximo de intensidad de gris */
   if ( fgets ( auxBuf, 256, f ) == NULL )
   {
      printf ( "loadPpm: error al leer el fichero\n" );
      fclose ( f );
      return ( 0 );
   }

   if ( sscanf ( auxBuf, "%d\n", max ) != 1 )
   {
      printf ( "loadPpm: error al buscar el valor máximo de intensidad\n" );
      fclose ( f );
      return ( 0 );
   }

   /* Reserva memoria para guardar la imagen */
   *buffer = (unsigned char *) malloc ( *ancho * *alto * 3 );
   if ( *buffer == NULL )
   {
      printf ( "loadPpm: error al reservar memoria\n" );
      fclose ( f );
      return ( 0 );
   }

   /* Lee los bytes */
   if ( fread ( *buffer, 3, *ancho * *alto, f ) != *ancho * *alto )
   {
      printf ( "loadPpm: error al leer el fichero\n" );
      fclose ( f );
      return ( 0 );
   }
   
   fclose ( f );
   return ( 1 );
}


// ----------------------------------------------------------------------
/**Escribe una imagen en escala de grises en un fichero PGM binario
   @param fName nombre del fichero que se crea (no se comprueba si ya está
          creado)
   @param buffer array de valores de gris de la imagen
   @param ancho, alto dimensiones de la imagen
   @param max valor máximo de intensidad de gris
   @retval 1 si no hay problemas
   @retval 0 en otro caso */
// ----------------------------------------------------------------------
int imgs::savePgm ( const char *fName, unsigned char *buffer, unsigned int ancho,
              unsigned int alto, unsigned int max )
{
   FILE *f;

   if ( ( f = fopen ( fName, "wb" ) ) == NULL )         /* Abre el fichero */
   {
      printf ( "savePgm: error al abrir el fichero\n" );
      return ( 0 );
   }

   /* Escribe el número mágico, las dimensiones y el valor máximo de
      intensidad. */
   if ( fprintf ( f, "P5\n" ) < 0 )
   {
      printf ( "savePgm: error al escribir en el fichero\n" );
      fclose ( f );
      return ( 0 );
   }

   if ( fprintf ( f, "%d %d\n", ancho, alto ) < 0 )
   {
      printf ( "savePgm: error al escribir en el fichero\n" );
      fclose ( f );
      return ( 0 );
   }
   
   if ( fprintf ( f, "%d\n", max ) < 0 )
   {
      printf ( "savePgm: error al escribir en el fichero\n" );
      fclose ( f );
      return ( 0 );
   }

   /* Escribe los bytes de la imagen */
   if ( fwrite ( buffer, 1, ancho*alto, f ) != ancho*alto )
   {
      printf ( "savePgm: error al escribir en el fichero\n" );
      fclose ( f );
      return ( 0 );
   }

   fclose ( f );         /* Cierra el fichero */
   return ( 1 );
}


// ----------------------------------------------------------------------
/**Escribe una imagen RGB en un fichero PPM binario
   @param fName nombre del fichero que se crea (no se comprueba si ya está
          creado)
   @param buffer array de valores RGB de la imagen
   @param ancho, alto dimensiones de la imagen
   @param max valor máximo de intensidad de color
   @retval 1 si no hay problemas
   @retval 0 en otro caso */
// ----------------------------------------------------------------------
int imgs::savePpm ( const char *fName, unsigned char *buffer, unsigned int ancho,
              unsigned int alto, unsigned int max )
{
   FILE *f;

   if ( ( f = fopen ( fName, "wb" ) ) == NULL )         /* Abre el fichero */
   {
      printf ( "savePpm: error al abrir el fichero\n" );
      return ( 0 );
   }

   /* Escribe el número mágico, las dimensiones y el valor máximo de
      intensidad. */
   if ( fprintf ( f, "P6\n" ) < 0 )
   {
      printf ( "savePpm: error al escribir en el fichero\n" );
      fclose ( f );
      return ( 0 );
   }
   
   if ( fprintf ( f, "%d %d\n", ancho, alto ) < 0 )
   {
      printf ( "savePpm: error al escribir en el fichero\n" );
      fclose ( f );
      return ( 0 );
   }

   if ( fprintf ( f, "%d\n", max ) < 0 )
   {
      printf ( "savePpm: error al escribir en el fichero\n" );
      fclose ( f );
      return ( 0 );
   }

   /* Escribe los bytes de la imagen */
   if ( fwrite ( buffer, 3, ancho*alto, f ) != ancho*alto )
   {
      printf ( "savePpm: error al escribir en el fichero\n" );
      fclose ( f );
      return ( 0 );
   }

   fclose ( f );         /* Cierra el fichero */
   return ( 1 );
}

