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

/**
 * Función que lee un núcleo desde fichero
 * @param ruta Ruta donde se encuentra el núcleo
 * @param nucleo Devuelve el núcleo leido en vector
 * @param tamaNucleo Devuelve el tamaño del núcleo leido
 */
void leerNucleo(char *ruta, vector<float> *nucleo, int *tamaNucleo) {
    FILE *file;
    float dato;

    file = fopen(ruta, "r");

    if (file == NULL) {
        cout << "No se puede leer Nucleo de convolución";
        exit(-1);
    }

    while (fscanf(file, "%f", &dato) != EOF) {
        nucleo->push_back(dato);
    }

    *tamaNucleo = (int) sqrt(nucleo->size());

    if ((*tamaNucleo) % 2 != 1) {
        cout << "Nucleo incorrecto" << endl;
        exit(-1);
    }

}

int main(int argc, char** argv) {
    /************* DECLARACIÓN DE VARIABLES ***************/
    unsigned char *imagen; // Imagen original
    unsigned char *imagenSalida; // Imagen de salida
    
    unsigned char *imagenC; // Imagen original
    unsigned char *imagenSalidaC; // Imagen de salida
    
    
    unsigned int h, w, M; // Alto, ancho e intersidad
    imgs gestorImagen; // Gestor de la imagen, carga y almacena imagenes

    /************** FORMA DE USO DE LA FUNCIÓN *************/
    if (argc < 3) {
        cout << "USO: ejecutable rutaImagenOrigen rutaImagenDestino rutaNucleo";
        exit(-1);
    }

    /************** DETECCIÓN DE IMAGEN EN ESCALA DE GRISES O RBG *************/
    bool color;
    string ruta = argv[1];
    ruta = ruta.substr(ruta.length() - 3, ruta.length());
    if (ruta.compare("pgm") == 0) {
        color = false;
    } else {
        if (ruta.compare("ppm") == 0) {
            color = true;
        } else {
            cout << "ERROR: Extensión de la imagen incorrecta. (.pgm o .ppm)" << endl;
            exit(-1);
        }
    }

    /************** CARGAMOS NÚCLEO DE CONVOLUCIÓN *************/
    int tamaNucleo, mitadTamano;
    vector<float> nucleo;
    leerNucleo(argv[3], &nucleo, &tamaNucleo);
    mitadTamano = tamaNucleo / 2;


    /************** CARGAMOS IMAGEN *************/
    if (!color) {
        if (!gestorImagen.loadPgm(argv[1], &imagen, &w, &h, &M)) {
            cout << "ERROR: Cargar imagen en ESCALA DE GRISES" << endl;
            exit(-1);
        }
    } else {
        if (!gestorImagen.loadPpm(argv[1], &imagenC, &w, &h, &M)) {
            cout << "ERROR: Cargar imagen en COLOR" << endl;
            exit(-1);
        }
    }

    /************** REALIZAMOS CONVOLUCIÓN *************/
    float acomulador, valorF;
    int fx, fy;
    if (!color) { //Imagen en ESCALA DE GRIS    
        imagenSalida = (unsigned char *) malloc(w * h); //Resevamos memoria para la imagen de salida (ancho por alto)

        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                //Aplicamos convolución
                acomulador = 0;
                for (int s = (mitadTamano * -1); s <= mitadTamano; s++) {
                    for (int t = (mitadTamano * -1); t <= mitadTamano; t++) {
                        fx = x + s;
                        fy = y + t;

                        if (fx < 0 || fy < 0 || fx >= w || fy >= h) {
                            valorF = 0; //Si nos salimos de los límites ponemos 0
                        } else {
                            valorF = imagen[w * fx + fy]; //Recorremos la matriz con un solo indice
                        }
                        acomulador += valorF * nucleo[(s + mitadTamano) * tamaNucleo + (t + mitadTamano)];
                    }
                }
                //Guardamos el resultado en la imagen de salida
                imagenSalida[w * x + y] = (unsigned char) acomulador;
            }
        }
    } else { //Imagen en COLOR
        imagenSalidaC = (unsigned char *) malloc(w * h * 3); //Resevamos memoria para la imagen de salida (ancho por alto)
        for (int z = 0; z < 3; z++) {
            for (int x = 0; x < w; x++) {
                for (int y = 0; y < h; y++) {
                    //Aplicamos convolución
                    acomulador = 0;
                    for (int s = (mitadTamano * -1); s <= mitadTamano; s++) {
                        for (int t = (mitadTamano * -1); t <= mitadTamano; t++) {
                            fx = x + s;
                            fy = y + t;

                            if (fx < 0 || fy < 0 || fx >= w || fy >= h) {
                                valorF = 0; //Si nos salimos de los límites ponemos 0
                            } else {
                                valorF = imagenC[w * fx + fy + z * w * h]; //Recorremos la matriz con un solo indice
                            }
                            acomulador += valorF * nucleo[(s + mitadTamano) * tamaNucleo + (t + mitadTamano)];
                        }
                    }
                    //Guardamos el resultado en la imagen de salida
                    imagenSalidaC[w * x + y + z * w * h] = (unsigned char) acomulador;
                }
            }
        }
    }

    /************** GUARDAMOS IMAGEN *************/
    if (!color) {
        if (!gestorImagen.savePgm(argv[2], imagenSalida, w, h, M)) {
            cout << "ERORR: Guardar imagen resultado en ESCALA DE GRISES" << endl;
            exit(-1);
        }
    } else {
        if (!gestorImagen.savePgm(argv[2], imagenSalidaC, w, h, M)) {
            cout << "ERORR: Guardar imagen resultado en COLOR" << endl;
            exit(-1);
        }
    }

    cout << "IMAGEN OBTENIDA..." << endl;

    return 0;
}
