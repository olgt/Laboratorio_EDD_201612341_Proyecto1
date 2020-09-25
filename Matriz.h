#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include "Nodo_Matriz.h"
#include "Nodo_Objeto.h"
#include "Cabecera.h"
#include <fstream>

using namespace std;

class Matriz
{
private:
    Cabecera* horizontal;
    Cabecera* vertical;
    int objetos;
    Cabecera* getVertical(int x);
    Cabecera* getHorizontal(int y);
    Cabecera *crearHorizontal(int y);
    Cabecera *crearVertical(int x);

    Nodo_Matriz* obtenerUltimoVertical(Cabecera* , int);
    Nodo_Matriz* obtenerUltimoHorizontal(Cabecera* , int);

public:
    Matriz();
    ~Matriz();
    void add(Nodo_Objeto* nuevo);
    bool chequearNodoEsCabecera(Nodo_Matriz* nodoAnalizado);
    void codigo();

    void imprimirCabeceraX();
    void imprimirCabeceraY();
    void imprimirMatriz();


    void crearGrafica(string nombre);
    void enlacesNodosMatrizHorizontal(ofstream &, Nodo_Matriz *horizontal);
    void enlacesNodosMatrizVertical(ofstream & MyFile, Nodo_Matriz* vertical);

    void crearNodosExtraMatrizHorizontal(ofstream & MyFile, Nodo_Matriz* horizontal);

    int getLengthHorizontal();
    int getLengthVertical();

    Nodo_Matriz* getFromMatriz(int x, int y);
    void enlacesNodosVaciosHorizontal(ofstream & MyFile);
    void enlacesNodosVaciosVertical(ofstream & MyFile);

    void enlacesNodosVaciosCabeceraVertical(ofstream & MyFile);
    void enlacesNodosVaciosCabeceraHorizontal(ofstream & MyFile);

    int getVentanas();
    int getEspacio();
    int getParedes();

    int getObjetos();
    void sumarCantidadObjeto();

    void agregarNodosVaciosARank(ofstream & MyFile, int x);

    void enlacesVaciosArribaAbajo(ofstream & MyFile, string idActual, string idAbajo, int xActual, int xAbajo, int y);
    void enlacesNodosVaciosAbajoRestantes(ofstream & MyFile, string idActual,int xActual, int y);

    void enlacesVaciosIzquierdaDerecha(ofstream & MyFile, string idActual, string idDerecha, int yActual, int yDerecha, int x);
    void enlacesNodosVaciosDerechaRestantes(ofstream & MyFile, string idActual, int yActual, int x);

    void enlacesVaciosCabeceraIzquierdaDerecha(ofstream & MyFile, int yDerecha, int yCabecera, int posCabecera, string idDerecha);
    void enlacesVaciosCabeceraArribaAbajo(ofstream & MyFile, int xAbajo, int xCabecera, int posCabecera, string idAbajo);

    Matriz* copiarMatriz();

    void eliminarParedes(int x1, int y1, int x2, int y2);
    void eliminarObjeto(int id, int longitudObjeto);

};

#endif // MATRIZ_H
