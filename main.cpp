/* 
 * File:   main.cpp
 * Author: José Manuel Serrano Mármol
 * Author: Raúl Salazar de Torres
 * Date: 16 - 1 - 2012 
 */
 
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "imgs.h"

using namespace std;

void leerNucleo(char *ruta,vector<float> *nucleo,int *tamaNucleo){
    FILE *file;
    float dato;
    
    file = fopen(ruta,"r");
    
    if(file == NULL){
        cout << "No se puede leer Nucleo de convolución";
        exit(-1);
    }
    
    while(fscanf(file,"%f",&dato) != EOF){
        nucleo->push_back(dato);
        cout << dato;
    }
    
    *tamaNucleo = (int)sqrt(nucleo->size());
    
    if( (*tamaNucleo) % 2 == 1){
        cout << "Nucleo correcto" << endl;
    }else{
        cout << "Nucleo incorrecto" << endl;
        exit(-1);
    }
    
}


int main(int argc, char** argv) {
    /************* DECLARACIÖN DE VARIABLES ***************/
    
    //float nucleo[3][3]={{1.0/9.0,1.0/9.0,1.0/9.0},{1.0/9.0,1.0/9.0,1.0/9.0},{1.0/9.0,1.0/9.0,1.0/9.0}}; //Nucleo de convolución
    unsigned char *imagen;       // Imagen original
    unsigned char *imagenSalida; // Imagen de salida
    unsigned int h, w, M;        // Alto, ancho e intersidad
    imgs gestorImagen;           // Gestor de la imagen, carga y almacena imagenes
    
    /************** FORMA DE USO DE LA FUNCIÓN *************/
    if(argc < 3 ){
        cout << "USO: ejecutable rutaImagenOrigen rutaImagenDestino rutaNucleo";
        exit(-1);
    }
    
    /************** CARGAMOS NUCLEO DE CONVOLUCIÓN *************/
    int tamaNucleo,mitadTamano;
    vector<float> nucleo;
    leerNucleo(argv[3],&nucleo,&tamaNucleo);
    mitadTamano = tamaNucleo / 2;
    
    
    /************** CARGAMOS IMAGEN *************/
    
    if ( !gestorImagen.loadPgm (argv[1], &imagen, &w, &h, &M )){
      cout << "Error al cargar imagen en ESCALA DE GRISES" << endl;
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
                        acomulador += valorF * nucleo[(s + mitadTamano) * tamaNucleo + (t + mitadTamano)];
                    }
                }
                //Guardamos el resultado en la imagen de salida
                imagenSalida[w * x + y] = (unsigned char) acomulador;
            }
        }
    
   /************** GUARDAMOS IMAGEN *************/
    
   if ( !gestorImagen.savePgm (argv[2], imagenSalida, w, h, M ) ){
      cout << "Error llamando a savePpm" << endl;
      exit ( -1 );
   }
    
    cout << "IMAGEN OBTENIDA..." << endl;
    
    return 0;
}
