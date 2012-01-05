/* 
 * File:   main.cpp
 * Author: serrano
 *
 * Created on 5 de enero de 2012, 10:01
 */
 
#include <cstdlib>
#include <iostream>
#include <vector>
#include "imgs.h"

using namespace std;

//void leerNucleo(string ruta,double nucleo[][]){
//    
//}


int main(int argc, char** argv) {
    /************* DECLARACIÖN DE VARIABLES ***************/
    
    float nucleo[3][3]={{1.0/9.0,1.0/9.0,1.0/9.0},{1.0/9.0,1.0/9.0,1.0/9.0},{1.0/9.0,1.0/9.0,1.0/9.0}}; //Nucleo de convolución
    unsigned char *imagen;       // Imagen original
    unsigned char *imagenSalida; // Imagen de salida
    unsigned int h, w, M;        // Alto, ancho e intersidad
    string nombreImagen;         // Ruta de la imagen
    int mitadTamano = 3/2;       // Mitad del tamaño del núcleo
    imgs gestorImagen;           // Gestor de la imagen, carga y almacena imagenes
    
//    nombreImagen = "./imagenBN.pgm";

    
    /************** CARGAMOS IMAGEN *************/
    
    if ( !gestorImagen.loadPgm ("imagenBN.pgm", &imagen, &w, &h, &M )){
      cout << "Error llamando a loadPpm" << endl;
      exit( -1 );
    }
    
    /************** REALIZAMOS CONVOLUCIÓN *************/
    
    float acomulador,valorF;
    int fx,fy;
    imagenSalida = (unsigned char *) malloc ( w * h ); //Resevamos memoria para la imagen de salida (ancho por alto)
    
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h ; y++){
            //Aplicamos convolución
            acomulador = 0;
            for(int s = (mitadTamano * -1); s <= mitadTamano; s++){
                for(int t = (mitadTamano * -1); t <= mitadTamano; t++){
                    fx = x + s;
                    fy = y + t;
                    
                    if(fx < 0 || fy < 0 || fx >= w || fy >= h){
                        valorF = 0; //Si nos salimos de los límites ponemos 0
                    }else{
                        valorF = imagen[w * fx + fy]; //Recorremos la matriz con un solo indice
                    }
                    acomulador += valorF * nucleo[s + mitadTamano][t + mitadTamano];
                }
            }
            //Guardamos el resultado en la imagen de salida
            imagenSalida[w * x + y] = (unsigned char) acomulador;
        }
    }
    
   /************** GUARDAMOS IMAGEN *************/
    
   if ( !gestorImagen.savePgm ( "resultado.pgm", imagenSalida, w, h, M ) ){
      cout << "Error llamando a savePpm" << endl;
      exit ( -1 );
   }
    
    cout << "IMAGEN OBTENIDA..." << endl;
    return 0;
}

